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

#include <string.h>

void linux_strrev(char *string){
    char buffer[256];

    strcpy(buffer, string);
    string[0] = '\0';

    for (int chars = 0; chars < strlen(buffer); chars++){
        string[chars] = buffer[strlen(buffer)-1 - chars];
        string[chars+1] = '\0';
    }
}

// void swapc(char *c1, char *c2){
//     char *temp = c1;
//     c1 = c2;
//     c2 = temp;
// }