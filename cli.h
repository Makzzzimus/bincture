#include <stdint.h>
#include <stdbool.h>



void printHead();


void askPath(char *path);

int8_t askBytesPerPixel();

void askSize(int *width, int *height, int fileSize, uint8_t bytesPerPixel);

bool askThreading();