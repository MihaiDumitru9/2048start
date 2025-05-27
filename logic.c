#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include "logic.h"
#include "render.h"



void initializeGrid(int **grid, int gridSize) {
    for (int i = 0; i < gridSize; i++)
        for (int j = 0; j < gridSize; j++)
            grid[i][j] = 0;

    spawnRandomTile(grid, gridSize);
    spawnRandomTile(grid, gridSize);
}

void spawnRandomTile(int **grid, int gridSize) {
    int emptyCells = 0;
    for (int i = 0; i < gridSize; i++)
        for (int j = 0; j < gridSize; j++)
            if (grid[i][j] == 0)
                emptyCells++;

    if (emptyCells == 0)
        return;

    int randomCell = rand() % emptyCells;
    int count = 0;
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (grid[i][j] == 0) {
                if (count == randomCell) {
                    grid[i][j] = (rand() % 10 == 0) ? 4 : 2;
                    return;
                }
                count++;
            }
        }
    }
}

int moveLeft(int **grid, int size, int *score) {
    int moved = 0;
    int merged[size][size];
    for(int r=0; r<size; ++r) for(int c=0; c<size; ++c) merged[r][c] = 0;

    for (int row = 0; row < size; row++) {
        for (int col = 1; col < size; col++) {
            if (grid[row][col] == 0) continue;

            int target = col;
            while (target > 0 && grid[row][target - 1] == 0) {
                grid[row][target - 1] = grid[row][target];
                grid[row][target] = 0;
                target--;
                moved = 1;
            }

            if (target > 0 && grid[row][target - 1] == grid[row][target] && !merged[row][target - 1]) {
                grid[row][target - 1] *= 2;
                *score += grid[row][target - 1];
                grid[row][target] = 0;
                merged[row][target - 1] = 1;
                moved = 1;
            }
        }
    }

    return moved;
}

int moveRight(int **grid, int size, int *score) {
    int moved = 0;
    int merged[size][size];
    for(int r=0; r<size; ++r) for(int c=0; c<size; ++c) merged[r][c] = 0;

    for (int row = 0; row < size; row++) {
        for (int col = size - 2; col >= 0; col--) {
            if (grid[row][col] == 0) continue;

            int target = col;
            while (target < size - 1 && grid[row][target + 1] == 0) {
                grid[row][target + 1] = grid[row][target];
                grid[row][target] = 0;
                target++;
                moved = 1;
            }

            if (target < size - 1 && grid[row][target + 1] == grid[row][target] && !merged[row][target + 1]) {
                grid[row][target + 1] *= 2;
                *score += grid[row][target + 1];
                grid[row][target] = 0;
                merged[row][target + 1] = 1;
                moved = 1;
            }
        }
    }

    return moved;
}

int moveUp(int **grid, int size, int *score) {
    int moved = 0;
    int merged[size][size];
    for(int r=0; r<size; ++r) for(int c=0; c<size; ++c) merged[r][c] = 0;

    for (int col = 0; col < size; col++) {
        for (int row = 1; row < size; row++) {
            if (grid[row][col] == 0) continue;

            int target = row;
            while (target > 0 && grid[target - 1][col] == 0) {
                grid[target - 1][col] = grid[target][col];
                grid[target][col] = 0;
                target--;
                moved = 1;
            }

            if (target > 0 && grid[target - 1][col] == grid[target][col] && !merged[target - 1][col]) {
                grid[target - 1][col] *= 2;
                *score += grid[target - 1][col];
                grid[target][col] = 0;
                merged[target - 1][col] = 1;
                moved = 1;
            }
        }
    }

    return moved;
}

int moveDown(int **grid, int size, int *score) {
    int moved = 0;
    int merged[size][size];
    for(int r=0; r<size; ++r) for(int c=0; c<size; ++c) merged[r][c] = 0;

    for (int col = 0; col < size; col++) {
        for (int row = size - 2; row >= 0; row--) {
            if (grid[row][col] == 0) continue;

            int target = row;
            while (target < size - 1 && grid[target + 1][col] == 0) {
                grid[target + 1][col] = grid[target][col];
                grid[target][col] = 0;
                target++;
                moved = 1;
            }

            if (target < size - 1 && grid[target + 1][col] == grid[target][col] && !merged[target + 1][col]) {
                grid[target + 1][col] *= 2;
                *score += grid[target + 1][col];
                grid[target][col] = 0;
                merged[target + 1][col] = 1;
                moved = 1;
            }
        }
    }

    return moved;
}

