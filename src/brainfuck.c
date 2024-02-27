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
#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

extern int errno;

static BrainfuckInstruction* parse_string(const char* str);
static void free_inst(BrainfuckInstruction*);

BrainfuckTape* brainfuck_init(void) {
    BrainfuckTape* tape;

    tape = (BrainfuckTape*) malloc(sizeof(BrainfuckTape));

    if (tape == NULL) {
        return NULL;
    }

    tape->ptr = tape->head = (BrainfuckCell*) malloc(sizeof(BrainfuckCell));

    if (tape->ptr == NULL) {
        free(tape);
        return NULL;
    }

    tape->ptr->value = 0;
    tape->ptr->prev = tape->ptr->next = NULL;
    tape->size = 1;

    return tape;
}

void brainfuck_exec(BrainfuckTape* tape, const char* str) {
    BrainfuckInstruction* inst;
    BrainfuckInstruction* ip;
    inst = ip = parse_string(str);

    while (ip) {
        switch (ip->symbol) {
            case '+':
                tape->ptr->value++;
                break;
            case '-':
                tape->ptr->value--;
                break;
            case '<':
                if (tape->ptr == tape->head) {
                    errno = EACCES;
                    goto exec_cleanup;
                }

                tape->ptr = tape->ptr->prev;
                break;
            case '>':
                if (tape->ptr->next == NULL) {
                    tape->ptr->next = (BrainfuckCell*) malloc(sizeof(BrainfuckCell));
                    tape->ptr->next->prev = tape->ptr;
                    tape->ptr->next->value = 0;
                    tape->ptr->next->next = NULL;
                    tape->size++;
                }

                tape->ptr = tape->ptr->next;
                break;
            case '.':
                fprintf(stdout, "%c", tape->ptr->value);
                break;
            case '[':
                if (tape->ptr->value == 0) {
                    ip = ip->loop;
                }
                break;
            case ']':
                if (tape->ptr->value != 0) {
                    ip = ip->loop;
                }
                break;
        }

        ip = ip->next;
    }

    exec_cleanup:
    free_inst(inst);
}


static BrainfuckInstruction* parse_string(const char* str) {
    BrainfuckInstruction *head, *tail, *inst;
    Stack* stack;

    stack = stack_init();

    head = tail = (BrainfuckInstruction*) malloc(sizeof(BrainfuckInstruction));

    while (*str) {
        tail->next = (BrainfuckInstruction*) malloc(sizeof(BrainfuckInstruction));
        tail->next->symbol = *str;
        tail->next->next = NULL;

        tail = tail->next;

        str++;

        switch (tail->symbol) {
            case '[':
                stack_push(stack, tail);
                break;
            case ']':
                inst = (BrainfuckInstruction*)stack_pop(stack);
                inst->loop = tail;
                tail->loop = inst;
                break;
        }
    }

    inst = head->next;
    free(head);

    return inst;
}


static void free_inst(BrainfuckInstruction* inst) {
    BrainfuckInstruction* ptr;

    while (inst) {
        ptr = inst;
        inst = inst->next;
        free(ptr);
    }
}
