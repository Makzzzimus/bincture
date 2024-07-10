#include <stdio.h>

void writePixelFromFile(FILE *userFile, FILE *bmp, int processedPixels);

int writeHeader(FILE *userFile, FILE *bmp);
void writeDIB(FILE *bmp, int width, int height);
void writeImageDataFromFile(FILE *userFile, FILE *bmp, int userFileSize);

FILE* buildBmpFromFile(char *userPath, int width, int height);

