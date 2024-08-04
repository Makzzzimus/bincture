#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "conio.h"
#include "bmp.h"
#include "cli.h"

#define MEGABYTE_SIZE 1048576.0F

#define HEADER "=========================[ Welcome to Bincture v0.1! ]=========================\n"

#define PATH_TIP "Drag & drop file into the terminal window to quickly insert the path to it.\n"
#define BPP_TIP  "The bytes per pixel value specifies the color depth and affects the number of pixels in visualization. \nNote: Most modern images use 3 Bpp or 4 Bpp. Depending on whether the image can have transparent pixels or not. If the visualization looks strange with a value of 3, try swapping it to 4\n"
#define SIZE_TIP  "The visualization will contain "
#define DIRECTION_TIP "Keep in mind that visualization starts at the bottom of the image."

#define ASK_PATH_PROMPT "Enter the path to the destination file: "
#define ASK_BPP_PROMPT "Enter the number of bytes per pixel [1, 2, 3, 4]: "
#define ASK_SIZE_PROMPT "Enter the size of visualization in following format {Width} {Height} (Both must be <100000). Both variables must be dividable by 4: "
#define ASK_EXIT_PROMPT "\nPress any key to exit the application..."

#define WAIT_WHILE_VISUALIZATION "The process of visualization may take a while to complete..."
#define SUCCESS_VISUALIZATION "The process of visualization has successfully finished. File was saved in current directory in the folder \"Bincture visualizations\""

//Positive error codes refer to errors in CLI input, while negative errors in runtime
#define INVALID_FILE_ERROR "Invalid file path provided!\n"                                  //Error code 1
#define LARGE_FILE_ERROR "File is too large or empty! File must be smaller than 4 GB\n"     //Error code 2
#define INVALID_BPP_ERROR "Enter only numbers ranging from 1 to 3!\n"                       //Error code 3
#define NEGATIVE_SIZE_ERROR "Enter only numbers greater than 0!\n"                          //Error code 4
#define UNDIVIDABLE_SIZE_ERROR "Both width and height values must be dividable by 4!\n"     //Error code 5
#define LARGE_SIZE_ERROR "Visualization can't handle more than 4,294,967,295 bytes!\n"      //Error code 6
#define NO_PALLETTE_ERROR "The pallette.txt file doesn't exist. This file is required to generate 8-bit images. It contains all colors of the image. Download it at github.com/Makzzzimus/bincture/blob/main/pallette.txt or create your own." //Error code 7

#define NO_LONGER_EXISTS_ERROR "\nThe given file doesn't exist anymore or can't be accessed\n"                             //Error code -1
#define CANT_MODIFY_ERROR "\nBincture doesn't have enough privilege level to create and modify files in this directory.\n" //Error code -2
#define MOVED_PALLETTE_ERROR "\nThe pallette.txt file was moved or deleted and can't be accessed"

int8_t lastError = 0;

void fgetw(char *buffer, uint8_t maxLength, FILE *file){
    char temp;
    for (uint8_t i = 0; i < maxLength; i++){
        temp = fgetc(file);
        if (temp == ' ' || temp == '\n' || temp == '\0'){
            return;
        }
        else{
            buffer[i] = temp;
        }
    }
    fgetc(file);
}

void printError(int8_t errorCode){
    c_textcolor(RED);
    printf("Error: ");
    
    switch(errorCode){
        case 1:
            puts(INVALID_FILE_ERROR);
            break;
        case 2:
            puts(LARGE_FILE_ERROR);
            break;
        case 3:
            puts(INVALID_BPP_ERROR);
            break;    
        case 4:
            puts(NEGATIVE_SIZE_ERROR);
            break;    
        case 5:
            puts(UNDIVIDABLE_SIZE_ERROR);
            break; 
        case 6:
            puts(LARGE_SIZE_ERROR);
            break;
        case 7:
            puts(NO_PALLETTE_ERROR);
            break;

        case -1:
            puts(NO_LONGER_EXISTS_ERROR);
            break;
        case -2:
            puts(CANT_MODIFY_ERROR);
            break;  
        case -3:
            puts(MOVED_PALLETTE_ERROR);
            break;  
    }
    c_textcolor(WHITE);
    return;
}
void printTip(char *string){
    c_textcolor(YELLOW);
    
    printf("Tip: ");
    puts(string);

    c_textcolor(WHITE);
    return;
}

void printHead(){
    c_clrscr();

    puts(HEADER);

    if (lastError != 0){
        printError(lastError);

        lastError = 0;
    }
}

