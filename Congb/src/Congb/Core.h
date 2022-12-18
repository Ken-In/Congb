#pragma once

#ifdef CB_PLATFORM_WINDOWS
#if CB_DYNAMIC_LINK
	#ifdef CB_BUILD_DLL
		#define CONGB_API __declspec(dllexport)
	#else
		#define CONGB_API __declspec(dllimport)
	#endif // CB_BUILD_DLL
#else
	#define CONGB_API
#endif
#else
	#error Congb only supports Windows!
#endif // CB_PLATFORM_WINDOWS

#ifdef CB_DEBUG
	#define CB_ENABLE_ASSERTS
#endif // CB_DEBUG


#ifdef CB_ENABLE_ASSERTS
	#define CB_ASSERT(x, ...) { if(!(x)) { CB_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define CB_CORE_ASSERT(x, ...) { if(!(x)) { CB_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define CB_ASSERT(x, ...) 
	#define CB_CORE_ASSERT(x, ...) 
#endif // CB_ENABLE_ASSERTS


#define BIT(x) (1 << x)

#define CB_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)