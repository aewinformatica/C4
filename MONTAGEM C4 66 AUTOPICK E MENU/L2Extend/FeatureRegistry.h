/*
    This file is part of L2Extend.

    L2Extend is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    L2Extend is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with L2Extend.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <map>
#include <string>
#include <vector>


template <typename DerivedT>
class Feature
{
protected:

	static DerivedT _instance;

public:

	DerivedT& derived()
	{ return static_cast<DerivedT&>(*this); }

	const DerivedT& derived() const
	{ return static_cast<const DerivedT&>(*this); }

	bool initAfterLoadData()
	{ return true; }

	bool initProcessAttach()
	{ return true; }
};

template <typename DerivedT>
DerivedT Feature<DerivedT>::_instance;


/*
	FeatureRegistry HOWTO

	Imagine you're writing a new feature - Territory Wars. You need
	to place some hooks during startup, but only after Fortresses have
	been initialized, and later load some data.

	struct TerritoryWars : Feature<TerritoryWars>
	{
		const char* name() const
		{
			return "Territory Wars";
		}

		TerritoryWars()
		{
			if (this != &_instance) return;                     // *1
			FeatureRegistry::addFeature(*this);
			FeatureRegistry::addDependency(*this, "Fortresses");
		}

		bool initProcessAttach()
		{
			// place hooks here
			return true;
		}

		bool initAfterLoadData()
		{
			// load data here
			return true;
		}
	};

	Only name() must always be defined, FeatureRegistry uses it to find
	dependencies. Feature registration is done inside the constructor.

	The line marked with *1 is important. Not only it ensures that the
	code following it is not called twice, it ensures that it is called
	at least once. Without it, the static member _instance would not be
	instantiated at all. Of course you could define your own instance
	of TerritoryWars as a global variable, but I find this way more
	convenient.

	Put this definition in a .cpp file, there's no need to put it in
	a header. Territory Wars' initialization functions will be called
	when appropriate. If Fortresses fail to initialize properly, then
	TWs initialization will be skipped.

	-- Light'm
 */

class FeatureRegistry
{
public:

	enum Stage
	{
		stInitFailed,
		stProcessAttach,
		stAfterLoadData,
	};

	template <typename DerivedT>
	static void addDependency(const Feature<DerivedT>& feat, const char* depend)
	{
		FeatureInfo& featInfo = instance()._features[feat.derived().name()];
		FeatureInfo& dependInfo = instance()._features[depend];
		featInfo._depends.push_back(&dependInfo);
	}

	template <typename DerivedT>
	static void addFeature(const Feature<DerivedT>& feat)
	{
		FeatureInfo& featInfo = instance()._features[feat.derived().name()];

		if (featInfo._feature == 0)
			featInfo._feature = new ConcreteFeature<DerivedT>(feat);
		else
		{
			std::string msg;
			msg += "[" __FUNCTION__ "]\n\n";
			msg += "type = ";
			msg += typeid(DerivedT).name();
			msg += "\nname = ";
			msg += feat.derived().name();
			msg += "\n\nAnother feature of that name has already been registered.";
			error(msg.c_str());
		}
	}

	template <typename FunctionT>
	static void foreachFeature(Stage st, FunctionT func)
	{
		FeatureMap::iterator it = instance()._features.begin();
		FeatureMap::iterator end = instance()._features.end();

		for (; it != end; ++it)
		{
			int initBit = it->second._initBits & FeatureInfo::stageBit(st);
			int failBit = it->second._initBits & FeatureInfo::stageBit(stInitFailed);
			func(it->first, !!failBit, !(failBit | initBit));
		}
	}

	static bool initFeatures(Stage st);

	static FeatureRegistry& instance();

private:

	struct AbstractFeature
	{
		virtual ~AbstractFeature() {}
		virtual bool init(Stage st) = 0;
		virtual const char* name() const = 0;
	};

	template <typename DerivedT>
	struct ConcreteFeature : public AbstractFeature
	{
		DerivedT _feat; // a copy, not reference!

		ConcreteFeature(const Feature<DerivedT>& feat)
			: _feat(feat.derived()) {}

		virtual bool init(Stage st)
		{
			switch (st)
			{
				default: return false;
				case stProcessAttach: return _feat.initProcessAttach();
				case stAfterLoadData: return _feat.initAfterLoadData();
			}
		}

		virtual const char* name() const
		{
			return _feat.name();
		}
	};

	struct FeatureInfo
	{
		AbstractFeature*                _feature;
		std::vector<const FeatureInfo*> _depends;
		int                             _initBits;

		FeatureInfo(AbstractFeature* feature = 0)
			: _feature(feature)
			, _initBits(0) {}

		~FeatureInfo()
		{
			delete _feature;
		}

		bool dependsOk(Stage st) const
		{
			int requiredBits = stageDependsBits(st);
			int testBits = requiredBits | stageBit(stInitFailed);

			// check that none of previous stages failed
			if ((_initBits & testBits) != requiredBits)
				return false;

			requiredBits |= stageBit(st);
			testBits |= stageBit(st);

			// check that all dependencies have already passed this stage
			for (size_t i = 0; i < _depends.size(); ++i)
			{
				int dependBits = _depends[i]->_initBits;
				if ((dependBits & testBits) != requiredBits)
					return false;
			}

			// ready to run init stage 'st'
			return true;
		}

		bool needsInit(Stage st) const
		{
			if (_feature == 0) return false;
			if (_initBits & stageBit(stInitFailed)) return false;
			if (_initBits & stageBit(st)) return false;
			return true;
		}

		void setStage(Stage st)
		{
			_initBits |= stageBit(st);
		}

		static int stageBit(Stage st)
		{
			return 1 << st;
		}

		static int stageDependsBits(Stage st)
		{
			return ((1 << st) - 1) & ~(1 << stInitFailed);
		}
	};

	struct StrLess
	{
		bool operator() (const char* left, const char* right) const
		{
			return strcmp(left, right) < 0;
		}
	};

	typedef std::map<const char*, FeatureInfo, StrLess> FeatureMap;

	FeatureMap _features;

	// private default constructor/destructor
	FeatureRegistry() {}
	~FeatureRegistry() {}

	// copy constructor and assigment operator not defined
	FeatureRegistry(const FeatureRegistry& other);
	FeatureRegistry& operator= (const FeatureRegistry& other);

	static void error(const char* msg);
};
