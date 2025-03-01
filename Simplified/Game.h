#pragma once
#include "SDL.h"

using namespace std;

class Game {
  SDL_Window *window;
  SDL_Renderer *ren;
  protected:
  bool running;
  public:
  SDL_Renderer *getRen();
  Game();
  void run();
  virtual void loop()=0;
};