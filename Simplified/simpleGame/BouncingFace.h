#pragma once
#include "SDL.h"

using namespace std;

class BouncingFace {
   SDL_Surface* surface;
   SDL_Texture *t;
   SDL_Rect rect;
   float ax,ay,vx,vy,x,y; 
   bool ready;
   public:
   BouncingFace(SDL_Renderer *ren,
    float x0=0,float y0=0,
    float vx0=0,float vy0=0,
    float ax0=0,float ay0=0);   
   void bounceX();
   void bounceY();
   void bounce();
   void loop(float dt);
   void render(SDL_Renderer *ren);
};
