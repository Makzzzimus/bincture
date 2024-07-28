#include <stdio.h>
#include <string.h>

#include "bmp.h"
#include "conio.h"
#include "cli.h"

#define HEADER_WIDTH 80
#define HEADER_HEIGHT 2 // Change later

#define PATH_TIP "Tip: Drag & drop file into the terminal window to quickly insert the path to it.\n"
#define BPP_TIP  "Tip: The bytes per pixel value specifies the color depth and affects the number of pixels in visualization.\n"

#define ASK_PATH_PROMPT "Enter the path to the destination file: "
#define ASK_BPP_PROMPT "Enter the number of bytes per pixel [1, 2, 3]:"

#define INVALID_FILE_ERROR "Error: Invalid file path provided!" //Error code 1
#define LARGE_FILE_ERROR "Error: File is too large or empty! File must be smaller than 4 GB" //Error code 2
#define INVALID_BPP_ERROR "Error: Enter only numbers ranging from 1 to 3!" //Error code 3

int8_t lastError = 0;

const char head[HEADER_HEIGHT][HEADER_WIDTH] = {
    "Logo is under development",
    "========================== Welcome to Bincture v0.1! =========================\n",
};

void printError(int8_t errorCode){
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
    }
    return;
}

void printHead(){
    c_clrscr();

    for (int8_t i = 0; i < HEADER_HEIGHT; i++){
        puts(head[i]);
    }

    if (lastError){
        printError(lastError);

        lastError = 0;
    }
}

unsigned int askPath(char *path){
    unsigned int userFileSize = 0;

    printHead();

    puts(PATH_TIP);
    printf(ASK_PATH_PROMPT);

    fgets(path, 255, stdin);
    //Delete quote signs if user dragged n dropped a file into terminal window
    if (path[0] == '"' || path[0] == '\'')  {path = (path + 1);} 
    for (uint8_t i = 0; i < 2; i++){
        if (path[strlen(path)-1] == '\n' || path[strlen(path)-1] == '"' || path[strlen(path)-1] == '\'')  {path[strlen(path)-1] = '\0';}
    }

    FILE *userFile = fopen(path, "r");
    if (userFile == NULL){
        lastError = 1;

        path[0] = '\0';
        fclose(userFile);
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

    puts(BPP_TIP);
    printf(ASK_BPP_PROMPT);

    int8_t bytesPerPixel = c_getch() - 48;

    if (bytesPerPixel == 0 || bytesPerPixel > 3){
        lastError = 3;
        bytesPerPixel = askBytesPerPixel();
    }
    return bytesPerPixel;
}