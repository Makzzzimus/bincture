#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

// Variables prefixed with [user] refer to the user file
// Variables prefixed with [bmp] refer to the visualization file

void getFileName(char* path, char* fileName){
    for (int i = strlen(path); i > 0; i--){ //Find file name
        if(path[i] == '\\' || path[i] == '/'){
            strrev(fileName);
            break;
            return;
        }
        else{
            fileName[strlen(fileName)] = path[i];
        }
    }
}

FILE* buildBmpFromFile(char *userPath, int width, int height){
    char userFileName[255] = "\0", bmpPath[255] = ".\\Bincture visualizations\\";
    long userFileSize = 0;
    
    FILE *userFile = fopen(userPath, "r");
    /*if (OS == "windows"){
        
    }
    else if (OS == "linux") {
        sprintf(bmpPath, "%s/Pictures/Bincture visualizations", getenv("HOME"));
    }
    else if (OS == "mac"){
        
    }
    else{
        puts("Your system is unsupported");
    }
    bmpPath()*/
    
    mkdir(".\\Bincture visualizations\\");

    getFileName(userPath, userFileName); 
    strncat(bmpPath, userFileName, strlen(userFileName) - 1);
    strcat(bmpPath, ".bmp");

    FILE *bmp = fopen(bmpPath, "a"); 
    if (bmp == NULL){
        puts("failure");
    }
}