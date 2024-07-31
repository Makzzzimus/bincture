#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "conio.h"
#include "bmp.h"
#include "decfwrite.h"
#include "os.h"
#include "cli.h"

#define OFFSET_TO_IMAGE_DATA 54           //dec 54 = hex = 36

#define DIB_SIZE 40                       //Always 40
#define COLOR_PLANES 1                    //Always 1
#define COMPRESSION_METHOD 0              //None
#define IMAGE_SIZE 0                      //Needed only if compression method is used
#define HORIZONTAL_PIXELS_PER_METER 0     //Used for printing
#define VERTICAL_PIXELS_PER_METER 0       //Used for printing
#define NUMBER_OF_COLORS 0                //Default value
#define NUMBER_OF_IMPORTANT_COLORS 0      //Every color is important

#define KILOBYTE_SIZE 1024

// Variables prefixed with [user] refer to the user file
// Variables prefixed with [bmp] refer to the visualization file


unsigned int getFileSize(FILE *userFile){
    unsigned int userFileSize = 0;

    fseek(userFile, 0, SEEK_END); //Get user's file size
    userFileSize = ftell(userFile);

    return userFileSize;
}

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

void writePixelFromFile(FILE *userFile, FILE *bmp, int processedBytes, uint8_t bytesPerPixel){
    unsigned char pixel[4] = "\0";
    for (int i = 0; i < bytesPerPixel; i++){
        fseek(userFile, processedBytes + i, SEEK_SET);
        pixel[i] = fgetc(userFile);
    }
    // if (bytesPerPixel > 1){
    //     swapc(&pixel[0], &pixel[bytesPerPixel - 1]);
    // }
    
    fwrite(pixel, sizeof(char), bytesPerPixel, bmp);
    return;
}


void writeHeader(FILE *userFile, FILE *bmp, unsigned int userFileSize, int lostPixels, uint8_t bytesPerPixel){
    fputs("BM", bmp); //Write BM letters to specify the file format

    fwrite32le(bmp, userFileSize - lostPixels * bytesPerPixel + OFFSET_TO_IMAGE_DATA); 

    fwrite32le(bmp, 0); //Write reserved empty bytes

    fwrite32le(bmp, OFFSET_TO_IMAGE_DATA);
}

void writeDIB(FILE *bmp, int width, int height, uint8_t bytesPerPixel){
    fwrite32le(bmp, DIB_SIZE);

    fwrite32le(bmp, width);
    fwrite32le(bmp, height);

    fwrite16le(bmp, COLOR_PLANES);
    fwrite16le(bmp, bytesPerPixel * 8);

    fwrite32le(bmp, COMPRESSION_METHOD);
    fwrite32le(bmp, IMAGE_SIZE);

    fwrite32le(bmp, HORIZONTAL_PIXELS_PER_METER);
    fwrite32le(bmp, VERTICAL_PIXELS_PER_METER);

    fwrite32le(bmp, NUMBER_OF_COLORS);
    fwrite32le(bmp, NUMBER_OF_IMPORTANT_COLORS);

    return;
}

void writeImageDataFromFile(FILE *userFile, FILE *bmp, unsigned int userFileSize, int lostPixels, uint8_t bytesPerPixel){
    int ignoredBytes = 0;
    uint16_t progressPrintCooldown = 0;

    if((userFileSize - ignoredBytes) % bytesPerPixel != 0){
        ignoredBytes = userFileSize % bytesPerPixel;
    }

    for (uint32_t processedBytes = 0; processedBytes < userFileSize - lostPixels * bytesPerPixel - ignoredBytes; processedBytes += bytesPerPixel){
        writePixelFromFile(userFile, bmp, processedBytes, bytesPerPixel);

        if (progressPrintCooldown == KILOBYTE_SIZE * 25){
            printProgress(userFileSize - lostPixels * bytesPerPixel - ignoredBytes, processedBytes);
            progressPrintCooldown = 0;
        }
        else{
            progressPrintCooldown++;
        }
    }
}


void buildBmpFromFile(char *userPath, int width, int height, unsigned int userFileSize, int lostPixels, uint8_t bytesPerPixel){
    char userFileName[256] = "\0", bmpPath[256] = "\0";
    
    FILE *userFile = fopen(userPath, "r");
    if (userFile == NULL){
        printError(-1);
        c_getch();
        exit(EXIT_FAILURE);
    }

    (OS == 'w') ? strcpy(bmpPath, ".\\Bincture visualizations\\") : strcpy(bmpPath, "./Bincture visualizations/");
    #ifdef _WIN32
        mkdir(bmpPath);
    #else
        mkdir(bmpPath, 0777);
    #endif

    getFileName(userPath, userFileName); 
    strncat(bmpPath, userFileName, strlen(userFileName));
    strcat(bmpPath, ".bmp");

    FILE *bmp = fopen(bmpPath, "wb");
    if (bmp == NULL){
        printError(-2);
        c_getch();
        exit(EXIT_FAILURE);
    }

    writeHeader(userFile, bmp, userFileSize, lostPixels, bytesPerPixel);

    writeDIB(bmp, width, height, bytesPerPixel);

    writeImageDataFromFile(userFile, bmp, userFileSize, lostPixels, bytesPerPixel);

    fclose(bmp);

    return;
}