cmake_minimum_required(VERSION 3.0.0)
project(fib)


add_subdirectory(input)
add_subdirectory(add)
add_subdirectory(food)
#link_directories("input" "add" "food")



message("FIB_LIB_INCLUDE_DIRS = ${FIB_LIB_INCLUDE_DIRS}")
message("FIB_LIB_LIBRARIES = ${FIB_LIB_LIBRARIES}")

add_executable(${PROJECT_NAME} main.c)
include_directories(food input add)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -coverage -lgcov" )

target_include_directories(${PROJECT_NAME} PUBLIC ${FIB_LIB_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${FIB_LIB_LIBRARIES})

add_subdirectory(test)
