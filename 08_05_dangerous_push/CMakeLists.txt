cmake_minimum_required(VERSION 3.10)
project(color_tests C)

set(CMAKE_C_STANDARD 11)

add_executable(test
    ./main.c
    ./snekstack.c
    ./exercise.c
    ../munit/munit.c
)

target_include_directories(test PRIVATE
	./
    ../munit
)
