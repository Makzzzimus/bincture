#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "decfwrite.h"
#include "os.h"

#define OFFSET_TO_IMAGE_DATA 54           //dec 54 = hex = 36

#define DIB_SIZE 40                       //Always 40
#define COLOR_PLANES 1                    //Always 1
#define BITS_PER_PIXEL 24                 //True color picture (Transparency isn't supported)
#define COMPRESSION_METHOD 0              //None
#define IMAGE_SIZE 0                      //Needed only if compression method is used
#define HORIZONTAL_PIXELS_PER_METER 1800  // =~ 45 ppi. Used for printing
#define VERTICAL_PIXELS_PER_METER 1800    // =~ 45 ppi. Used for printing
#define NUMBER_OF_COLORS 0                //Default value
#define NUMBER_OF_IMPORTANT_COLORS 0      //Every color is important

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

void writePixelFromFile(FILE *userFile, FILE *bmp, int processedPixels){
    char pixel[4] = "\0";
    fseek(userFile, 54 + processedPixels, SEEK_SET);
    for (int i = 0; i < 3; i++){
        fseek(userFile, i, SEEK_CUR);
        pixel[i] = fgetc(userFile);
    }
    swapc(&pixel[0], &pixel[2]);

    fwrite(pixel, sizeof(char), 3, bmp);
    return;
}


int writeHeader(FILE *userFile, FILE *bmp){
    unsigned int userFileSize = 0;

    fseek(userFile, 0, SEEK_END); //Get user's file size
    userFileSize = ftell(userFile);
    rewind(userFile);

    fputs("BM", bmp); //Write BM letters to specify the file format

    fwrite32le(bmp, userFileSize); 

    fwrite32le(bmp, 0); //Write reserved empty bytes

    fwrite32le(bmp, OFFSET_TO_IMAGE_DATA); 

    return userFileSize;
}

void writeDIB(FILE *bmp, int width, int height){
    fwrite32le(bmp, DIB_SIZE);

    fwrite32le(bmp, width);
    fwrite32le(bmp, height);

    fwrite16le(bmp, COLOR_PLANES);
    fwrite16le(bmp, BITS_PER_PIXEL);

    fwrite32le(bmp, COMPRESSION_METHOD);
    fwrite32le(bmp, IMAGE_SIZE);

    fwrite32le(bmp, HORIZONTAL_PIXELS_PER_METER);
    fwrite32le(bmp, VERTICAL_PIXELS_PER_METER);

    fwrite32le(bmp, NUMBER_OF_COLORS);
    fwrite32le(bmp, NUMBER_OF_IMPORTANT_COLORS);

    return;
}

void writeImageDataFromFile(FILE *userFile, FILE *bmp, int userFileSize){
    int unusedPixels = 0;

    if((userFileSize - unusedPixels) % 3 != 0){
        unusedPixels = userFileSize % 3;
    }

    for (unsigned int processedPixels = 0; processedPixels < userFileSize - unusedPixels; processedPixels += 3){
        writePixelFromFile(userFile, bmp, processedPixels);
    }
}


FILE* buildBmpFromFile(char *userPath, int width, int height){
    char userFileName[256] = "\0", bmpPath[256] = "\0";
    unsigned int userFileSize = 0;
    
    FILE *userFile = fopen(userPath, "r");
    if (userFile == NULL){
        puts("Enter the valid path to a file");
        exit(EXIT_FAILURE);
    }
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
    
    (OS == "windows") ? strcpy(bmpPath, ".\\Bincture visualizations\\") : strcpy(bmpPath, "./Bincture visualizations/");

    #ifdef _WIN32
        mkdir(bmpPath);
    #else
        mkdir(bmpPath, 0777);
    #endif

    getFileName(userPath, userFileName); 
    strncat(bmpPath, userFileName, strlen(userFileName));
    strcat(bmpPath, ".bmp");

    FILE *bmp = fopen(bmpPath, "wb"); 

    userFileSize = writeHeader(userFile, bmp);

    writeDIB(bmp, width, height);

    writeImageDataFromFile(userFile, bmp, userFileSize);

    fclose(bmp);
}