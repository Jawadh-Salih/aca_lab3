cmake_minimum_required(VERSION 3.6)
project(aca_lab3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.c
        src/matmat.c
        src/matvec.c
        src/matvec_AUTO.c
        src/util.c
        include/util.h src/sse_methods.c include/sse_methods.h include/matvec_drivers.h src/matvec_drivers.c include/matvec.h include/matmat_drivers.h src/matmat_drivers.c include/matmat.h)

#set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-msse3 -ftree-vectorizer-verbose=2 -ftree-vectorize")
#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-msse3 -ftree-vectorizer-verbose=2 -ftree-vectorize")
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-msse3")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-msse3")
add_executable(aca_lab3 ${SOURCE_FILES})
include_directories(include)
target_link_libraries(aca_lab3 m)