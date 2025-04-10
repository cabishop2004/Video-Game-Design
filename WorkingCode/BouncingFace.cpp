#include <stdlib.h>
#include <iostream>
#include "SDL.h"
#include "BouncingFace.h"

using namespace std;

void BouncingFace::bounceX() { vx *= -1; }
void BouncingFace::bounceY() { vy *= -1; }
void BouncingFace::bounce() { bounceX(); bounceY(); }

BouncingFace::BouncingFace(SDL_Renderer *ren, float ax0, float ay0, float vx0, float vy0, float x0, float y0) {
    ready = false;
    attacking = false;
    attackTimer = 0;

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

    // Load sword image
    SDL_Surface* swordSurface = SDL_LoadBMP("sword.bmp");
    if (swordSurface) {
        SDL_SetColorKey(swordSurface, SDL_TRUE, SDL_MapRGB(swordSurface->format, 0, 255, 0));
        sword = SDL_CreateTextureFromSurface(ren, swordSurface);
        SDL_FreeSurface(swordSurface);
    } else {
        cerr << "Failed to load sword image" << endl;
        sword = nullptr;
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
    if (y < 600 - 96) {
        vy += ay * dt;
    }

    x += vx * dt;
    y += vy * dt;

    rect.x = x;
    rect.y = y;

    if (y >= 600 - 96) {
        y = 600 - 96;
        vy = 0;
    }

    if (x < 0) x = 0;
    if (x > 800 - 96) x = 800 - 96;

    if (attacking) {
        attackTimer -= dt;
        if (attackTimer <= 0) {
            attacking = false;
        }
    }
}

void BouncingFace::render(SDL_Renderer *ren, SDL_RendererFlip flip) {

    SDL_RenderCopyEx(ren, t, NULL, &rect, 0, NULL, flip);

    if (attacking && sword) {
        SDL_Rect swordRect;
        swordRect.w = 50;
        swordRect.h = 24;

        if (flip == SDL_FLIP_NONE) {
            swordRect.x = x + 70;
        } else {
            swordRect.x = x - 20;
        }
        swordRect.y = y + 40;

        SDL_RenderCopyEx(ren, sword, NULL, &swordRect, 0, NULL, flip);
    }
}

void BouncingFace::attack() {
    attacking = true;
    attackTimer = attackDuration;
}

//float BouncingFace::getX() { return x; }  // Optional: already used in render logic
