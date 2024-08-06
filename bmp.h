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

#pragma once

#include <stdio.h>
#include <stdint.h>

unsigned int getFileSize(FILE *userFile);
void getFileName(char* path, char* fileName);

void writeBufferFromFile(FILE *userFile, FILE *bmp, int processedBytes, int bytesLeft, uint8_t bytesPerPixel);

void writeHeader(FILE *userFile, FILE *bmp, unsigned int userFileSize, int lostPixels,  uint8_t bytesPerPixel);
void writeDIB(FILE *bmp, int width, int height, uint8_t bytesPerPixel);
void writePallette(FILE *bmp);
void writeImageDataFromFile(FILE *userFile, FILE *bmp, unsigned int userFileSize, int lostPixels, uint8_t bytesPerPixel);

void buildBmpFromFile(char *userPath, int width, int height, unsigned int userFileSize, int lostPixels, uint8_t bytesPerPixel);

