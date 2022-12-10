#pragma once

#ifdef CB_PLATFORM_WINDOWS
	#ifdef CB_BUILD_DLL
		#define CONGB_API __declspec(dllexport)
	#else
		#define CONGB_API __declspec(dllimport)
	#endif // CB_BUILD_DLL
#else
	#error Congb only supports Windows!
#endif // CB_PLATFORM_WINDOWS

#ifdef CB_ENABLE_ASSERTS
	#define CB_ASSERT(x, ...) { if(!(x)) { CB_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define CB_CORE_ASSERT(x, ...) { if(!(x)) { CB_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define CB_ASSERT(x, ...) 
	#define CB_CORE_ASSERT(x, ...) 
#endif // CB_ENABLE_ASSERTS


#define BIT(x) (1 << x)