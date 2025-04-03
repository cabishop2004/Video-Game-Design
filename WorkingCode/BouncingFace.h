#pragma once
#include "SDL.h"

class BouncingFace {
   SDL_Surface* surface;
   SDL_Texture *t;
   SDL_Rect rect;
   float ax, ay, vx, vy, x, y;
   bool ready;
   bool attacking;
   float attackTimer;
   const float attackDuration = 0.3f; // Attack lasts 0.3 seconds

public:
   BouncingFace(SDL_Renderer *ren, float x0 = 0, float y0 = 0, float vx0 = 0, float vy0 = 0, float ax0 = 0, float ay0 = 0);
   
   void bounceX();
   void bounceY();
   void bounce();
   void loop(float dt);
   void render(SDL_Renderer *ren, SDL_RendererFlip flip = SDL_FLIP_NONE);

   void setVx(float newVx) { vx = newVx; }  // Setter for horizontal velocity
   void setVy(float newVy) { vy = newVy; }  // Setter for vertical velocity
   float getY() { return y; }  // Getter for Y position

   void attack();  // Triggers attack
};
