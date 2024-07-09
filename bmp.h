#include <stdio.h>

void writePixelFromFile(FILE, FILE*);

long writeHeader(FILE, FILE*);
void writeDIB(FILE*, int, int);
void writeImageDataFromFile(FILE, FILE*, long);

FILE* buildBmpFromFile(char*, int, int);

