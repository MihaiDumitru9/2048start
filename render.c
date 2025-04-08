#include <stdio.h>
#include <stdlib.h>
#include "render.h"

#define wWidth 1600
#define wHeight 720

void drawText(SDL_Renderer *renderer, TTF_Font *font, const char *text, int x, int y) {
    SDL_Color color = {255, 255, 255, 255}; 
    SDL_Surface *surface = TTF_RenderText_Solid(font, text, color);  
    if (surface == NULL) {
        printf("Eroare la crearea suprafeței de text: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);  
    if (texture == NULL) {
        printf("Eroare la crearea texturii: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    int windowWidth = wWidth;
    int windowHeight = wHeight;

    int textWidth = surface->w;
    int textHeight = surface->h;

    x = (windowWidth - textWidth) / 2;  
    y = (windowHeight - textHeight) - 20;  

    SDL_Rect dstRect = {x, y, textWidth, textHeight};  
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);  

    SDL_FreeSurface(surface);  
    SDL_DestroyTexture(texture);  
}

void drawMenu(SDL_Renderer *renderer, TTF_Font *font, int selectedOption) {
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color highlight = {0, 255, 0, 255};
    char *menuOptions[] = {
        "Start Classic Game",
        "Start 2x2 Game",
        "Start 3x3 Game",
        "Start Multiplayer Game"
    };

    for (int i = 0; i < 4; i++) {
        SDL_Color color = (i == selectedOption) ? highlight : white;

        SDL_Surface *surface = TTF_RenderText_Solid(font, menuOptions[i], color);
        if (surface == NULL) {
            printf("Eroare la crearea suprafeței de text: %s\n", TTF_GetError());
            continue;
        }

        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
        if (texture == NULL) {
            printf("Eroare la crearea texturii: %s\n", SDL_GetError());
            SDL_FreeSurface(surface);
            continue;
        }

        int textWidth = surface->w;
        int textHeight = surface->h;
        int x = (wWidth - textWidth) / 2;
        int y = (wHeight / 2) + (i * (textHeight + 10));

        SDL_Rect dstRect = {x, y, textWidth, textHeight};
        SDL_RenderCopy(renderer, texture, NULL, &dstRect);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
}

void startGame(SDL_Window **gameWindow, SDL_Renderer **gameRenderer) {
    *gameWindow = SDL_CreateWindow("Classic Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    if (*gameWindow == NULL) {
        printf("Eroare la crearea ferestrei: %s\n", SDL_GetError());
        return;
    }
    
    *gameRenderer = SDL_CreateRenderer(*gameWindow, -1, SDL_RENDERER_ACCELERATED);
    if (*gameRenderer == NULL) {
        printf("Eroare la crearea renderer-ului: %s\n", SDL_GetError());
        SDL_DestroyWindow(*gameWindow);
        return;
    }

    SDL_SetRenderDrawColor(*gameRenderer, 0, 0, 255, 255);
    SDL_RenderClear(*gameRenderer);

    SDL_Color white = {255, 255, 255, 255};
    TTF_Font *font = TTF_OpenFont("font1.ttf", 24);
    if (font == NULL) {
        printf("Eroare la deschiderea fontului: %s\n", TTF_GetError());
        return;
    }
    drawText(*gameRenderer, font, "Classic Game Started!", 100, 100);

    SDL_RenderPresent(*gameRenderer);

    int running = 1;
    SDL_Event event;
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_q) {
                    running = 0;
                }
            }
        }

        SDL_RenderPresent(*gameRenderer);
    }

    SDL_DestroyRenderer(*gameRenderer);
    SDL_DestroyWindow(*gameWindow);
    TTF_CloseFont(font);
}

void cleanup(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font) {
    TTF_CloseFont(font);  
    SDL_DestroyRenderer(renderer);  
    SDL_DestroyWindow(window);  
    TTF_Quit();  
    SDL_Quit();  
}
