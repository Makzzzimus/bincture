/*  Development of this feature has been discontinued, due to uchar.h and 
*   wchar.h headers are being missed on non-glibc platforms such as Windows. 
*/

#include <stdbool.h>

#define MATRIX_ROWS 21
#define MATRIX_COLUMNS 80

#define PATH_ROW 17
#define PATH_COLUMN 2
#define PATH_LINE_LENGTH 75


void updateUI(char32_t matrix[MATRIX_ROWS][MATRIX_COLUMNS]);

void modifyMatrix(char32_t matrix[MATRIX_ROWS][MATRIX_COLUMNS], char *string, char row, char column, char maxLength);


void calculatePixels(char (*matrix)[17], int *width, int *height, int fileSize, char bytesPerPixel, bool isAutoResolution);

int setWidth(char (*matrix)[17]);
int setHeight(char (*matrix)[17]);

char setOption(char (*matrix)[17], char digit);

void setTipsNInfo(char (*matrix)[17], char (*strings)[3]);
void setStatus(char32_t matrix[MATRIX_ROWS][MATRIX_COLUMNS], char *string);

void setPath(char32_t matrix[MATRIX_ROWS][MATRIX_COLUMNS], char *path);