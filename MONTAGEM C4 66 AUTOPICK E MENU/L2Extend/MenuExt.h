#pragma once
#include "Global.h"

class MenuExt
{
public:
	static void Install();
	static bool ShoWindowHook(HWND hwnd,int nCmdShow);

	static bool CALLBACK HandleCommand(HWND hWnd ,UINT message,WPARAM wParam,LPARAM Lparam);
};