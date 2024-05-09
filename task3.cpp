#include <SDL2/SDL.h>
#include <iostream>
using namespace std;

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
bool isRunning;
Uint32 startTime;
Uint32 currentTime;
bool collision = false; // Flag to track collision

// Moving balls
int r = 50;
int x = -2 * r;
int y = SCREEN_HEIGHT / 2;

// Movable balls
int R = 50;
int X = SCREEN_WIDTH / 2;
int Y = SCREEN_HEIGHT - R;

bool initializeWindow() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "Error: SDL initialization failed\nSDL Error: " << SDL_GetError() << endl;
        isRunning = false;
        return false;
    }

    window = SDL_CreateWindow("Collision", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    if (Y > R) Y -= 10;
                    break;
                case SDLK_LEFT:
                    if (X > R) X -= 10;
                    break;
                case SDLK_RIGHT:
                    if (X < SCREEN_WIDTH - R) X += 10;
                    break;
                case SDLK_DOWN:
                    if (Y < SCREEN_HEIGHT - R) Y += 10;
                    break;
                default:
                    break;
            }
        }
    }
}

bool checkCollision() {
    int d = (x - X) * (x - X) + (y - Y) * (y - Y);
    int sumRadii = (r + R) * (r + R);
    return d <= sumRadii;
}

void increment() {
    x += 20; // Increase x position at a faster rate
    if (x >= SCREEN_WIDTH + r) x = -r;
}

void update() {
    currentTime = SDL_GetTicks();
    Uint32 passedTime = currentTime - startTime;
    if (passedTime >= 16) { // Update approximately every 16 milliseconds (60 FPS)
        increment();
        startTime = currentTime;

        // Check for collision after each update
        collision = checkCollision();
    }
    SDL_Delay(16);
}

void drawFilledCircle(int cx, int cy, int radius) {
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= radius * radius) {
                SDL_RenderDrawPoint(renderer, cx + x, cy + y);
            }
        }
    }
}

void render() {
    // Clear the screen
    SDL_SetRenderDrawColor(renderer, 210, 126, 26, 255);
    SDL_RenderClear(renderer);

    // Draw the balls
    if (collision) {
        SDL_SetRenderDrawColor(renderer, 133, 55, 64, 255); // Change color if collision occurred
    } else {
        SDL_SetRenderDrawColor(renderer, 36, 48, 60, 255);
    }
    drawFilledCircle(x, y, r);

    if (collision) {
        SDL_SetRenderDrawColor(renderer, 133, 55, 64, 255); // Change color if collision occurred
    } else {
        SDL_SetRenderDrawColor(renderer, 36, 48, 60, 255);
    }
    drawFilledCircle(X, Y, R);

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
    startTime = SDL_GetTicks();

    while (isRunning) {
        Events();
        update();
        render();
    }

    clear();

    return 0;
}
