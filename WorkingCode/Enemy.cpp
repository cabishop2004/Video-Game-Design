#include <stdlib.h>
#include <iostream>
#include "SDL.h"
#include "Enemy.h"

using namespace std;

Enemy::Enemy(const char* name, SDL_Renderer *ren, bool e, int w, int h, float x0, float y0, float vx0, float vy0, float ax0, float ay0)
{
    surface = SDL_LoadBMP(name);
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

    x = x0;
    y = y0;
    vx = vx0;
    vy = vy0;
    ax = ax0;
    ay = ay0;
    enabled = e;
    rect.w = w;
    rect.h = h;
    rect.x = static_cast<int>(x);
    rect.y = static_cast<int>(y);
    flip = SDL_FLIP_NONE;
}

void Enemy::loop(float dt, float playerX)
{
    if(!enabled)
        return;
    tracking(dt, playerX);
}

void Enemy::render(SDL_Renderer *ren)
{
    if(enabled)
        SDL_RenderCopyEx(ren, t, NULL, &rect, 0, NULL, flip);
    else
        return;
}

void Enemy::tracking(float dt, float playerX)
{
    float direction = 0.0f;

    // Determine direction: -1 if player is to the left, +1 if to the right, 0 if aligned
    if (x < playerX)
    {
        setFlip(SDL_FLIP_NONE);
        direction = 1.0f;
    }

    else //if (x > playerX)
    {
        setFlip(SDL_FLIP_HORIZONTAL);
        direction = -1.0f;
    }

    // Accelerate in the direction of the player
    ax = direction * 200.0f;  // Adjust 200.0f to control acceleration rate

    // Apply acceleration to velocity
    vx += ax * dt;

    // Optional: Clamp vx to prevent it from going too fast
    float maxSpeed = 500.0f;
    if (vx > maxSpeed) vx = maxSpeed;
    if (vx < -maxSpeed) vx = -maxSpeed;

    // Move the enemy
    x += vx * dt;
    rect.x = x;
}