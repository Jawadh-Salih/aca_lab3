cmake_minimum_required(VERSION 3.6)
project(aca_lab3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        src/matmat.c
        src/matvec.c
        src/matvec_AUTO.c
        src/util.c
        include/util.h)

add_executable(aca_lab3 ${SOURCE_FILES})