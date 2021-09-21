cmake_minimum_required(VERSION 3.20)
project(Project_ROW C)

set(CMAKE_C_STANDARD 11)

include_directories(..)

add_executable(Project_ROW
        main.c
        motor.h)
