#include <stdlib.h>
#include <iostream>
#include <vector>
#include <SDL.h>
#include "Game.h"

using namespace std;

void KarlsQuit() {
  cerr << "Karl Wins"<<endl;
  SDL_Quit();
}

  SDL_Renderer *Game::getRen(){ return ren;}
  Game::Game() {
    running=true;
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
      cerr << endl << "Unable to initialize SDL: " <<SDL_GetError()<<endl;
      running=false;
      return;
    }
    atexit(KarlsQuit);
    window = SDL_CreateWindow("Greek Video Game",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800, 600,0);
    if(!window){
        cerr << "Failed to create window"<<endl;
        running=false;
        return;
    }
    ren=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    if (!ren){
        cerr << "Failed to create Renderer"<<endl;
        running=false;
        return;
    }
  }
  void Game::run() {
    while (running){
      loop();
    }
  }
