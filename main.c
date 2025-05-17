#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "render.h"

#define wWidth 1600
#define wHeight 720


int initSDL(SDL_Window **window, SDL_Renderer **renderer, TTF_Font **font) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("Eroare la inițializarea SDL: %s\n", SDL_GetError());
        return -1;
    }

    if (TTF_Init() != 0) {
        printf("Eroare la inițializarea SDL_ttf: %s\n", TTF_GetError());
        SDL_Quit();  
        return -1;
    }

    *window = SDL_CreateWindow("2048 Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, wWidth, wHeight, SDL_WINDOW_SHOWN);
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);

    *font = TTF_OpenFont("font1.ttf", 24); 

    if (*font == NULL) {
        printf("Eroare la încărcarea fontului: %s\n", TTF_GetError());
        SDL_DestroyRenderer(*renderer);
        SDL_DestroyWindow(*window);
        TTF_Quit();
        SDL_Quit();  
        return -1;  
    }

    return 0;
}

int handleEvents(SDL_Event *event, int *selectedOption, int *running) {
    while (SDL_PollEvent(event)) {
        if (event->type == SDL_QUIT) {
            return 0;
        } else if (event->type == SDL_KEYDOWN) {
            if (event->key.keysym.sym == SDLK_q) {
                return 0;
            } else if (event->key.keysym.sym == SDLK_UP) {
                if (*selectedOption > 0) {
                    *selectedOption = *selectedOption - 1;
                } else {
                    *selectedOption = 0;
                }
            } else if (event->key.keysym.sym == SDLK_DOWN) {
                if (*selectedOption < 3) {
                    *selectedOption = *selectedOption + 1;
                } else {
                    *selectedOption = 3;
                }
            } else if (event->key.keysym.sym == SDLK_RETURN) {
                if (*selectedOption == 0) {
                    return 1;
                }
                else if (*selectedOption == 1) {
                    return 2;
                }
                else if (*selectedOption == 2) {
                    return 3;
                }
                else if (*selectedOption == 3) {
                    return 4;
                }
            }
        }
    }
    return -1;
}

int main() {
    srand(time(NULL));  

    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    TTF_Font *font = NULL;
    SDL_Window *gameWindow = NULL;
    SDL_Renderer *gameRenderer = NULL;

    if (initSDL(&window, &renderer, &font) != 0) {
        return -1;  
    }

    int running = 1;
    int selectedOption = 0;
    SDL_Event event;

    while (running) {
        int menuState = handleEvents(&event, &selectedOption, &running);  

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  
        SDL_RenderClear(renderer);

        if (menuState == -1) {
            drawMenu(renderer, font, selectedOption);
        } else {
            if (menuState == 1) {
                printf("Start Classic Game\n");
                startGame(&gameWindow, &gameRenderer);
            } else if(menuState == 2) {
                printf("Start 2x2 Game\n");
                startGame(&gameWindow, &gameRenderer);
            } else if(menuState == 3) {
                printf("Start 3x3 Game\n");
                startGame(&gameWindow, &gameRenderer);
            } else if(menuState == 4) {
                printf("Start Multiplayer Game\n");
                startGame(&gameWindow, &gameRenderer);
            } else {
                printf("Exit\n");
                running = 0;
            }
        }

        drawText(renderer, font, "Press q to exit", 100, 100);

        SDL_RenderPresent(renderer);
    }

    cleanup(window, renderer, font);  
    return 0;
}