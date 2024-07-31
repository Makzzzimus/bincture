#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
#elif __linux__
    #include <locale.h>
#endif

#include "conio.h"
#include "bmp.h"
#include "cli.h"
//#include "tui.h"

int main(){
    char path[255];
    signed int lostPixels = 0;
    unsigned int userFileSize = 0, width = 0, height = 0;
    uint8_t bytesPerPixel = 0;

    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #elif __linux__
        setlocale(LC_ALL, "");
    #endif

    /* //TUI driver
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

    int action = c_getch();
    switch (action){
    case 'p':
        setPath(matrix, path);
        break;           
    default:
        break;
    }*/
    c_textcolor(WHITE);

    userFileSize = askPath(path);

    bytesPerPixel = askBytesPerPixel();

    askSize(&width, &height, userFileSize, &lostPixels, bytesPerPixel);

    buildBmpFromFile(path, width, height, userFileSize, lostPixels, bytesPerPixel);

    askExit();

    return 0;
}