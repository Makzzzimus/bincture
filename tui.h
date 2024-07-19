#include <stdbool.h>

#define MATRIX_ROWS 21
#define MATRIX_COLUMNS 80

void updateUI(char32_t matrix[MATRIX_ROWS][MATRIX_COLUMNS]);

void modifyMatrix(char32_t matrix[MATRIX_ROWS][MATRIX_COLUMNS], char *string, char row, char column, char maxLength);


void calculatePixels(char (*matrix)[17], int *width, int *height, int fileSize, char bytesPerPixel, bool isAutoResolution);

int setWidth(char (*matrix)[17]);
int setHeight(char (*matrix)[17]);

char setOption(char (*matrix)[17], char digit);

void setTipsNInfo(char (*matrix)[17], char (*strings)[3]);
void setStatus(char32_t matrix[MATRIX_ROWS][MATRIX_COLUMNS], char *string);

void setPath(char (*matrix)[17], char *path);