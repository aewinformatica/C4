#include "Global.h"

char *StrNChr(char *str, char c, int len)
{
	//guard(const char *StrNChr(const char *str, char c, int len));

	while (len > 0)
	{
		if (*str == c)
			return str;
		str++;
		len--;
	}
	return str;

	//unguard;
}

int WcsNLen(const char *str, int len)
{
//	guard(int WcsNLen(const unsigned char *str, int len));

	int i;
	for (i = 0; i < len; i++)
	{
		if (!str[0] && !str[1])
			break;
		str += 2;
	}
	return i;

//	unguard;
}

const char *DisassembleQ(const char* packet, char* format, ...)
{
//	guard(const unsigned char *Disassemble(const unsigned char* packet, const char* format, ...));

	char* f = format;
	va_list ap;
	int t;
	va_start(ap, format);
	while ((t = *format++))
	{
		switch (t)
		{
		case 'c':
			{
				char* cp = va_arg(ap, char*);
				*cp = *packet++;
			}
			break;
		case 'h':
			{
				short* hp = va_arg(ap, short*);
#ifdef _WIN32
				*hp = ((short *)packet)[0];
#else
				*hp = packet[0] + (packet[1] << 8);
#endif
				packet += 2;
			}
			break;
		case 'd':
			{
				int* dp = va_arg(ap, int*);

#ifdef _WIN32           // CPU specific optimization.
				*dp = ((int *)packet)[0];
#else
				*dp = packet[0] + (packet[1] << 8) + (packet[2] << 16) + (packet[3] << 24);
#endif
				packet += 4;
			}
			break;

		case 'f':
			{
				double* dp = va_arg(ap, double*);

#ifdef _WIN32           // CPU specific optimization.
				CopyMemory(dp, packet, 8);
				/*
				int i1 = *(int*)packet;
				int i2 = *(((int*)packet)+1);
				*(((int*)dp)+0) = i2;
				*(((int*)dp)+1) = i1;
				*/
				/*
				*dp = ((double *)packet)[0];
				*/
#else
				*dp = packet[0] + (packet[1] << 8) + (packet[2] << 16) + (packet[3] << 24)
					+ (packet[4] << 32) + (packet[5] << 40) + (packet[6] << 48) + (packet[7] << 56)
#endif
				packet += 8;
			}
			break;

		case 's':
			{
				int dstLen = va_arg(ap, int);
				char* dst = va_arg(ap, char*);
				strncpy(dst, (char*)packet, dstLen);
				dst[dstLen - 1] = 0;
				char* end = (char*)StrNChr((char*)packet, '\0', dstLen) + 1;
//		if (end - packet > dstLen) {
//		    log.Add(LOG_ERROR, "too long string in %s", f);
//		}
				packet = end;
			}
			break;
		case 'S':
			{
				int len = va_arg(ap, int) / sizeof(wchar_t);
				len = WcsNLen(packet, len-1);
				wchar_t* dst = va_arg(ap, wchar_t*);
				memcpy(dst, packet, len * sizeof(wchar_t));
				dst[len] = 0;
				packet += (len + 1) * sizeof(wchar_t);
			}
			break;
		case 'Q':
			{
				__int64* dp = va_arg(ap, __int64*);

#ifdef _WIN32           // CPU specific optimization.
				*dp = ((__int64 *)packet)[0];
#else
				*dp = packet[0] + (packet[1] << 8) + (packet[2] << 16) + (packet[3] << 24) + 
					(packet[4] << 32) + (packet[5] << 40) + (packet[6] << 48) + (packet[7] << 56);
#endif
				packet += 8;
			}
			break;
		case 'b':
			{
				__int16 size = va_arg(ap, __int16);
				__int64 *mem = va_arg(ap, __int64*);

				CopyMemory(mem, packet, size);
				packet += size;
			}
			break;
#ifdef _DEBUG
		default:
			printf("Disassemble: unknown type %c in %s", t, f);
#endif
		}
	}
	va_end(ap);
	return packet;

//	unguard;
}
