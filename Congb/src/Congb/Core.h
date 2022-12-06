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
