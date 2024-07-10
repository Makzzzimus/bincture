#include <string.h>

void linux_strrev(char *string){
    char buffer[256];

    strcpy(buffer, string);
    string[0] = '\0';

    for (int chars = 0; chars < strlen(buffer); chars++){
        string[chars] = buffer[strlen(buffer)-1 - chars];
        string[chars+1] = '\0';
    }
}

void swapc(char *c1, char *c2){
    char *temp = c1;
    c1 = c2;
    c2 = temp;
}