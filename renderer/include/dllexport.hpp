#pragma once

#if defined(PLATFORM_WINDOWS)
    #if defined(YSERA_BUILD_SHARED)
        #if defined(YSERA_DLLEXPORT)
            #define YSERA_API __declspec(dllexport)
        #else
            #define YSERA_API __declspec(dllimport)
        #endif
    #endif
#endif

#if not defined(YSERA_API)
    #define YSERA_API
#endif