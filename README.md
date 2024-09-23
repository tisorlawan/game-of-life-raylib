# game-of-life-raylib

https://github.com/user-attachments/assets/47d1bbf0-e72a-4a4f-b97b-e7359b6ea75c



This project is an implementation of Conway's Game of Life using C and the Raylib library.

It is one of my project on my journey learning C and Raylib.

## Features

- 100x100 grid simulation
- Toroidal grid implementation
- Gosper Glider Gun placements
- Random noise generation
- Periodic disturbances to maintain activity
- Interactive cell toggling
- Pause/Resume functionality

## Prerequisites

Before you begin, ensure you have met the following requirements:

- You have installed the latest version of [GCC](https://gcc.gnu.org/) or any C compiler
- You have installed [Raylib](https://www.raylib.com/)
  For statically built raylib, see the [Makefile](./Makefile).

## Installing Game of Life Simulation

To install the Game of Life Simulation, follow these steps:

1. Clone the repository
   ```
   git clone https://github.com/tisorlawan/game-of-life.git
   ```
2. Navigate to the project directory
   ```
   cd game-of-life
   ```
3. Compile the program
   ```
   gcc -o game_of_life main.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
   ```

## Using Game of Life Simulation

To use the Game of Life Simulation, follow these steps:

1. Run the compiled program
   ```
   ./game_of_life
   ```
2. The simulation will start automatically
3. Use the following controls:
   - Click on cells to toggle them on/off
   - Press SPACE to pause/resume the simulation
   - Press D to introduce a random disturbance
   - Press Q to quit the program
