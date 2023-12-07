#pragma once

#ifdef FURY_PLATFORM_WINDOWS
	#ifdef FURY_BUILD_DLL
		#define FURY_API __declspec(dllexport)
	#else
		#define FURY_API __declspec(dllimport)
	#endif
#else
	#error FURY only supports Windows!
#endif

#define BIT_S(x) (1 << x)