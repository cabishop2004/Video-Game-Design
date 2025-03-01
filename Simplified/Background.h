#pragma once
#include "SDL.h"

using namespace std;

class Background{
    SDL_Surface* b;
    SDL_Texture *bt;
    SDL_Rect brect;
    bool ready;
  public:
    Background(SDL_Renderer *ren);
    void render(SDL_Renderer *ren);
};

