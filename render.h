#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>


#ifndef __RENDER_H__
#define __RENDER_H__



void drawText(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y);

void cleanup(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font);

void drawMenu(SDL_Renderer *renderer, TTF_Font *font, int selectedOption);

void startGame(SDL_Window **gameWindow, SDL_Renderer **gameRenderer);

#endif
