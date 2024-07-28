#include <stdio.h>

unsigned int getFileSize(FILE *userFile);
void getFileName(char* path, char* fileName);

void writePixelFromFile(FILE *userFile, FILE *bmp, int processedPixels);

void writeHeader(FILE *userFile, FILE *bmp, unsigned int userFileSize);
void writeDIB(FILE *bmp, int width, int height);
void writeImageDataFromFile(FILE *userFile, FILE *bmp, int userFileSize);

FILE* buildBmpFromFile(char *userPath, int width, int height, unsigned int userFileSize);

