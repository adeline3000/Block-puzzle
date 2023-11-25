# Block Puzzle Game

## Introduction

This repository contains the source code and assets for a Block Puzzle game developed in C using the SDL 1.2 library, as part of our second year in the general computer science license program, we undertook the development of a computer project. Please note that the project structure is maintained as per the existing organization to avoid potential breaking changes.

## Project Structure

    .
    ├── bin/Debug/              # Compiled binary files (avoid modifying this directory)
    ├── obj/Debug/              # Object files generated during compilation (avoid modifying this directory)
    ├── *.dll                   # SDL and related library files (Do not modify or relocate these files)
    ├── *.png, *.ttf            # Image and font assets used in the game
    ├── *.c, *.h                # Source code files for different components of the game
    ├── .cbp, .depend, .layout  #Code::Blocks project files (Do not modify unless familiar with Code::Blocks)
    └── README.md               #Documentation for the project



## Important Notes

- **Deprecation Warning:** This project relies on SDL 1.2. Modifying the project structure may lead to breaking changes.
- Please avoid modifying library files or essential project files unless you are familiar with the consequences.

## Running the Game

To run the game:

1. Ensure the necessary SDL and library files are available.
2. Compile the source code using an appropriate compiler (e.g., Code::Blocks).
3. Run the compiled executable.


## User Guide

### 1. General Overview

The game involves placing pieces of different shapes, randomly appearing on the game board, in a grid to build as many lines or columns as possible. Each piece consists of one or more blocks, and the player's score changes with each placement. The game ends when there is a blockage, meaning the three pieces proposed by the machine cannot be placed on the grid.

![image](https://github.com/adeline3000/Block-puzzle/assets/68406007/6099550c-775e-4c25-97d1-a8fb9ba7690e)

The game also allows players to continue a game, pause the current game, resume it, return to the main menu, or view the list of top scores.

### 2. Gameplay

- Upon starting the game, the player is on the main page, which contains a brief introduction and options to play, watch the machine play, or exit.
  
  ![image](https://github.com/adeline3000/Block-puzzle/assets/68406007/d36d4167-f85d-4f70-b71e-7e2364a5a892) 
  
- Clicking "Play" launches the game, defaulting to the last saved game.
  
  ![image](https://github.com/adeline3000/Block-puzzle/assets/68406007/f14e25a6-77a9-4029-9235-47bfeb134b73)
  ![image](https://github.com/adeline3000/Block-puzzle/assets/68406007/fd7bd7a4-e891-4383-95fb-2e537a2e8b3b)

- During the game, players can click on a piece to move it. The score changes based on the number of blocks in the piece.
- Bonuses are awarded for forming lines or columns: +100 points for one, +300 for two, +600 for three, +1000 for four, and +1500 for five.
- If the three proposed pieces are inaccessible, the game ends. Players can enter their name if their score is among the top five.

  ![image](https://github.com/adeline3000/Block-puzzle/assets/68406007/56f2a495-f4be-41c1-b849-e04e3e83bd9d)


## Programmer's Guide

### 1. Project Files

- `constantes.h`: Global constants definitions.
- `main.c`: Main function file.
- `jeu.c` and `jeu.h`: Functions managing the player and computer parts of the game.
- `menu.c` and `menu.h`: Functions handling all menus.
- `fichiers.c` and `fichiers.h`: Functions managing file reading and writing.
- `score.c` and `score.h`: Functions managing the game score.
- `pieces.c` and `pieces.h`: Functions managing game pieces.

### 2. Key Functions

a. **init_jeu:** Initiates a new game or continues an old one based on the parameter provided.

b. **deplacer_piece:** Moves a piece using the mouse.

c. **verifyplacement:** Checks if there is enough space on the grid to place a piece.

d. **placer_grille:** Places a piece on the grid.

e. **save_jeu** and **charger_jeu:** Save and load the game.

f. **meilleurescor:** Saves the top 5 scores in descending order.

g. **robot:** Enables the computer to play automatically.

### 3. Other Functions

- `bliter_piece` and `bliter_grille`: Display the grid and pieces.
- `affich_rank`: Display the top 5 scores.
- `enter_name`: Allows keyboard input for entering a name.
- `collision`: Prevents a piece from going outside the window.

## Conclusion

This project provided us with the opportunity to understand and experience the various stages of game development, starting with getting acquainted with the SDL library. In addition to being an educational project, it was also enjoyable and gave us a lot of freedom in both code and design.

