# Apollo and Diana Maze Solver

This project involves solving the "Apoollo and Diana" maze problem by modeling it as a graph and implementing an algorithm for traversal in C++.

## Problem Description

The maze problem was inspired by "MAD MAZES: Intriguing Mind Twisters for Puzzle Buffs, Game Nuts and Other Smart People" by Robert Abbott.
It requires navigating a maze of red and blue arrows from the starting position of the upper-left corner of the maze to the bull's-eye in the bottom-right corner of the maze.
The arrow that a person is on indicate the direction in which one is allow move. 
The objective is to find a path from the starting point to the bull's-eye while alternating between red and blue arrows and avoid loops.

## Solution Overview

**How the Problem was Modeled**
* The maze is modeled as a graph, where each arrow represents a vertex.
* Directed edges between vertieces represent valid moves indicated by arrows.
* Each vertex contains information about the arrow's color, direction, position, and neighbors.

**Algorithm Description**
1.  Construct the graph based on the input maze
2.  Perform a Breadth-First Search (BFS) traversal to find the shortest path from the starting point to the bull's-eye.
3.  Write the path that was found to the output file named output.txt.

## Usage
When first running the code the user needs to have the input file ("input.txt") containing the mzae grid and arrow directions in the same directory as the code file.
Compile the code using a C++ compiler.
Run the commands: 
```
g++ project3.cpp -o maze
./maze
```
