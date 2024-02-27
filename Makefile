vpath %.c ./src/
vpath %.h ./src/

CFLAGS=-Wextra -O3

test_stack.out: test/test_stack.c stack.o
	cc -o $@ $^

stack.o: stack.c stack.h
	cc -o $@ -c $<
