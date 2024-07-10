#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"


void askPath(char*);
int askWidth();
int askHeight();

int main(){
    char path[255];
    int width = 0, height = 0;
    askPath(path);
    if(path[strlen(path)-1] == '\n'){
        path[strlen(path)-1] = '\0';
    }
    width = askWidth();
    height = askHeight();

    buildBmpFromFile(path, width, height);

    return 0;
}

void askPath(char *path){ //rewrite later
    printf("\npath: ");
    fgets(path, 255, stdin);
    printf(path);
}

int askWidth(){ //rewrite later
    char buffer[7];
    int width = 0;
    printf("\nwidth: ");
    fgets(buffer, 7, stdin);
    width = strtol(buffer, NULL, 0);
    //printf(width);
    return width;
}

int askHeight(){ //rewrite later
    char buffer[7];
    int height = 0;
    printf("\nheight: ");
    fgets(buffer, 7, stdin);
    height = strtol(buffer, NULL, 0);
    //printf(height);
    return height;
}