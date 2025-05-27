#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "render.h"
#include "logic.h"



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

    int textWidth = surface->w;
    int textHeight = surface->h;

    x = (wWidth - textWidth) / 2;
    y = (wHeight - textHeight) - 20;

    SDL_Rect dstRect = {x, y, textWidth, textHeight};
    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

void drawMenu(SDL_Renderer *renderer, TTF_Font *font, int selectedOption) {
    static SDL_Texture *menuImage = NULL;
    if (!menuImage) {
        SDL_Surface *imgSurface = IMG_Load("menu_logo.png");
        if (!imgSurface) {
            printf("Failed to load image: %s\n", IMG_GetError());
        } else {
            menuImage = SDL_CreateTextureFromSurface(renderer, imgSurface);
            SDL_FreeSurface(imgSurface);
        }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    int newWidth = 200;
    int newHeight = 200;

    if (menuImage) {
        int imgW, imgH;
        SDL_QueryTexture(menuImage, NULL, NULL, &imgW, &imgH);
        SDL_Rect dstRect = {
            (wWidth - newWidth) / 2,
            50,
            newWidth,
            newHeight
        };
        SDL_RenderCopy(renderer, menuImage, NULL, &dstRect);
    }

    SDL_Color white = {255, 255, 255, 255};
    SDL_Color highlight = {255, 165, 0, 255};
    char *menuOptions[] = {
        "Start 3x3 Game",
        "Start 4x4 Game",
        "Start 5x5 Game",
        "Start Multiplayer Game"
    };

    for (int i = 0; i < 4; i++) {
        SDL_Color color = (i == selectedOption) ? highlight : white;

        SDL_Surface *surface = TTF_RenderText_Solid(font, menuOptions[i], color);
        SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);

        int textWidth = surface->w;
        int textHeight = surface->h;
        int x = (wWidth - textWidth) / 2;
        int y = 400 + i * (textHeight + 10);

        SDL_Rect dstRect = {x, y, textWidth, textHeight};
        SDL_RenderCopy(renderer, texture, NULL, &dstRect);

        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }
}

