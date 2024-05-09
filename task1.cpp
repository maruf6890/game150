#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

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

    window = SDL_CreateWindow("Circle", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
    ball.radius = 150;
    ball.CenterX = SCREEN_WIDTH / 2;
    ball.CenterY = SCREEN_HEIGHT / 2;
}



void update() {
  
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
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Draw the ball
    SDL_SetRenderDrawColor(renderer, 200, 14, 9, 255);
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
