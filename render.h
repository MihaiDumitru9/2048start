#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


#ifndef __RENDER_H__
#define __RENDER_H__

#define GRID_SIZE 4
#define TILE_SIZE 100
#define TILE_PADDING 10

void drawGrid(SDL_Renderer *renderer, int grid[GRID_SIZE][GRID_SIZE], int offsetX, int offsetY);


void drawText(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y);

void cleanup(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font);

void drawMenu(SDL_Renderer *renderer, TTF_Font *font, int selectedOption);

void startGame(SDL_Window **gameWindow, SDL_Renderer **gameRenderer);

#endif