#include <stdint.h>
#include <stdbool.h>

void fgetw(char *buffer, uint8_t maxLength, FILE *file); // Get word from file

void printError(int8_t errorCode);
void printHead();

unsigned int askPath(char *path);
int8_t askBytesPerPixel();
void askSize(int *width, int *height, int fileSize, int8_t bytesPerPixel);
bool askThreading();