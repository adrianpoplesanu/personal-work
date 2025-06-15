cmake_minimum_required(VERSION 3.31)
project(lox2 C)

set(CMAKE_C_STANDARD 11)

add_executable(lox2 main.c chunk.c memory.c debug.c value.c vm.c compiler.c scanner.c)
