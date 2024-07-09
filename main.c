#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"


void askPath(char*);
int askWidth();
int askHeight();

int main(){
    char path[255];
    int width = 0, height = 0;
    askPath(path);
    //width = askWidth();
    //height = askHeight();

    buildBmpFromFile(path, 500, 500);

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