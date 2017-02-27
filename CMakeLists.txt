cmake_minimum_required(VERSION 3.6)
project(aca_lab3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        matmat.c
        matvec.c
        matvec_AUTO.c
        util.c
        util.h)

add_executable(aca_lab3 ${SOURCE_FILES})