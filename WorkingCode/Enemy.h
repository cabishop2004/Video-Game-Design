#pragma once
#include "SDL.h"

class Enemy
{
    private:
        SDL_Surface* surface;
        SDL_Texture *t;
        SDL_Rect rect;
        float ax, ay, vx, vy, x, y;
        bool enabled;
        SDL_RendererFlip flip;
    public:
        //constructor
        Enemy(const char* name, SDL_Renderer *ren, bool e, int w, int h, float x0, float y0, float vx0, float vy0, float ax0, float ay0);

        //main loop
        void loop(float dt, float playerX);
        //renderer for the enemy
        void render(SDL_Renderer *ren);
        //allows enemy to track and follow player
        void tracking(float dt, float playerX);
        
        //getters and settters
        void setVx(float newVx) { vx = newVx; }  // Setter for horizontal velocity
        void setVy(float newVy) { vy = newVy; }  // Setter for vertical velocity
        void setFlip(SDL_RendererFlip fflip) { flip = fflip; }
        void setEnabled(bool e) { enabled = e; }
        SDL_RendererFlip getFlip() { return flip; }
        float getX() { return x; }  // Getter for X position
        bool getEnabled() { return enabled; } // Getter for enabled
};