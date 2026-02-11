#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rendering.c"
#include "categorizing.c"
#include <SDL2/SDL.h>

#define WINDOW_X 600
#define WINDOW_Y 600

#define DRAW_RADIUS 11

int main(int argc, char* argv[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    // create grid representation of our view for ML processing
    int **grid = (int **)malloc(WINDOW_Y * sizeof(int *));
    for (int i = 0; i < WINDOW_Y; i++) {
        grid[i] = (int *)calloc(WINDOW_X, sizeof(int));  // calloc initializes to 0
    }

    SDL_Window *screen = SDL_CreateWindow("Bullshit-ass App",
            SDL_WINDOWPOS_UNDEFINED,
            SDL_WINDOWPOS_UNDEFINED,
            WINDOW_X, WINDOW_Y,
            0);
    SDL_Renderer *renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_SOFTWARE);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    short int running = 1;
    short int drawing = 0;
    SDL_Event event;
    float lastDrawnPoint[2] = { -1.0, -1.0 }; 

    SDL_RenderPresent(renderer);

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = 0;
            }

            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_c) {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderClear(renderer);
                    SDL_RenderPresent(renderer);
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
                    
                    // Clear the grid
                    for (int i = 0; i < WINDOW_Y; i++) {
                        memset(grid[i], 0, WINDOW_X * sizeof(int));
                    }
                }

                else if (event.key.keysym.sym == SDLK_RETURN) {
                    printf("Grid saved. Exiting GUI.\n");
                    running = 0;
                }
            }

            else if (!drawing && event.type == SDL_MOUSEBUTTONDOWN) drawing = 1;

            else if (drawing && event.type == SDL_MOUSEBUTTONUP) {
                lastDrawnPoint[0] = -1.0;
                lastDrawnPoint[1] = -1.0;
                drawing = 0;
            }

            if (drawing) {

                if (lastDrawnPoint[0] != -1.0) {
                    drawLine(renderer, grid, event.button.x, event.button.y, lastDrawnPoint[0], lastDrawnPoint[1], DRAW_RADIUS, WINDOW_X, WINDOW_Y);
                }

                else drawCircle(renderer, grid, event.button.x, event.button.y, DRAW_RADIUS, WINDOW_X, WINDOW_Y);

                SDL_RenderPresent(renderer);
                lastDrawnPoint[0] = event.button.x;
                lastDrawnPoint[1] = event.button.y;
            }
        }

        // read mouse input.
        // if right click, grab index of click, call SDL_RenderDrawPoint
        // also, read keyboard input. if <enter>, exit program
    }

    SDL_DestroyWindow(screen);
    SDL_Quit();

    char category = categorizeGrid(grid, WINDOW_X, WINDOW_Y);

    printf("You draw a %c", category);

    // Free allocated memory
    for (int i = 0; i < WINDOW_Y; i++) {
        free(grid[i]);
    } free(grid);

    return 0;
}