#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>



void drawText(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y);
void drawMenu(SDL_Renderer *renderer, TTF_Font *font, int selectedOption);
void drawGameOver(SDL_Renderer *renderer, TTF_Font *font);
void startGame(SDL_Window **gameWindow, SDL_Renderer **gameRenderer, int gridSize);
void renderGrid(SDL_Renderer *renderer, TTF_Font *font, int **grid, int gridSize, int gridDrawX, int gridDrawY, int score, const char *playerName); // MODIFIED
void cleanup(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font);

#endif 