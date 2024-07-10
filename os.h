void linux_strrev(char *string);

void swapc(char *c1, char *c2);

#ifdef _WIN32
    #define OS "windows"
#elif __linux__
    #define OS "linux"
    #define strrev(string) linux_strrev(string)
#elif TARGET_OS_MAC 
    #define OS "mac"
#else
    #define OS "unsupported"
#endif