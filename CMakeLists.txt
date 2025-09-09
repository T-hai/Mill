cmake_minimum_required(VERSION 3.22)
project(Mill_Game)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Mill_Game
        Board.cpp
        Board.h
        Game.cpp
        Game.h
        main.cpp
        Player.cpp
        Player.h
        Point.cpp
        Point.h)
