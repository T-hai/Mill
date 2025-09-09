# Mill (Nine Men's Morris)

A C++ implementation of the classic **Mill game** (Nine Men's Morris).

## Description

This project implements the traditional board game **Mill**, where two players take turns placing and moving their pieces with the goal of forming "mills" (three pieces in a row) to remove the opponent's pieces.  

The game is implemented in **C++**, using multiple classes to manage the board, points, players, and game logic.

## Features

- 7x7 board layout with valid playable points
- Two-player turn-based gameplay
- Detection of mills (horizontal and vertical)
- Ability to remove opponent pieces after forming a mill
- Console-based interface

## Project Structure

- `main.cpp` – main entry point of the game  
- `Board.h` / `Board.cpp` – Board and point management, mill detection  
- `Game.h` / `Game.cpp` – Game logic and player turns  
- `Player.h` / `Player.cpp` – Player class and pieces  
- `Point.h` / `Point.cpp` – Board point representation  

## Requirements

- **C++ compiler** (tested with Visual Studio 2022 and CLion)  
- Standard C++ library  

## Compilation (Windows, Developer Command Prompt)

```cmd
cl /EHsc main.cpp Board.cpp Game.cpp Player.cpp Point.cpp /Fe:mill_game.exe
mill_game.exe