int canMove(int **grid, int gridSize) {
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (grid[i][j] == 0)
                return 1;
            if (j + 1 < gridSize && grid[i][j] == grid[i][j + 1])
                return 1;
            if (i + 1 < gridSize && grid[i][j] == grid[i + 1][j])
                return 1;
        }
    }
    return 0;
}

void initGrid(int **grid, int size) {
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            grid[i][j] = 0;
    spawnRandomTile(grid, size);
    spawnRandomTile(grid, size);
}

void printGrid(int **grid, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++)
            printf("%4d ", grid[i][j]);
        printf("\n");
    }
    printf("\n");
}

int handlePlayerMove(SDL_Keycode key, int **grid, int size, int *score, int isPlayer1) {
    int moved = 0;
    if (isPlayer1) {
        if (key == SDLK_a) moved = moveLeft(grid, size, score);
        else if (key == SDLK_d) moved = moveRight(grid, size, score);
        else if (key == SDLK_w) moved = moveUp(grid, size, score);
        else if (key == SDLK_s) moved = moveDown(grid, size, score);
    } else {
        if (key == SDLK_LEFT) moved = moveLeft(grid, size, score);
        else if (key == SDLK_RIGHT) moved = moveRight(grid, size, score);
        else if (key == SDLK_UP) moved = moveUp(grid, size, score);
        else if (key == SDLK_DOWN) moved = moveDown(grid, size, score);
    }
    if (moved) spawnRandomTile(grid, size);
    return moved;
}

