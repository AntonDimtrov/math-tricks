# Math-Tricks

This project is a simple two-player board game written in C++ for the **Introduction to Programming Course** at the **Faculty of Mathematics and Informatics, Sofia University**.

## Table of Contents
- [Description](#description)
- [How to Play](#how-to-play)
- [Features](#features)
- [Build and Run](#build-and-run)
- [Game Controls](#game-controls)
- [Saving and Loading](#saving-and-loading)
- [File Structure](#file-structure)
- [Author](#author)

---

## Description
The game is set on a dynamically generated grid-based board where players take turns moving their tokens (P1 and P2) and accumulating points based on arithmetic operations (`+`, `-`, `*`, `/`) on the visited cells. The objective is to achieve the highest score while navigating the board.

## How to Play
1. At the start of the game, players are placed at opposite corners of the board:
   - Player 1 (P1): Top-left corner.
   - Player 2 (P2): Bottom-right corner.
2. Each player takes turns moving to an adjacent or diagonal cell.
3. The player's score is updated based on the operation (`+`, `-`, `*`, `/`) and value on the visited cell.
4. The game ends when a player has no valid moves left.

---

## Features
- **Dynamic Board Generation**: The board is created with arithmetic operations and values, distributed based on distance from the center.
- **Player Scoring**: Each move affects the player’s score based on the operation and value of the visited cell.
- **Turn-Based Play**: Players alternate turns, with the current player highlighted on the board.
- **Save/Load Functionality**: The game state can be saved and resumed from a file.
- **Real-Time Display**: The board is visually updated after every move.
- **Validation**: Prevents invalid moves and ensures game integrity.

---

## Build and Run
### Prerequisites
- A C++ compiler (e.g., Visual Studio, GCC)
- Windows OS (for `windows.h` dependency)

### Instructions
1. Clone the repository:
   ```bash
   git clone <repository_url>
   cd arithmetic-board-game
