# 2048 in C (SDL2)

## Overview
This project is a **C implementation of the classic 2048 game** with a graphical interface built using **SDL2**.  
It includes the standard 2048 mechanics, interactive menus, score tracking, multiple difficulty levels, and a multiplayer mode.

## Features

### Core Gameplay
- Classic **2048 gameplay**
- Move tiles using the **arrow keys**
- Merge tiles with the same value
- Generate a new tile after each valid move

### Score System
- Display the **current score**
- Save and display the **highest score**

### User Interface
- Graphical interface built with **SDL2**
- Start screen and interactive menus
- Menu options:
  - Start
  - Instructions
  - Exit

### Game State Detection
- Detects:
  - victory
  - defeat
  - the option to continue after reaching 2048

### Multiplayer Mode
- Two players play in parallel, each with their own board
- Players take turns making moves, similar to a chess clock system
- Each round is limited to **1 minute**
- The winner is the player with the **highest score** at the end of the round

### Difficulty Levels
- **Easy** – 5x5 grid, offering more space for moves
- **Medium** – 4x4 grid, similar to the classic version
- **Hard** – 3x3 grid, with more limited moves
- **Expert** – 2x2 grid, designed for a maximum challenge

## Libraries Used
- **SDL2** – graphical interface and event handling
- **SDL2_ttf** – text rendering for score and interface elements
- **stdlib.h / stdio.h** – standard memory allocation and input/output operations
- **time.h** – random tile generation

## Project Structure
- `main.c` – game initialization and main loop
- `logic.c / logic.h` – implementation of the game rules
- `render.c / render.h` – rendering the board and interface

## Purpose
This project was developed as a graphical and interactive version of 2048 in C, focusing on game logic, rendering, and user interaction using SDL2.
