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

// Perhaps I should combine those functions into one. Maybe later

void fwrite16le(FILE* file, short number) {  // write short to binary using little-endian
  unsigned char bytes[2] = "\0";
  bytes[0] = number;
  bytes[1] = number >> 8;

  fwrite(bytes, sizeof(bytes), 1, file);
}

void fwrite32le(FILE* file, int number) {  // write integer to binary using little-endian
  unsigned char bytes[4] = "\0";
  bytes[0] = number;
  bytes[1] = number >> 8;
  bytes[2] = number >> 16;
  bytes[3] = number >> 24;

  fwrite(bytes, sizeof(bytes), 1, file);
}

// void fwrite64le(FILE *file, long number){ //write long to binary using little-endian
//     unsigned char bytes[8] = "\0";
//     bytes[0] = number;
//     bytes[1] = number >> 8;
//     bytes[2] = number >> 16;
//     bytes[3] = number >> 24;
//     bytes[4] = number >> 32;
//     bytes[5] = number >> 40;
//     bytes[6] = number >> 48;
//     bytes[7] = number >> 56;

//     fwrite(bytes, sizeof(bytes), 1, file);
// }