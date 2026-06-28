cmake_minimum_required(VERSION 4.2)
project(EDRR_linux)

set(CMAKE_CXX_STANDARD 20)

add_executable(EDRR_linux main.cpp
        edr.functions.h
        source.cpp
        edr.functions.h)
