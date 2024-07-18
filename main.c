#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uchar.h>
#ifdef _WIN32
    #include <windows.h>
#elif __linux__
    #include <locale.h>
#endif

#include "bmp.h"
#include "cui.h"

void askPath(char*);
int askWidth();
int askHeight();

int main(){
    char path[255];
    int width = 0, height = 0;

    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        // DWORD consoleMode = 0; //This should enable ANSI escape codes, but it breaks console
        // HANDLE std_out = GetStdHandle(STD_OUTPUT_HANDLE);
        // GetConsoleMode(std_out, &consoleMode);
        //SetConsoleMode(std_out, consoleMode &~ENABLE_VIRTUAL_TERMINAL_PROCESSING); 
    #elif __linux__
        setlocale(LC_ALL, "");
    #endif

    char32_t matrix[MATRIX_ROWS][MATRIX_COLUMNS] = {
        U"┌────────────────────────────────── Status ───────────────────────────────────┐",
        U"│                                                                             │",
        U"└─────────────────────────────────────────────────────────────────────────────┘",
        U"┌ Picture resolution ┐┌───────────────── Additional options ──────────────────┐",
        U"│                    ││ <1> Set picture resolution automatically -------- [y] │",
        U"│ ╭Width╮    Height╮ ││ <2> Use multi-threading to perform visualization  [y] │",
        U"│ │     │    │     │ ││ <3> Use BGR instead of RGB ---------------------- [n] │",
        U"│ ╰─────╯    ╰─────╯ ││ <4> Bytes per pixels ---------------------------- [3] │",
        U"│   <w>        <h>   ││                                                       │",
        U"│                    ││                                                       │",
        U"│                    ││                                                       │",
        U"├────── Pixels ──────┤├───────────────────── Tips & Info ─────────────────────┤",
        U"│ Picture will have  ││ It is recommended to read the user manual before      │",
        U"│ ?      px          ││ proceeding. Press m to open manual.                   │",
        U"│ ?      px are lost ││                                                       │",
        U"└────────────────────┘└───────────────────────────────────────────────────────┘",
        U"┌─────────────────────── <p> Enter the path to a file ────────────────────────┐",
        U"│ _                                                                           │",
        U"│                                                                             │",
        U"│                                                                             │",
        U"└─────────────────────────────────────────────────────────────────────────────┘"
    };

    updateUI(matrix);

    askPath(path);
    // if(path[strlen(path)-1] == '\n'){
    //     path[strlen(path)-1] = '\0';
    // }
    
    // width = askWidth();
    // height = askHeight();

    // buildBmpFromFile(path, width, height);

    return 0;
}

void askPath(char *path){ //rewrite later
    printf("\npath: ");
    fgets(path, 255, stdin);
    printf(path);
}

int askWidth(){ //rewrite later
    char buffer[7];
    int width = 0;
    printf("\nwidth: ");
    fgets(buffer, 7, stdin);
    width = strtol(buffer, NULL, 0);
    //printf(width);
    return width;
}

int askHeight(){ //rewrite later
    char buffer[7];
    int height = 0;
    printf("\nheight: ");
    fgets(buffer, 7, stdin);
    height = strtol(buffer, NULL, 0);
    //printf(height);
    return height;
}