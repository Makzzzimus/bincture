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

void linux_strrev(char* string);

// void swapc(char *c1, char *c2);

#ifdef _WIN32
#define OS 'w'
#elif __unix__
#define OS 'u'
#define strrev(string) linux_strrev(string)
#else
#define OS 'n'
#endif