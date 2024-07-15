#include <stdbool.h>


void refreshUI(char32_t matrix[18][85]);

void modifyMatrix(char32_t matrix[18][85], char *string, char row, char column, char maxLength);


void calculatePixels(char (*matrix)[17], int *width, int *height, int fileSize, char bytesPerPixel, bool isAutoResolution);

int setWidth(char (*matrix)[17]);
int setHeight(char (*matrix)[17]);

char setOption(char (*matrix)[17], char digit);

void setTipsNInfo(char (*matrix)[17], char (*strings)[3]);

void setPath(char (*matrix)[17], char *path);