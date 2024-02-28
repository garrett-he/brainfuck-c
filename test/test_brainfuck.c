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

#include "../src/brainfuck.h"
#include "minunit.h"
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

extern int errno;

int tests_run = 0;

static char* test_brainfuck_init(void) {
    BrainfuckTape* tape;

    tape = brainfuck_init();

    mu_assert("error: brainfuck_init() == NULL", tape != NULL);
    mu_assert("error: tape->size != 1", tape->size == 1);
    mu_assert("error: tape->ptr != tape->head", tape->ptr == tape->head);
    mu_assert("error: tape->ptr->value != 0", tape->ptr->value == 0);

    return 0;
}

static char* test_brainfuck_exec(void) {
    BrainfuckTape* tape;

    tape = brainfuck_init();

    brainfuck_exec(tape, "+++++");
    mu_assert("error, tape->ptr->value != 5", tape->ptr->value == 5);

    brainfuck_exec(tape, "--");
    mu_assert("error, tape->ptr->value != 3", tape->ptr->value == 3);

    brainfuck_exec(tape, ">");
    mu_assert("error, tape->size != 2", tape->size == 2);
    mu_assert("error, tape->ptr->value != 0", tape->ptr->value == 0);

    brainfuck_exec(tape, "<");
    mu_assert("error, tape->ptr->value != 3", tape->ptr->value == 3);

    // Should output five '#'
    brainfuck_exec(tape, "++ +++++ +++++ +++++ +++++ +++++ +++++");
    brainfuck_exec(tape, ".....");

    return 0;
}

static char* all_tests(void) {
    mu_run_test(test_brainfuck_init);
    mu_run_test(test_brainfuck_exec);

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
