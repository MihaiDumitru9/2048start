#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "render.h" 
#include "logic.h"



int initSDL(SDL_Window **window, SDL_Renderer **renderer, TTF_Font **font) {
    if (IMG_Init(IMG_INIT_PNG) == 0) {
        printf("SDL_image failed to initialize: %s\n", IMG_GetError());
        return -1;
    }

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
    if (!*window) {
        printf("Failed to create window: %s\n", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!*renderer) {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        TTF_Quit();
        SDL_Quit();
        return -1;
    }

    *font = TTF_OpenFont("font4.ttf", 30);
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
            *running = 0;
            return 0;
        } else if (event->type == SDL_KEYDOWN) {
            switch (event->key.keysym.sym) {
                case SDLK_q:
                    *running = 0;
                    return 0;
                case SDLK_UP:
                    if (*selectedOption > 0)
                        (*selectedOption)--;
                    break;
                case SDLK_DOWN:
                    if (*selectedOption < 3)
                        (*selectedOption)++;
                    break;
                case SDLK_RETURN:
                    return *selectedOption + 1;
                default:
                    break;
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
            if (menuState >= 1 && menuState <= 3) {
                int gridSize = 3 + (menuState - 1);
                printf("Starting Game with grid size %dx%d\n", gridSize, gridSize);
                startGame(&gameWindow, &gameRenderer, gridSize);
            } else if (menuState == 4) {
                printf("Starting Multiplayer Game\n");
                runMultiplayerGame(window, renderer, font);
            } else {
                running = 0;
            }
        }

        drawText(renderer, font, "Press q to exit", 0, 100);
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    cleanup(window, renderer, font);
    return 0;
}
