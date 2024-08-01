#pragma once

#include <stdio.h>
#include <stdint.h>

unsigned int getFileSize(FILE *userFile);
void getFileName(char* path, char* fileName);

void writePixelFromFile(FILE *userFile, FILE *bmp, int processedBytes, uint8_t bytesPerPixel);

void writeHeader(FILE *userFile, FILE *bmp, unsigned int userFileSize, int lostPixels,  uint8_t bytesPerPixel);
void writeDIB(FILE *bmp, int width, int height, uint8_t bytesPerPixel);
void writePallette(FILE *bmp);
void writeImageDataFromFile(FILE *userFile, FILE *bmp, unsigned int userFileSize, int lostPixels, uint8_t bytesPerPixel);

void buildBmpFromFile(char *userPath, int width, int height, unsigned int userFileSize, int lostPixels, uint8_t bytesPerPixel);

