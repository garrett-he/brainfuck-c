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

#include <stdlib.h>
#include <errno.h>
#include "stack.h"

extern int errno;

Stack* stack_init(void) {
    Stack* stack;

    errno = 0;
    stack = (Stack*) malloc(sizeof(Stack));

    if (stack == NULL) {
        return NULL;
    }

    stack->length = 0;
    stack->top = NULL;

    return stack;
}

void stack_push(Stack* stack, void* data) {
    StackElement* el;

    errno = 0;
    el = (StackElement*) malloc(sizeof(StackElement));

    if (el == NULL) {
        return;
    }

    el->data = data;
    el->prev = stack->top;
    stack->top = el;

    stack->length++;
}

void* stack_pop(Stack* stack) {
    StackElement* el;
    void* data;

    if (stack->length == 0) {
        errno = EFAULT;
        return NULL;
    }

    el = stack->top;
    data = el->data;

    stack->top = stack->top->prev;

    free(el);
    stack->length--;

    return data;
}

void stack_free(Stack* stack) {
    StackElement* el;

    while (stack->top) {
        el = stack->top;
        stack->top = stack->top->prev;
        free(el);
    }
}
