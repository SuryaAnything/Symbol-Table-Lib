cmake_minimum_required(VERSION 3.28)
project(SymbolTable C)

set(CMAKE_C_STANDARD 11)

add_executable(SymbolTable main.c
        symbol.h
        symbol.c)
