#include <stdio.h>

#include "conio.h"
#include "cli.h"

#define HEADER_WIDTH 80
#define HEADER_HEIGHT 2 // Change later

const char head[HEADER_HEIGHT][HEADER_WIDTH] = {
    "Logo is under development",
    "========================== Welcome to Bincture v0.1! =========================",
};

void printHead(){
    c_clrscr();

    for (int8_t i = 0; i < HEADER_HEIGHT; i++){
        puts(head[i]);
    }
}