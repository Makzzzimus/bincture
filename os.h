#ifdef _WIN32
    #define OS "windows"
#elif __linux__
    #define OS "linux"
#elif TARGET_OS_MAC 
    #define OS "mac"
#else
    #define OS "unsupported"
#endif