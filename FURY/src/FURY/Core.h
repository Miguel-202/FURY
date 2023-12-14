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

#ifdef FURY_ENABLE_ASSERTS
	#define FURY_ASSERT(x, ...) { if(!(x)) { FURY_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define FURY_CORE_ASSERT(x, ...) { if(!(x)) { FURY_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define FURY_ASSERT(x, ...)
	#define FURY_CORE_ASSERT(x, ...)
#endif

#define BIT_S(x) (1 << x)

#define FURY_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)