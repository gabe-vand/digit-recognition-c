#pragma once
#include <SDL2/SDL.h>
#include <math.h>

// add params to draw line / circle: windowx and windowy and for each point compute if it is valud so we dont fuck grid up

void drawCircle(SDL_Renderer* ren, int** grid, float posX, float posY, int radius, int WINDOW_X, int WINDOW_Y);

void drawLine(SDL_Renderer* ren, int** grid, float startX, float startY, float endX, float endY, int radius, int WINDOW_X, int WINDOW_Y) {
    //given a start and and end point, calculate a straight line to get there and for each point on the line, call drawRadius
    float dx = endX - startX;
    float dy = endY - startY;
    int steps = ceil(fmax(fabs(dx), fabs(dy)));

    float xIncrement = dx / steps;
    float yIncrement = dy / steps;

    float curX = startX;
    float curY = startY;

    for (int i = 0; i < steps; i++) {
        curX = curX + xIncrement;
        curY = curY + yIncrement;
        drawCircle(ren, grid, curX, curY, radius, WINDOW_X, WINDOW_Y);
    }
}

void drawCircle(SDL_Renderer* ren, int** grid, float posX, float posY, int radius, int WINDOW_X, int WINDOW_Y) {
    // goal: draw a circle around (posX, posY) and call the draw func on each point

    // how? draw box around x,y with w=pixels.
    // for each pixel, calculate distance using circle formula and check if it is <pixels

    int topLeft[2]     = { posX - radius, posY - radius };
    int bottomRight[2] = { posX + radius, posY + radius };

    for (int x = topLeft[0]; x < bottomRight[0]; x++) {
        for (int y = topLeft[1]; y < bottomRight[1]; y++) {
            //we are iterating every pixel in the cube
            float xDist = abs(posX - x);
            float yDist = abs(posY - y);
            float distance = sqrt(pow(xDist, 2) + pow(yDist, 2));

            int valid = (x > 0 && x < WINDOW_X && y > 0 && y < WINDOW_Y);

            if (valid && distance < (float)radius) {
                SDL_RenderDrawPoint(ren, x, y);
                grid[y][x] = 1; // is this in bounds? seems dangerous for now
            }
        }
    }
}