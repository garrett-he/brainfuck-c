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

#include "../src/stack.h"
#include "minunit.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

extern int errno;

int tests_run = 0;

static char* test_stack_init(void) {
    Stack* stack;

    stack = stack_init();

    mu_assert("error: stack_init() == NULL", stack != NULL);
    mu_assert("error: stack->length != 0", stack->length == 0);
    mu_assert("error: stack->top != NULL", stack->top == NULL);

    return 0;
}

static char* test_stack_push(void) {
    Stack* stack;
    char* str = "testing string";

    stack = stack_init();
    stack_push(stack, str);

    mu_assert("error: stack_push()",  errno == 0);
    mu_assert("error: stack->length != 1", stack->length == 1);
    mu_assert("error: stack->top->data != str", stack->top->data == str);

    return 0;
}

static char* test_stack_pop(void) {
    Stack* stack;
    char* expected = "expected string";
    char* actual;

    stack = stack_init();
    stack_push(stack, expected);

    actual = (char*)stack_pop(stack);

    mu_assert("error: stack_pop() != expected", actual == expected);
    mu_assert("error: stack->length != 0", stack->length == 0);

    return 0;
}

static char* test_stack_free(void) {
    Stack* stack;
    char* str = "testing string";

    stack = stack_init();
    stack_push(stack, str);

    mu_assert("error: stack_free()",  errno == 0);

    return 0;
}

static char* all_tests(void) {
    mu_run_test(test_stack_init);
    mu_run_test(test_stack_push);
    mu_run_test(test_stack_pop);
    mu_run_test(test_stack_free);

    return 0;
}

int main(int argc, char** argv) {
    char* result = all_tests();

    if (result != 0) {
        printf("%s\n", result);
    } else {
        printf("All tests passed\n");
    }

    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