unsigned int askPath(char *path){
    unsigned int userFileSize = 0;

    printHead();

    printTip(PATH_TIP);
    printf(ASK_PATH_PROMPT);

    fgets(path, 255, stdin);

    //Delete quote signs if user dragged n dropped a file into terminal window
    if (path[0] == '"' || path[0] == '\'')  {memmove(path, path + 1, strlen(path));} 
    for (uint8_t i = 0; i < 2; i++){
        if (path[strlen(path)-1] == '\n' || path[strlen(path)-1] == '"' || path[strlen(path)-1] == '\'')  {path[strlen(path)-1] = '\0';}
    }

    FILE *userFile = fopen(path, "r");
    if (userFile == NULL){
        lastError = 1;

        path[0] = '\0';
        userFileSize = askPath(path);
        return userFileSize;
    }

    userFileSize = getFileSize(userFile);
    if (userFileSize > UINT32_MAX || userFileSize == 0){
        lastError = 2;

        path[0] = '\0';
        fclose(userFile);
        userFileSize = askPath(path);
        return userFileSize;
    }

    fclose(userFile);
    return userFileSize;
}

int8_t askBytesPerPixel(){
    printHead();

    printTip(BPP_TIP);
    printf(ASK_BPP_PROMPT);

    uint8_t bytesPerPixel = c_getch() - 48;

    if (bytesPerPixel == 0 || bytesPerPixel > 4){
        lastError = 3;
        bytesPerPixel = askBytesPerPixel();
    }
    if (bytesPerPixel == 1){
        FILE *pallette = fopen("./pallette.txt", "r");
        if (pallette == NULL){
            lastError = 7;
            bytesPerPixel = askBytesPerPixel();
        }
        fclose(pallette);
    }
    return bytesPerPixel;
}

void askSize(int *width, int *height, int fileSize, int *lostPixels, int8_t bytesPerPixel){
    int totalPixels = fileSize / bytesPerPixel;
    char widthBuffer[8] = "\0", heightBuffer[8] = "\0";
    unsigned int recWidth1 = 0, recHeight1 = 0, recWidth2 = 128, recHeight2 = 0; //rec - Recommended
    int recLostPixels1 = 0, recLostPixels2 = 0;

    recWidth1 = recHeight1 = (int)floor(sqrt(totalPixels));
    if (recWidth1 % 4){
        recHeight1 = recWidth1 += 4 - (recWidth1 % 4);
    }
    recLostPixels1 = totalPixels - recWidth1 * recHeight1;

    recHeight2 = totalPixels / recWidth2;
    if (recHeight2 % 4){
        recHeight2 += 4 - (recHeight2 % 4);
    }
    recLostPixels2 = totalPixels - recWidth2 * recHeight2;

    printHead();

    char finalTip[512] = "\0", tipBody[325] = "\0";
    strcat(finalTip, SIZE_TIP);
    sprintf(tipBody, "%d pixels. The recommended visualization sizes for this file are %dx%d or %dx%d (for waterfall visualization).. In the first case %d pixels will be lost, in the second case %d pixels will be lost. (If this value is negative, additional white pixels will be added to start of visualization.)\n\n", totalPixels, recWidth1, recHeight1, recWidth2, recHeight2, recLostPixels1, recLostPixels2);
    strcat(finalTip, tipBody);
    printTip(finalTip);

    printf(ASK_SIZE_PROMPT);

    fgetw(widthBuffer, 7, stdin);
    fgetw(heightBuffer, 7, stdin);

    *width = strtol(widthBuffer, NULL, 0);
    *height = strtol(heightBuffer, NULL, 0);

    if (*width <= 0 || *height <= 0){
        lastError = 4;
        fflush(stdin);
        askSize(width, height, fileSize, lostPixels, bytesPerPixel);
        return;
    }
    if (*width % 4 || *height % 4){
        lastError = 5;
        fflush(stdin);
        askSize(width, height, fileSize, lostPixels, bytesPerPixel);
        return;
    }
    uint64_t bytes = (uint64_t)(*width) * (*height) * bytesPerPixel;
    if (bytes > UINT32_MAX){
        lastError = 6;
        fflush(stdin);
        askSize(width, height, fileSize, lostPixels, bytesPerPixel);
        return;
    }

    *lostPixels = totalPixels - *width * *height;
    printf("Visualization size will be %dx%d. In this case, %d pixels will be lost \nContinue with this size? [Y/n]: ", *width, *height, *lostPixels);
    char action = c_getch();
    if (action == 'n'){
        fflush(stdin);
        askSize(width, height, fileSize, lostPixels, bytesPerPixel);
    }
    return;
}

void askExit(){
    printHead();

    c_textcolor(GREEN);
    puts(SUCCESS_VISUALIZATION);
    c_textcolor(WHITE);

    printTip(DIRECTION_TIP);
    puts(ASK_EXIT_PROMPT);
    c_getch();
    exit(EXIT_SUCCESS);
}

void printProgress(int totalBytes, int processedBytes){
    printHead();

    char progressBarFill[26] = ".........................";
    float totalMBytes =  (float)totalBytes / MEGABYTE_SIZE, processedMBytes = (float)processedBytes / MEGABYTE_SIZE,
    percents = processedMBytes / (totalMBytes / 100);

    for(int i = 0; i < percents / 4; i++){
        progressBarFill[i] = '#';
    }
    puts(WAIT_WHILE_VISUALIZATION);
    printf("Visualizing [%s] %.1f MB / %.1f MB | %.1f%%\n", progressBarFill, processedMBytes, totalMBytes, percents);
}