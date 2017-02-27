cmake_minimum_required(VERSION 3.6)
project(aca_lab3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.c
        src/matmat.c
        src/matvec.c
        src/matvec_AUTO.c
        src/util.c
        include/util.h)
set(SSE_FLAG -msse3)
set(CMAKE_CXX_FLAGS ${SSE_FLAGS})
set(CMAKE_C_FLAGS ${SSE_FLAGS})
add_executable(aca_lab3 ${SOURCE_FILES})
target_link_libraries(aca_lab3 m)