void drawGameOver(SDL_Renderer *renderer, TTF_Font *font) {
    const char *gameOverText = "Game Over!";
    SDL_Color red = {255, 165, 0, 255};

    SDL_Surface *surface = TTF_RenderText_Solid(font, gameOverText, red);
    if (!surface) {
        printf("Error creating Game Over surface: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        printf("Error creating Game Over texture: %s\n", SDL_GetError());
        return;
    }

    int textW, textH;
    SDL_QueryTexture(texture, NULL, NULL, &textW, &textH);

    SDL_Rect dstRect = {
        (800 - textW) / 2,
        20 + (100 + 10),
        textW,
        textH
    };

    SDL_RenderCopy(renderer, texture, NULL, &dstRect);
    SDL_DestroyTexture(texture);
}

void startGame(SDL_Window **gameWindow, SDL_Renderer **gameRenderer, int gridSize) {
    int gameWindowWidth = 800;
    int gameWindowHeight = 600;

    if (gridSize == 5) {
        gameWindowWidth = 950;
        gameWindowHeight = 750;
    }

    *gameWindow = SDL_CreateWindow("2048 Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, gameWindowWidth, gameWindowHeight, SDL_WINDOW_SHOWN);
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

    TTF_Font *font = TTF_OpenFont("font4.ttf", 36);
    if (font == NULL) {
        printf("Eroare la deschiderea fontului: %s\n", TTF_GetError());
        SDL_DestroyRenderer(*gameRenderer);
        SDL_DestroyWindow(*gameWindow);
        return;
    }

    TTF_Font *font1 = TTF_OpenFont("font4.ttf", 42);
    if (font1 == NULL) {
        printf("Eroare la deschiderea fontului: %s\n", TTF_GetError());
        SDL_DestroyRenderer(*gameRenderer);
        SDL_DestroyWindow(*gameWindow);
        return;
    }

    int **grid = malloc(gridSize * sizeof(int *));
    for (int i = 0; i < gridSize; ++i) {
        grid[i] = calloc(gridSize, sizeof(int));
    }

    initializeGrid(grid, gridSize);

    int running = 1;
    int gameOver = 0;
    int score = 0;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_q) {
                    running = 0;
                }

                if (!gameOver) {
                    int moved = 0;
                    if (event.key.keysym.sym == SDLK_LEFT) {
                        moved = moveLeft(grid, gridSize, &score);
                    } else if (event.key.keysym.sym == SDLK_RIGHT) {
                        moved = moveRight(grid, gridSize, &score);
                    } else if (event.key.keysym.sym == SDLK_UP) {
                        moved = moveUp(grid, gridSize, &score);
                    } else if (event.key.keysym.sym == SDLK_DOWN) {
                        moved = moveDown(grid, gridSize, &score);
                    }

                    if (moved) {
                        spawnRandomTile(grid, gridSize);
                        if (!canMove(grid, gridSize)) {
                            gameOver = 1;
                        }
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(*gameRenderer, 50, 50, 50, 255);
        SDL_RenderClear(*gameRenderer);

        if (gameOver) {
            SDL_Color orange = {255, 165, 0, 255};
            SDL_Color white = {255, 255, 255, 255};

            SDL_Surface *gameOverSurface = TTF_RenderText_Solid(font1, "Game Over!", orange);
            SDL_Texture *gameOverTexture = SDL_CreateTextureFromSurface(*gameRenderer, gameOverSurface);
            int gameOverW, gameOverH;
            SDL_QueryTexture(gameOverTexture, NULL, NULL, &gameOverW, &gameOverH);
            SDL_Rect gameOverRect = {
                (gameWindowWidth - gameOverW) / 2,
                200,
                gameOverW,
                gameOverH
            };
            SDL_RenderCopy(*gameRenderer, gameOverTexture, NULL, &gameOverRect);
            SDL_FreeSurface(gameOverSurface);
            SDL_DestroyTexture(gameOverTexture);

            char scoreTextStr[64];
            sprintf(scoreTextStr, "Score: %d", score);
            SDL_Surface *scoreSurface = TTF_RenderText_Solid(font, scoreTextStr, white);
            SDL_Texture *scoreTexture = SDL_CreateTextureFromSurface(*gameRenderer, scoreSurface);
            int scoreW, scoreH;
            SDL_QueryTexture(scoreTexture, NULL, NULL, &scoreW, &scoreH);
            SDL_Rect scoreRect = {
                (gameWindowWidth - scoreW) / 2,
                gameOverRect.y + gameOverRect.h + 40,
                scoreW,
                scoreH
            };
            SDL_RenderCopy(*gameRenderer, scoreTexture, NULL, &scoreRect);
            SDL_FreeSurface(scoreSurface);
            SDL_DestroyTexture(scoreTexture);

            const char *messageText = "Press q to select a new gamemode";
            SDL_Surface *messageSurface = TTF_RenderText_Solid(font, messageText, white);
            SDL_Texture *messageTexture = SDL_CreateTextureFromSurface(*gameRenderer, messageSurface);
            int messageW, messageH;
            SDL_QueryTexture(messageTexture, NULL, NULL, &messageW, &messageH);
            SDL_Rect messageRect = {
                (gameWindowWidth - messageW) / 2,
                scoreRect.y + scoreRect.h + 30,
                messageW,
                messageH
            };
            SDL_RenderCopy(*gameRenderer, messageTexture, NULL, &messageRect);
            SDL_FreeSurface(messageSurface);
            SDL_DestroyTexture(messageTexture);

        } else {
            int tileSize = 100;
            int padding = 10;
            int totalGridDisplayWidth = gridSize * tileSize + (gridSize - 1) * padding;
            int totalGridDisplayHeight = totalGridDisplayWidth;

            char currentScoreText[64];
            sprintf(currentScoreText, "Score: %d", score);
            SDL_Color currentScoreColor = {255, 255, 255, 255};

            SDL_Surface *currentScoreSurface = TTF_RenderText_Solid(font, currentScoreText, currentScoreColor);
            SDL_Texture *currentScoreTexture = SDL_CreateTextureFromSurface(*gameRenderer, currentScoreSurface);

            int currentScoreW, currentScoreH;
            SDL_QueryTexture(currentScoreTexture, NULL, NULL, &currentScoreW, &currentScoreH);

            int scoreToGridPadding = 20;
            int combinedContentHeight = currentScoreH + scoreToGridPadding + totalGridDisplayHeight;

            int startY = (gameWindowHeight - combinedContentHeight) / 2;
            if (startY < 0) startY = 0;

            SDL_Rect currentScoreRect = {
                (gameWindowWidth - currentScoreW) / 2,
                startY,
                currentScoreW,
                currentScoreH
            };
            SDL_RenderCopy(*gameRenderer, currentScoreTexture, NULL, &currentScoreRect);
            SDL_FreeSurface(currentScoreSurface);
            SDL_DestroyTexture(currentScoreTexture);

            int offsetX = (gameWindowWidth - totalGridDisplayWidth) / 2;
            int offsetY = currentScoreRect.y + currentScoreRect.h + scoreToGridPadding;

            for (int row = 0; row < gridSize; row++) {
                for (int col = 0; col < gridSize; col++) {
                    SDL_Rect tileRect = {
                        offsetX + col * (tileSize + padding),
                        offsetY + row * (tileSize + padding),
                        tileSize,
                        tileSize
                    };
                    SDL_Color tileColor;

                    switch(grid[row][col]) {
                        case 2: tileColor = (SDL_Color){238, 228, 218, 255}; break;
                        case 4: tileColor = (SDL_Color){237, 224, 200, 255}; break;
                        case 8: tileColor = (SDL_Color){242, 177, 121, 255}; break;
                        case 16: tileColor = (SDL_Color){245, 149, 99, 255}; break;
                        case 32: tileColor = (SDL_Color){246, 124, 95, 255}; break;
                        case 64: tileColor = (SDL_Color){246, 94, 59, 255}; break;
                        case 128: tileColor = (SDL_Color){237, 207, 114, 255}; break;
                        case 256: tileColor = (SDL_Color){237, 204, 97, 255}; break;
                        case 512: tileColor = (SDL_Color){237, 200, 80, 255}; break;
                        case 1024: tileColor = (SDL_Color){237, 197, 63, 255}; break;
                        case 2048: tileColor = (SDL_Color){237, 194, 46, 255}; break;
                        default: tileColor = (SDL_Color){180, 180, 180, 255}; break;
                    }

                    SDL_SetRenderDrawColor(*gameRenderer, tileColor.r, tileColor.g, tileColor.b, tileColor.a);
                    SDL_RenderFillRect(*gameRenderer, &tileRect);

                    if (grid[row][col] != 0) {
                        char valueText[10];
                        snprintf(valueText, sizeof(valueText), "%d", grid[row][col]);
                        SDL_Color color = {0, 0, 0, 255};

                        SDL_Surface *surface = TTF_RenderText_Blended(font, valueText, color);
                        if (!surface) {
                            printf("Error creating text surface: %s\n", TTF_GetError());
                            continue;
                        }

                        SDL_Texture *texture = SDL_CreateTextureFromSurface(*gameRenderer, surface);
                        SDL_FreeSurface(surface);
                        if (!texture) {
                            printf("Error creating texture from surface: %s\n", SDL_GetError());
                            continue;
                        }

                        SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);

                        int textW, textH;
                        SDL_QueryTexture(texture, NULL, NULL, &textW, &textH);

                        SDL_Rect textRect = {
                            tileRect.x + (tileSize - textW) / 2,
                            tileRect.y + (tileSize - textH) / 2,
                            textW,
                            textH
                        };

                        SDL_RenderCopy(*gameRenderer, texture, NULL, &textRect);
                        SDL_DestroyTexture(texture);
                    }
                }
            }
        }

        SDL_RenderPresent(*gameRenderer);
        SDL_Delay(16);
    }

    for (int i = 0; i < gridSize; ++i) {
        free(grid[i]);
    }
    free(grid);

    TTF_CloseFont(font);
    TTF_CloseFont(font1);
    SDL_DestroyRenderer(*gameRenderer);
    SDL_DestroyWindow(*gameWindow);
}

void renderGrid(SDL_Renderer *renderer, TTF_Font *font, int **grid, int gridSize, int gridDrawX, int gridDrawY, int score, const char *playerName) {
    int tileSize = 100;
    int padding = 10;

    int totalGridWidth = gridSize * tileSize + (gridSize - 1) * padding;
    int totalGridHeight = totalGridWidth;

    char scoreText[64];
    snprintf(scoreText, sizeof(scoreText), "%s Score: %d", playerName, score);
    SDL_Color white = {255, 255, 255, 255};

    SDL_Surface *surface = TTF_RenderText_Solid(font, scoreText, white);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    int textW = surface->w;
    int textH = surface->h;
    SDL_FreeSurface(surface);

    SDL_Rect textRect = {
        gridDrawX + (totalGridWidth - textW) / 2,
        gridDrawY - textH - 20,
        textW,
        textH
    };
    SDL_RenderCopy(renderer, texture, NULL, &textRect);
    SDL_DestroyTexture(texture);

    for (int row = 0; row < gridSize; row++) {
        for (int col = 0; col < gridSize; col++) {
            SDL_Rect tileRect = {
                gridDrawX + col * (tileSize + padding),
                gridDrawY + row * (tileSize + padding),
                tileSize,
                tileSize
            };

            SDL_Color tileColor;
            switch(grid[row][col]) {
                case 2: tileColor = (SDL_Color){238, 228, 218, 255}; break;
                case 4: tileColor = (SDL_Color){237, 224, 200, 255}; break;
                case 8: tileColor = (SDL_Color){242, 177, 121, 255}; break;
                case 16: tileColor = (SDL_Color){245, 149, 99, 255}; break;
                case 32: tileColor = (SDL_Color){246, 124, 95, 255}; break;
                case 64: tileColor = (SDL_Color){246, 94, 59, 255}; break;
                case 128: tileColor = (SDL_Color){237, 207, 114, 255}; break;
                case 256: tileColor = (SDL_Color){237, 204, 97, 255}; break;
                case 512: tileColor = (SDL_Color){237, 200, 80, 255}; break;
                case 1024: tileColor = (SDL_Color){237, 197, 63, 255}; break;
                case 2048: tileColor = (SDL_Color){237, 194, 46, 255}; break;
                default: tileColor = (SDL_Color){180, 180, 180, 255}; break;
            }

            SDL_SetRenderDrawColor(renderer, tileColor.r, tileColor.g, tileColor.b, tileColor.a);
            SDL_RenderFillRect(renderer, &tileRect);

            if (grid[row][col] != 0) {
                char valueText[10];
                snprintf(valueText, sizeof(valueText), "%d", grid[row][col]);
                SDL_Color color = {0, 0, 0, 255};

                SDL_Surface *valSurface = TTF_RenderText_Blended(font, valueText, color);
                SDL_Texture *valTexture = SDL_CreateTextureFromSurface(renderer, valSurface);
                SDL_FreeSurface(valSurface);

                int valW, valH;
                SDL_QueryTexture(valTexture, NULL, NULL, &valW, &valH);

                SDL_Rect valRect = {
                    tileRect.x + (tileSize - valW) / 2,
                    tileRect.y + (tileSize - valH) / 2,
                    valW,
                    valH
                };

                SDL_RenderCopy(renderer, valTexture, NULL, &valRect);
                SDL_DestroyTexture(valTexture);
            }
        }
    }
}

void cleanup(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font) {
    if (font != NULL) {
        TTF_CloseFont(font);
    }
    if (renderer != NULL) {
        SDL_DestroyRenderer(renderer);
    }
    if (window != NULL) {
        SDL_DestroyWindow(window);
    }
    TTF_Quit();
    SDL_Quit();
    IMG_Quit();
}
