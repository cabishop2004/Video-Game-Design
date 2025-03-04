#include <stdlib.h>
#include <iostream>
#include <SDL.h>
#include "BouncingFace.h"

using namespace std;

void BouncingFace::bounceX() { vx *= -1; }
void BouncingFace::bounceY() { vy *= -1; }
void BouncingFace::bounce() { bounceX(); bounceY(); }

BouncingFace::BouncingFace(SDL_Renderer *ren, float ax0, float ay0, float vx0, float vy0, float x0, float y0) {
    ready = false;
    surface = SDL_LoadBMP("face.bmp");
    if (!surface) {
        cerr << "Failed to load image" << endl;
        return;
    }
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGBA(surface->format, 0, 255, 0, 255));
    t = SDL_CreateTextureFromSurface(ren, surface);
    if (!t) {
        cerr << "Failed to create texture" << endl;
        return;
    }

    rect.w = 96;
    rect.h = 96;
    ax = ax0;
    ay = ay0;
    vx = vx0;
    vy = vy0;
    x = (x0 == -1) ? rand() % 800 : x0;
    y = (y0 == -1) ? rand() % 600 : y0;
    ready = true;
}

void BouncingFace::loop(float dt) {
    // Apply gravity
    vy += ay * dt;
    
    // Update position
    x += vx * dt;
    y += vy * dt;

    rect.x = x;
    rect.y = y;

    // Handle floor collision (prevents falling below the screen)
    if (y >= 600 - 96) {
        y = 600 - 96;
        vy = 0;  // Stop downward motion when landing
    }

    // Screen bounds (left/right)
    if (x < 0) x = 0;
    if (x > 800 - 96) x = 800 - 96;
}

void BouncingFace::render(SDL_Renderer *ren, SDL_RendererFlip flip) {
    SDL_RenderCopyEx(ren, t, NULL, &rect, 0, NULL, flip);
}

