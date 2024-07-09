#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "decfwrite.h"

#define OFFSET_TO_IMAGE_DATA 54 //dec 54 = char 6 = hex = 36. 36 is offset to Image Data

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

int writeHeader(FILE *userFile, FILE *bmp){
    unsigned int userFileSize = 0;

    fseek(userFile, 0, SEEK_END); //Get user's file size
    userFileSize = ftell(userFile);
    rewind(userFile);

    fputs("BM", bmp); //Write BM letters

    fwrite32le(bmp, userFileSize); //Write user's file size

    fwrite32le(bmp, 0); //Write reserved empty bytes

    fputc(OFFSET_TO_IMAGE_DATA, bmp); //Write offset of image data

    return userFileSize;
}

FILE* buildBmpFromFile(char *userPath, int width, int height){
    char userFileName[255] = "\0", bmpPath[255] = ".\\Bincture visualizations\\";
    unsigned int userFileSize = 0;
    
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
    strncat(bmpPath, userFileName, strlen(userFileName));
    strcat(bmpPath, ".bmp");

    FILE *bmp = fopen(bmpPath, "wb"); 
    if (bmp == NULL){
        puts("failure");
    }
    userFileSize = writeHeader(userFile, bmp);

    fclose(bmp); //temporary
}