void runMultiplayerGame(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font) {
    int **grid1 = malloc(GRID_SIZE * sizeof(int *));
    int **grid2 = malloc(GRID_SIZE * sizeof(int *));
    for (int i = 0; i < GRID_SIZE; i++) {
        grid1[i] = calloc(GRID_SIZE, sizeof(int));
        grid2[i] = calloc(GRID_SIZE, sizeof(int));
    }

    int score1 = 0, score2 = 0;
    initGrid(grid1, GRID_SIZE);
    initGrid(grid2, GRID_SIZE);

    int currentPlayer = 0;
    time_t startTime = time(NULL);
    const int duration = 60;

    SDL_Event event;
    int running = 1;
    int multiplayerGameOver = 0;

    int tileSize = 100;
    int padding = 10;
    int gridPadding = 50;

    int totalGridWidth = GRID_SIZE * tileSize + (GRID_SIZE - 1) * padding;
    int totalWidth = totalGridWidth * 2 + gridPadding;

    int offsetX1 = (wWidth - totalWidth) / 2;
    int offsetX2 = offsetX1 + totalGridWidth + gridPadding;

    int offsetY = (wHeight - totalGridWidth) / 2 + 50;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
                break;
            }
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_q) {
                    running = 0;
                    break;
                }

                if (!multiplayerGameOver) {
                    SDL_Keycode key = event.key.keysym.sym;
                    int moved = 0;

                    if (currentPlayer == 0) {
                        moved = handlePlayerMove(key, grid1, GRID_SIZE, &score1, 1);
                    } else {
                        moved = handlePlayerMove(key, grid2, GRID_SIZE, &score2, 0);
                    }

                    if (moved) {
                        currentPlayer = 1 - currentPlayer;
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
        SDL_RenderClear(renderer);

        if (multiplayerGameOver) {
            SDL_Color orange = {255, 165, 0, 255};
            SDL_Color white = {255, 255, 255, 255};

            const char *gameOverText = "Multiplayer Game Over!";
            SDL_Surface *surface = TTF_RenderText_Solid(font, gameOverText, orange);
            SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
            int textW, textH;
            SDL_QueryTexture(texture, NULL, NULL, &textW, &textH);
            SDL_Rect dstRect = { (wWidth - textW) / 2, 150, textW, textH };
            SDL_RenderCopy(renderer, texture, NULL, &dstRect);
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);

            char p1ScoreText[64];
            snprintf(p1ScoreText, sizeof(p1ScoreText), "Player 1 Score: %d", score1);
            surface = TTF_RenderText_Solid(font, p1ScoreText, white);
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_QueryTexture(texture, NULL, NULL, &textW, &textH);
            SDL_Rect p1ScoreRect = { (wWidth - textW) / 2, dstRect.y + dstRect.h + 50, textW, textH };
            SDL_RenderCopy(renderer, texture, NULL, &p1ScoreRect);
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);

            char p2ScoreText[64];
            snprintf(p2ScoreText, sizeof(p2ScoreText), "Player 2 Score: %d", score2);
            surface = TTF_RenderText_Solid(font, p2ScoreText, white);
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_QueryTexture(texture, NULL, NULL, &textW, &textH);
            SDL_Rect p2ScoreRect = { (wWidth - textW) / 2, p1ScoreRect.y + p1ScoreRect.h + 20, textW, textH };
            SDL_RenderCopy(renderer, texture, NULL, &p2ScoreRect);
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);

            char winnerMessage[100];
            if (score1 > score2) {
                snprintf(winnerMessage, sizeof(winnerMessage), "Player 1 Wins!");
            } else if (score2 > score1) {
                snprintf(winnerMessage, sizeof(winnerMessage), "Player 2 Wins!");
            } else {
                snprintf(winnerMessage, sizeof(winnerMessage), "It's a Tie!");
            }
            surface = TTF_RenderText_Solid(font, winnerMessage, orange);
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_QueryTexture(texture, NULL, NULL, &textW, &textH);
            SDL_Rect winnerRect = { (wWidth - textW) / 2, p2ScoreRect.y + p2ScoreRect.h + 50, textW, textH };
            SDL_RenderCopy(renderer, texture, NULL, &winnerRect);
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);

            const char *quitMessage = "Press q to select a new gamemode";
            surface = TTF_RenderText_Solid(font, quitMessage, white);
            texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_QueryTexture(texture, NULL, NULL, &textW, &textH);
            SDL_Rect quitRect = { (wWidth - textW) / 2, winnerRect.y + winnerRect.h + 50, textW, textH };
            SDL_RenderCopy(renderer, texture, NULL, &quitRect);
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);

        } else {
            renderGrid(renderer, font, grid1, GRID_SIZE, offsetX1, offsetY, score1, "Player 1");
            renderGrid(renderer, font, grid2, GRID_SIZE, offsetX2, offsetY, score2, "Player 2");

            char turnText[50];
            snprintf(turnText, sizeof(turnText), "Current Turn: Player %d", currentPlayer + 1);
            SDL_Color highlight = {255, 165, 0, 255};
            SDL_Surface *turnSurface = TTF_RenderText_Solid(font, turnText, highlight);
            SDL_Texture *turnTexture = SDL_CreateTextureFromSurface(renderer, turnSurface);
            int tw, th;
            SDL_QueryTexture(turnTexture, NULL, NULL, &tw, &th);
            SDL_Rect turnRect = { (wWidth - tw) / 2, 50, tw, th };
            SDL_RenderCopy(renderer, turnTexture, NULL, &turnRect);
            SDL_FreeSurface(turnSurface);
            SDL_DestroyTexture(turnTexture);

            int remainingTime = duration - (int)difftime(time(NULL), startTime);
            if (remainingTime < 0) remainingTime = 0;

            char timerString[50];
            snprintf(timerString, sizeof(timerString), "Time: %d seconds", remainingTime);
            SDL_Color timerColor = {255, 255, 255, 255};

            SDL_Surface *timerSurface = TTF_RenderText_Solid(font, timerString, timerColor);
            SDL_Texture *timerTexture = SDL_CreateTextureFromSurface(renderer, timerSurface);
            int timerW, timerH;
            SDL_QueryTexture(timerTexture, NULL, NULL, &timerW, &timerH);

            SDL_Rect timerRect = { wWidth - timerW - 20, 50, timerW, timerH };

            SDL_RenderCopy(renderer, timerTexture, NULL, &timerRect);
            SDL_FreeSurface(timerSurface);
            SDL_DestroyTexture(timerTexture);

            if (difftime(time(NULL), startTime) >= duration) {
                multiplayerGameOver = 1;
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(10);
    }

    printf("\nTime's up!\n\nFinal Scores:\n");
    printf("Player 1: %d\n", score1);
    printf("Player 2: %d\n", score2);

    if (score1 > score2)
        printf("Player 1 wins!\n");
    else if (score2 > score1)
        printf("Player 2 wins!\n");
    else
        printf("It's a tie!\n");

    for (int i = 0; i < GRID_SIZE; i++) {
        free(grid1[i]);
        free(grid2[i]);
    }
    free(grid1);
    free(grid2);
}