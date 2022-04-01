cmake_minimum_required(VERSION 3.13)

project(HW2_C)

add_compile_options(-Wall -Wextra -pedantic)

set(CMAKE_C_STANDARD 11)
set(THREADS_PREFER_PTHREAD_FLAG ON)

set(SOURCE_DIRECTORY  project/src)
set(INCLUDE_DIRECTORY project/include)

set(CMAKE_CXX_FLAGS "-g -O0 -Wall -Wno-unknown-pragmas -Wno-sign-compare -Wwrite-strings -Wno-unused -Werror -Wpedantic -fprofile-arcs -ftest-coverage")
set(CMAKE_C_FLAGS "-g -O0 -Wall -Wno-unknown-pragmas -Wno-sign-compare -Wwrite-strings -Wno-unused -Werror -Wpedantic -fprofile-arcs -ftest-coverage")
set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )


add_subdirectory(project/tests)

add_library(lib_matrix_one_thread STATIC ${SOURCE_DIRECTORY}/matrix_transpose_one_thread.c)
target_include_directories(lib_matrix_one_thread PUBLIC ${INCLUDE_DIRECTORY})

add_library(lib_matrix_multi_thread STATIC ${SOURCE_DIRECTORY}/matrix_transpose_multi_thread.c)
target_include_directories(lib_matrix_multi_thread PUBLIC ${INCLUDE_DIRECTORY})