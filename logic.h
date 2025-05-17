#ifndef LOGIC_H
#define LOGIC_H

#define GRID_SIZE 4

void initializeGrid(int grid[GRID_SIZE][GRID_SIZE]);
void spawnRandomTile(int grid[GRID_SIZE][GRID_SIZE]);
void moveLeft(int grid[GRID_SIZE][GRID_SIZE]);
void moveRight(int grid[GRID_SIZE][GRID_SIZE]);
void moveUp(int grid[GRID_SIZE][GRID_SIZE]);
void moveDown(int grid[GRID_SIZE][GRID_SIZE]);

#endif
