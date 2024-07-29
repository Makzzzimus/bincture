#include <stdio.h>
#include <stdint.h>

unsigned int getFileSize(FILE *userFile);
void getFileName(char* path, char* fileName);

void writePixelFromFile(FILE *userFile, FILE *bmp, int processedPixels, uint8_t bytesPerPixel);

void writeHeader(FILE *userFile, FILE *bmp, unsigned int userFileSize);
void writeDIB(FILE *bmp, int width, int height, uint8_t bytesPerPixel);
void writeImageDataFromFile(FILE *userFile, FILE *bmp, int userFileSize, uint8_t bytesPerPixel);

void buildBmpFromFile(char *userPath, int width, int height, unsigned int userFileSize, uint8_t bytesPerPixel);

