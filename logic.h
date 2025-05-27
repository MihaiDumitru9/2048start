#ifndef LOGIC_H
#define LOGIC_H

#include <SDL2/SDL_ttf.h>

#define GRID_SIZE 4
#define wWidth 1600
#define wHeight 720


void initializeGrid(int **grid, int gridSize);
void spawnRandomTile(int **grid, int gridSize);
int moveLeft(int **grid, int size, int *score);
int moveRight(int **grid, int size, int *score);
int moveUp(int **grid, int size, int *score);
int moveDown(int **grid, int size, int *score);
int canMove(int **grid, int gridSize);
void initGrid(int **grid, int size);
void printGrid(int **grid, int size);
int handlePlayerMove(SDL_Keycode key, int **grid, int size, int *score, int isPlayer1);
void runMultiplayerGame(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font);

#endif 
