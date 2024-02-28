/*
 * Copyright (C) 2019 Garrett HE <garrett.he@hotmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "brainfuck.h"
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

extern int errno;

int main(int argc, char** argv) {
    FILE* fp;
    BrainfuckTape* tape;
    char* str;
    int filelen;

    if (argc < 2) {
        fprintf(stderr, "%s", "usage: bfi [FILE]\n");
        return -1;
    }

    fp = fopen(argv[1], "r");

    if (fp == NULL) {
        return errno;
    }

    fseek(fp, 0, SEEK_END);

    filelen = ftell(fp);
    str = (char*) malloc((filelen + 1) * sizeof(char));
    rewind(fp);

    fread(str, 1, filelen, fp);
    str[filelen] = '\0';

    fclose(fp);

    tape = brainfuck_init();
    brainfuck_exec(tape, str);

    free(str);

    return 0;
}
