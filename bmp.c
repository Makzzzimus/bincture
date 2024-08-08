/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * Author: Makzzzimus
 * Date: 2024
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "bmp.h"
#include "cli.h"
#include "conio.h"
#include "decfwrite.h"
#include "os.h"

#define OFFSET_TO_IMAGE_DATA 54  // dec 54 = hex = 36

#define DIB_SIZE 40                    // Always 40
#define COLOR_PLANES 1                 // Always 1
#define COMPRESSION_METHOD 0           // None
#define IMAGE_SIZE 0                   // Needed only if compression method is used
#define HORIZONTAL_PIXELS_PER_METER 0  // Used for printing
#define VERTICAL_PIXELS_PER_METER 0    // Used for printing
#define NUMBER_OF_COLORS 0             // Default value
#define NUMBER_OF_IMPORTANT_COLORS 0   // Every color is important

#define KILOBYTE_SIZE 1024
#define BUFFER_SIZE (KILOBYTE_SIZE * 1024)

// Variables prefixed with [user] refer to the user file
// Variables prefixed with [bmp] refer to the visualization file

static unsigned char buffer[BUFFER_SIZE] = "\0";

unsigned int getFileSize(FILE* userFile) {
  unsigned int userFileSize = 0;

  fseek(userFile, 0, SEEK_END);  // Get user's file size
  userFileSize = ftell(userFile);

  return userFileSize;
}

void getFileName(char* path, char* fileName) {
  bool relativePath = true;
  for (int i = strlen(path); i > -1; i--) {  // Find file name
    if (path[i] == '\\' || path[i] == '/') {
      strrev(fileName);
      relativePath = false;
      break;
      return;
    } else {
      fileName[strlen(fileName)] = path[i];
    }
  }
  if (relativePath) {
    strrev(fileName);
    return;
  }
}

void writeBufferFromFile(FILE* userFile, FILE* bmp, int processedBytes, int bytesLeft, uint8_t bytesPerPixel) {
  fseek(userFile, processedBytes, SEEK_SET);
  fread(buffer, BUFFER_SIZE, 1, userFile);

  fwrite(buffer, bytesLeft < BUFFER_SIZE ? bytesLeft : BUFFER_SIZE, 1, bmp);
  return;
}

void writeHeader(FILE* userFile, FILE* bmp, unsigned int userFileSize, int lostPixels, uint8_t bytesPerPixel) {
  fputs("BM", bmp);  // Write BM letters to specify the file format

  short palletteSize = bytesPerPixel == 1 ? 1024 : 0;
  uint8_t ignoredBytes =
      (userFileSize - lostPixels * bytesPerPixel + OFFSET_TO_IMAGE_DATA + palletteSize) % bytesPerPixel;
  fwrite32le(bmp, userFileSize - lostPixels * bytesPerPixel + OFFSET_TO_IMAGE_DATA + palletteSize - ignoredBytes);

  fwrite32le(bmp, 0);  // Write reserved empty bytes

  fwrite32le(bmp, OFFSET_TO_IMAGE_DATA);
}

void writeDIB(FILE* bmp, int width, int height, uint8_t bytesPerPixel) {
  fwrite32le(bmp, DIB_SIZE);

  fwrite32le(bmp, width);
  fwrite32le(bmp, height);

  fwrite16le(bmp, COLOR_PLANES);
  fwrite16le(bmp, bytesPerPixel * 8);

  fwrite32le(bmp, COMPRESSION_METHOD);
  fwrite32le(bmp, IMAGE_SIZE);

  fwrite32le(bmp, HORIZONTAL_PIXELS_PER_METER);
  fwrite32le(bmp, VERTICAL_PIXELS_PER_METER);

  fwrite32le(bmp, NUMBER_OF_COLORS);
  fwrite32le(bmp, NUMBER_OF_IMPORTANT_COLORS);

  return;
}

void writePallette(FILE* bmp) {
  FILE* pallette = fopen("./pallette.txt", "r");
  if (pallette == NULL) {
    printError(-3);
    c_getch();
    exit(EXIT_FAILURE);
  }

  for (int i = 0; i < KILOBYTE_SIZE; i++) {
    char digits[4] = "\0";
    fgetw(digits, 3, pallette);
    unsigned char byte = strtol(digits, NULL, 0);
    fwrite(&byte, 1, 1, bmp);
  }
  fclose(pallette);
}

void writeImageDataFromFile(FILE* userFile,
                            FILE* bmp,
                            unsigned int userFileSize,
                            int lostPixels,
                            uint8_t bytesPerPixel) {
  int ignoredBytes = 0;
  uint16_t progressBarCooldown = 0;

  if ((userFileSize - ignoredBytes) % bytesPerPixel != 0) {
    ignoredBytes = userFileSize % bytesPerPixel;
  }

  for (uint32_t processedBytes = 0; processedBytes < userFileSize - lostPixels * bytesPerPixel - ignoredBytes;
       processedBytes += BUFFER_SIZE) {
    writeBufferFromFile(userFile, bmp, processedBytes,
                        (userFileSize - lostPixels * bytesPerPixel - ignoredBytes) - processedBytes, bytesPerPixel);

    if (progressBarCooldown == 64) {
      printProgress(userFileSize - lostPixels * bytesPerPixel - ignoredBytes, processedBytes);
      progressBarCooldown = 0;
    } else {
      progressBarCooldown++;
    }
  }
}

void buildBmpFromFile(char* userPath,
                      int width,
                      int height,
                      unsigned int userFileSize,
                      int lostPixels,
                      uint8_t bytesPerPixel) {
  char userFileName[256] = "\0", bmpPath[256] = "\0";

  FILE* userFile = fopen(userPath, "r");
  if (userFile == NULL) {
    printError(-1);
    c_getch();
    exit(EXIT_FAILURE);
  }

  (OS == 'w') ? strcpy(bmpPath, ".\\Bincture visualizations\\") : strcpy(bmpPath, "./Bincture visualizations/");
#ifdef _WIN32
  mkdir(bmpPath);
#else
  mkdir(bmpPath, 0777);
#endif

  getFileName(userPath, userFileName);
  strcat(bmpPath, userFileName);
  strcat(bmpPath, ".bmp");

  FILE* bmp = fopen(bmpPath, "wb");
  if (bmp == NULL) {
    printError(-2);
    c_getch();
    exit(EXIT_FAILURE);
  }

  writeHeader(userFile, bmp, userFileSize, lostPixels, bytesPerPixel);

  writeDIB(bmp, width, height, bytesPerPixel);

  if (bytesPerPixel == 1) {
    writePallette(bmp);
  }

  printProgress(userFileSize - lostPixels * bytesPerPixel, 0);
  writeImageDataFromFile(userFile, bmp, userFileSize, lostPixels, bytesPerPixel);

  fclose(userFile);
  fclose(bmp);

  return;
}