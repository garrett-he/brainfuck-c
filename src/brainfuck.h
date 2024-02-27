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
#ifndef __BRAINFUCK_H__
#define __BRAINFUCK_H__

typedef struct BrainfuckCell_t {
    unsigned char value;
    struct BrainfuckCell_t* prev;
    struct BrainfuckCell_t* next;
} BrainfuckCell;

typedef struct {
    unsigned int size;
    BrainfuckCell* head;
    BrainfuckCell* ptr;
} BrainfuckTape;

typedef struct BrainfuckInstruction_t {
    char symbol;
    struct BrainfuckInstruction_t* next;
    struct BrainfuckInstruction_t* loop;
} BrainfuckInstruction;

BrainfuckTape* brainfuck_init(void);
void brainfuck_exec(BrainfuckTape*, const char*);

#endif /* __BRAINFUCK_H__ */
