#include <SDL2/SDL.h>
#include <bits/stdc++.h>
using namespace std;

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 450

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
bool isRunning;
int red = 0;
Uint32 startTime;
Uint32 currentTime;

struct ball {
    int radius;
    int CenterX;
    int CenterY;
} ball;

bool initializeWindow() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "Error: SDL initialization failed\nSDL Error: " << SDL_GetError() << endl;
        isRunning = false;
        return false;
    }

    window = SDL_CreateWindow("Blinking Circle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        cout << "Error: Failed to create window\nSDL Error: " << SDL_GetError() << endl;
        isRunning = false;
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        cout << "Error: Failed to create renderer\nSDL Error: " << SDL_GetError() << endl;
        isRunning = false;
        return false;
    }

    return true;
}

void Events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            isRunning = false;
        }
    }
}

void setup() {
    ball.radius = 2;
    ball.CenterX = SCREEN_WIDTH / 2;
    ball.CenterY = SCREEN_HEIGHT / 2;
}

void increment() {
    ball.radius += 2; // Increase radius at a faster rate
    if (ball.radius >= min(SCREEN_HEIGHT/2,SCREEN_WIDTH/2)) ball.radius = 2;
}

void update() {
    currentTime = SDL_GetTicks();
    Uint32 passedTime = currentTime - startTime;
    if (passedTime >= 16) { // Update approximately every 16 milliseconds (60 FPS)
        increment();
        startTime = currentTime;
    }
}

void draw() {
    for (int x = -ball.radius; x <= ball.radius; x++) {
        for (int y = -ball.radius; y <= ball.radius; y++) {
            if (x*x + y*y <= ball.radius*ball.radius) {
                SDL_RenderDrawPoint(renderer, ball.CenterX + x, ball.CenterY + y);
            }
        }
    }
}

void render() {
    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 210, 126, 26, 255);
    SDL_RenderClear(renderer);

    // Draw the ball
    SDL_SetRenderDrawColor(renderer, 36, 48, 60, 255);
    draw();

    // Present the renderer
    SDL_RenderPresent(renderer);
}

void clear() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char** argv) {
    isRunning = initializeWindow();
    setup();
    startTime = SDL_GetTicks();

    while (isRunning) {
        Events();
        update();
        render();
    }

    clear();

    return 0;
}
