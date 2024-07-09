#include <stdio.h>

void fwrite16le(FILE *file, short number); //write short to binary using little-endian

void fwrite32le(FILE *file, int number); //write integer to binary using little-endian

void fwrite64le(FILE *file, long number); //write long to binary using little-endian