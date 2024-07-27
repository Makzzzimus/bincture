/*  Development of this feature has been discontinued, due to uchar.h and 
*   wchar.h headers are being missed on non-glibc platforms such as Windows. 
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <uchar.h>
#include "conio.h"
#include "tui.h" //All matrix adresses are stored here
#include "os.h"

#define CHAR_BUFFER_SIZE 4

//Characters
#define FIRST_PRINTABLE_CHARACTER 33
#define LAST_PRINTABLE_CHARACTER 126
#ifdef _WIN32
    #define BACKSPACE 8
#elif __linux__
    #define BACKSPACE 127
#endif
#define SPACE 32
#define SPECIAL_KEY 0
#define ESCAPE

#define CURSOR_COLOR 208 //Later, user will be able to change the color of the cursor.

//Cursor variables are only read in updateUI function
uint8_t curRow, curColumn, curLength; //cur - Cursor
bool curSet;

void clear(){
    puts("\e[H\e[2J\e[3J");
}

void updateUI(char32_t matrix[MATRIX_ROWS][MATRIX_COLUMNS]){
    char buffer[CHAR_BUFFER_SIZE] = "\0", outputString[255] = "\0", curANSI[12] = "\0";
    uint8_t curEnd = curColumn + curLength;
    sprintf(curANSI, "\033[38;5;%dm", CURSOR_COLOR);

    mbstate_t p;
    #ifdef __linux__
        p.__count = 0;
    #endif

    clear();

    for (uint8_t i = 0; i < MATRIX_ROWS; i++){
        for (uint8_t j = 0; j < MATRIX_COLUMNS; j++){
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

            for (uint8_t c = 0; c < CHAR_BUFFER_SIZE; c++){ //Other methods to empty the string such as strcpy didn't work for some reason.
                buffer[c] = '\0';
            }
        }
        puts(outputString);
        outputString[0] = '\0';
    }
}

void modifyMatrix(char32_t matrix[MATRIX_ROWS][MATRIX_COLUMNS], char *string, char row, char column, char maxLength){
    uint8_t strLength = strlen(string);
    for (uint8_t i = 0; i < maxLength; i++){
        if (strLength > i){
            matrix[row][column + i] = string[i];
        }
        else{
            matrix[row][column + i] = ' ';
        }
    }
}


void setPath(char32_t matrix[MATRIX_ROWS][MATRIX_COLUMNS], char *path){ //Unfinished
    uint8_t length = 0;
    uint8_t row = 0;
    curRow = PATH_ROW; curColumn = PATH_COLUMN; curLength = PATH_LINE_LENGTH; curSet = true;

    updateUI(matrix);
    while (true){
        char c = c_getch();
        //printf("%d\n", c);

        row = length / PATH_LINE_LENGTH;
        if (length < 225){
            if (c >= FIRST_PRINTABLE_CHARACTER && c <= LAST_PRINTABLE_CHARACTER){
                modifyMatrix(matrix, &c, PATH_ROW + row, PATH_COLUMN + (length - row * PATH_LINE_LENGTH), PATH_LINE_LENGTH - (length - row * PATH_LINE_LENGTH));
                updateUI(matrix);
                length++;
                printf("%d\n", length);
            }
            else if (c == SPECIAL_KEY){
                c_getch(); //Skip second byte of special key's character
            }
            printf("%d\n", c);
        }
        if (c == BACKSPACE && length > 0){
                modifyMatrix(matrix, "", PATH_ROW + row, PATH_COLUMN + (length - row * PATH_LINE_LENGTH) + length - 1, 1);
                updateUI(matrix);
                length--;
                printf("length :%d\n", length);
                printf("row :%d\n", row);
        }
    }
}