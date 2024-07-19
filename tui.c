#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <uchar.h>
#include "tui.h"
#include "os.h"

#define CHAR_BUFFER_SIZE 4

#define CURSOR_COLOR 208 //Later cursor color will be customizable outside of code

char curRow, curColumn, curLength; //cur - Cursor
bool curSet;

void clear(){
    puts("\e[H\e[2J\e[3J");
}

void updateUI(char32_t matrix[MATRIX_ROWS][MATRIX_COLUMNS]){
    char buffer[CHAR_BUFFER_SIZE] = "\0", outputString[255] = "\0", curANSI[12] = "\0";
    char curEnd = curColumn + curLength;
    sprintf(curANSI, "\033[38;5;%dm", CURSOR_COLOR);

    mbstate_t p;
    #ifdef __linux__
        p.__count = 0;
    #endif

    clear();

    for (char i = 0; i < MATRIX_ROWS; i++){
        for (char j = 0; j < MATRIX_COLUMNS; j++){
            if(curSet){
                if (curRow == i && curColumn == j){
                    strncat(outputString, curANSI, 11);
                }
                else if (curRow == i && curEnd == j){
                    strcat(outputString, "\033[0m");
                }
            }
            size_t result = c32rtomb(buffer, matrix[i][j], &p); //Decoded characters must be written to the buffer, otherwise, strange things can happen...
            strcat(outputString, buffer);

            for (int c = 0; c < CHAR_BUFFER_SIZE; c++){ //Other methods to empty the string such as strcpy didn't work for some reason.
                buffer[c] = '\0';
            }
        }
        puts(outputString);
        outputString[0] = '\0';
    }
}

void modifyMatrix(char32_t matrix[MATRIX_ROWS][MATRIX_COLUMNS], char *string, char row, char column, char maxLength){
    char strLength = strlen(string);
    for (char i = 0; i < maxLength; i++){
        if (strLength > i){
            matrix[row][column + i] = string[i];
        }
        else{
            matrix[row][column + i] = ' ';
        }
    }
}