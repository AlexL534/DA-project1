cmake_minimum_required(VERSION 3.27)
project(Water_Supply_Management)

set(CMAKE_CXX_STANDARD 17)

add_executable(Water_Supply_Management
        src/main.cpp
        src/Reservoir.cpp
        src/Reservoir.h
        src/Station.cpp
        src/Station.h
        src/City.cpp
        src/City.h
        src/Pipe.cpp
        src/Pipe.h
        src/parse.cpp
        src/parse.h
)
