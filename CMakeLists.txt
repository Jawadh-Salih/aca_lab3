cmake_minimum_required(VERSION 3.5)
project(aca_lab3)
set(CMAKE_BUILD_TYPE Release)
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
set(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} "-msse4.1 -O0 -Wall")
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-msse4.1 -O0 -Wall")
#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-msse3 -march=native -O0 -Wall")
#set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-msse3 -mcmodel=large -O0 -Wall")
set_source_files_properties(src/matvec_auto.c PROPERTIES COMPILE_FLAGS "-ftree-vectorizer-verbose=4 -ftree-vectorize")
set_source_files_properties(src/matmat_auto.c PROPERTIES COMPILE_FLAGS "-ftree-vectorizer-verbose=4 -ftree-vectorize")
add_executable(aca_lab3 ${SOURCE_FILES})
target_link_libraries(aca_lab3 m)

include(CTest)
enable_testing()
# Does application run
add_test(aca_lab3Dorun aca_lab3 -h)
set_tests_properties(aca_lab3Dorun PROPERTIES PASS_REGULAR_EXPRESSION "Show this menu")

add_test(aca_lab3{mt4} aca_lab3 -n 4 -mt)
set_tests_properties(aca_lab3{mt4} PROPERTIES PASS_REGULAR_EXPRESSION "(7 SSE mxm.*verified.*listing 7 C.*- OK).*(7 auto.*verified.*listing 7 C.*- OK)")

add_test(aca_lab3vt4 aca_lab3 -n 4 -vt)
set_tests_properties(aca_lab3vt4 PROPERTIES PASS_REGULAR_EXPRESSION "(SSE.*version verified against listing 5 C Program - OK)\
.*(Listing 6 C Program verified against listing 5 C Program - OK)\
.*(Auto vectorized version verified against simple version - OK)")
set(CTEST_PARALLEL_LEVEL 3)
