cmake_minimum_required(VERSION 3.6)
project(brainfuck)

set(SOURCE_FILES src/stack.c src/brainfuck.c src/bfi.c)
add_executable(bfi.out ${SOURCE_FILES})
