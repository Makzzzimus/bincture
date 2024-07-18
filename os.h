void linux_strrev(char *string);

void swapc(char *c1, char *c2);

#ifdef _WIN32
    #define OS 'w'
#elif __linux__
    #define OS 'l'
    #define strrev(string) linux_strrev(string)
#elif __APPLE__ 
    #define OS 'm'
#else
    #define OS 'u'
#endif