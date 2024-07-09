#include <stdio.h>

//Perhaps I should combine those functions into one. Maybe later

void fwrite16le(FILE *file, short number){ //write short to binary using little-endian
    unsigned char bytes[4] = "\0";
    bytes[0] = number;
    bytes[1] = number >> 8;

    fwrite(bytes, sizeof(bytes), 1, file);
}

void fwrite32le(FILE *file, int number){ //write integer to binary using little-endian
    unsigned char bytes[4] = "\0";
    bytes[0] = number;
    bytes[1] = number >> 8;
    bytes[2] = number >> 16;
    bytes[3] = number >> 24;

    fwrite(bytes, sizeof(bytes), 1, file);
}

void fwrite64le(FILE *file, long number){ //write long to binary using little-endian
    unsigned char bytes[4] = "\0";
    bytes[0] = number;
    bytes[1] = number >> 8;
    bytes[2] = number >> 16;
    bytes[3] = number >> 24;
    bytes[4] = number >> 32;
    bytes[5] = number >> 40;
    bytes[6] = number >> 48;
    bytes[7] = number >> 56;

    fwrite(bytes, sizeof(bytes), 1, file);
}