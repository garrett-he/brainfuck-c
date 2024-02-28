vpath %.c ./src/
vpath %.h ./src/

CFLAGS=-Wextra -O3

test_brainfuck.out: test/test_brainfuck.c brainfuck.o stack.o
	cc -o $@ $^

test_stack.out: test/test_stack.c stack.o
	cc -o $@ $^

brainfuck.o: brainfuck.c brainfuck.h
	cc -o $@ -c $<

stack.o: stack.c stack.h
	cc -o $@ -c $<
