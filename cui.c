#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <uchar.h>

#define MATRIX_ROWS 18
#define MATRIX_COLUMNS 85

#define BUFFER_SIZE 4

void clear(){
    puts("\e[H\e[2J\e[3J");
}

void refreshUI(char32_t matrix[MATRIX_ROWS][MATRIX_COLUMNS]){
    mbstate_t p;
    char buffer[4] = "\0", outputString[255] = "\0";

    clear();

    for (char i = 0; i < MATRIX_ROWS; i++){
        for (char j = 0; j < MATRIX_COLUMNS; j++){
            size_t result = c32rtomb(buffer, matrix[i][j], &p); //Decoded characters must be written to the buffer, otherwise, strange things can happen...
            strcat(outputString, buffer);

            for (int c = 0; c < BUFFER_SIZE; c++){ //Other methods to empty the string such as strcpy didn't work for some reason.
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