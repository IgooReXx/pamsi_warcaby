cmake_minimum_required(VERSION 3.25)
project(PAMSIproj3)

set(CMAKE_CXX_STANDARD 17)

add_compile_options(-Wall -Wextra -pedantic)

add_executable(PAMSIproj3 main.cpp
        field.cpp
        field.h
        checkersBoard.cpp
        checkersBoard.h
        piece_char.cpp
        piece_char.h
        possible_moves.cpp
        possible_moves.h
        heuristics_function.cpp
        heuristics_function.h moveTree.cpp moveTree.h
        input_to_move_vector.cpp
        input_to_move_vector.h
        move_vector_to_output.cpp
        move_vector_to_output.h)
