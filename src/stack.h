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
#ifndef __STACK_H__
#define __STACK_H__

typedef struct StackElement_t {
    struct StackElement_t* prev;
    void* data;
} StackElement;

typedef struct {
    unsigned int length;
    StackElement* top;
} Stack;

Stack* stack_init(void);

void stack_push(Stack*, void*);

void* stack_pop(Stack*);

void stack_free(Stack*);

#endif /* __STACK_H__ */
