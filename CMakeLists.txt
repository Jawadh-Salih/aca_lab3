cmake_minimum_required(VERSION 3.5)
project(aca_lab3)

#set(CMAKE_CXX_STANDARD 11)

include_directories(include)

set(SOURCE_FILES main.c
        src/main_drivers.c include/main_drivers.h
        src/matmat.c include/matmat.h
        src/util.c include/util.h
        src/matvec.c include/matvec.h
        src/sse_methods.c include/sse_methods.h
        src/matvec_auto.c include/matvec_auto.h
        src/matmat_auto.c include/matmat_auto.h)

#set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-msse3 -ftree-vectorizer-verbose=2 -ftree-vectorize")
#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-msse3 -ftree-vectorizer-verbose=2 -ftree-vectorize")
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-msse3 -march=native -O3 -Wall")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-msse3 -march=native -O3 -Wall")
#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-msse3 -mcmodel=large")

#set_source_files_properties(src/matvec_auto.c PROPERTIES COMPILE_FLAGS -ftree-vectorize)
#set_source_files_properties(include/matvec_auto.h PROPERTIES COMPILE_FLAGS -ftree-vectorize)
#set_source_files_properties(src/matmat_auto.c PROPERTIES COMPILE_FLAGS ftree-vectorize)
add_executable(aca_lab3 ${SOURCE_FILES})
target_link_libraries(aca_lab3 m)
