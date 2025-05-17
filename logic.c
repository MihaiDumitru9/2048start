#include <stdlib.h>
#include "logic.h"

void initializeGrid(int grid[GRID_SIZE][GRID_SIZE]) {
    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            grid[row][col] = 0;
        }
    }
    spawnRandomTile(grid);
    spawnRandomTile(grid);
}

void spawnRandomTile(int grid[GRID_SIZE][GRID_SIZE]) {
    int emptyCells[GRID_SIZE * GRID_SIZE][2];
    int emptyCount = 0;

    for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
            if (grid[row][col] == 0) {
                emptyCells[emptyCount][0] = row;
                emptyCells[emptyCount][1] = col;
                emptyCount++;
            }
        }
    }

    if (emptyCount > 0) {
        int idx = rand() % emptyCount;
        int r = emptyCells[idx][0];
        int c = emptyCells[idx][1];
        
        int randomValue = rand() % 10;
        if (randomValue < 9) {
            grid[r][c] = 2;
        } else {
            grid[r][c] = 4;
        }
    }
    
}

void moveLeft(int grid[GRID_SIZE][GRID_SIZE]) {
    for (int row = 0; row < GRID_SIZE; row++) {
        int lastMergeCol = -1;
        for (int col = 1; col < GRID_SIZE; col++) {
            if (grid[row][col] == 0) continue;
            int targetCol = col;
            while (targetCol > 0 && grid[row][targetCol - 1] == 0) {
                grid[row][targetCol - 1] = grid[row][targetCol];
                grid[row][targetCol] = 0;
                targetCol--;
            }
            if (targetCol > 0 && grid[row][targetCol - 1] == grid[row][targetCol] && lastMergeCol != targetCol - 1) {
                grid[row][targetCol - 1] *= 2;
                grid[row][targetCol] = 0;
                lastMergeCol = targetCol - 1;
            }
        }
    }
}

void moveRight(int grid[GRID_SIZE][GRID_SIZE]) {
    for (int row = 0; row < GRID_SIZE; row++) {
        int lastMergeCol = GRID_SIZE;
        for (int col = GRID_SIZE - 2; col >= 0; col--) {
            if (grid[row][col] == 0) continue;
            int targetCol = col;
            while (targetCol < GRID_SIZE - 1 && grid[row][targetCol + 1] == 0) {
                grid[row][targetCol + 1] = grid[row][targetCol];
                grid[row][targetCol] = 0;
                targetCol++;
            }
            if (targetCol < GRID_SIZE -1 && grid[row][targetCol + 1] == grid[row][targetCol] && lastMergeCol != targetCol +1) {
                grid[row][targetCol + 1] *= 2;
                grid[row][targetCol] = 0;
                lastMergeCol = targetCol +1;
            }
        }
    }
}

void moveUp(int grid[GRID_SIZE][GRID_SIZE]) {
    for (int col = 0; col < GRID_SIZE; col++) {
        int lastMergeRow = -1;
        for (int row =1; row < GRID_SIZE; row++) {
            if (grid[row][col] ==0) continue;
            int targetRow = row;
            while (targetRow >0 && grid[targetRow-1][col]==0) {
                grid[targetRow-1][col]=grid[targetRow][col];
                grid[targetRow][col]=0;
                targetRow--;
            }
            if (targetRow>0 && grid[targetRow-1][col]==grid[targetRow][col] && lastMergeRow != targetRow-1) {
                grid[targetRow-1][col]*=2;
                grid[targetRow][col]=0;
                lastMergeRow = targetRow -1;
            }
        }
    }
}

void moveDown(int grid[GRID_SIZE][GRID_SIZE]) {
    for (int col =0; col<GRID_SIZE; col++) {
        int lastMergeRow =GRID_SIZE;
        for (int row =GRID_SIZE -2; row >=0; row--) {
            if (grid[row][col]==0) continue;
            int targetRow=row;
            while (targetRow<GRID_SIZE -1 && grid[targetRow+1][col]==0) {
                grid[targetRow+1][col]=grid[targetRow][col];
                grid[targetRow][col]=0;
                targetRow++;
            }
            if (targetRow<GRID_SIZE -1 && grid[targetRow+1][col]==grid[targetRow][col] && lastMergeRow != targetRow+1) {
                grid[targetRow+1][col]*=2;
                grid[targetRow][col]=0;
                lastMergeRow =targetRow+1;
            }
        }
    }
}
