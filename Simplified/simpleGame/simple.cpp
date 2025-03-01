#include <stdlib.h>
#include <iostream>
#include <vector>
#include "SDL.h"
#include "Game.h"
#include "BouncingFace.h"
#include "Background.h"

using namespace std;

class MyGame:public Game {
    float dt;
    BouncingFace *bf;//*bf2;
    vector<BouncingFace *> faces;
    Background *back;
  public:
    MyGame(int level=1):Game(){
        srand(level); 
        bf=new BouncingFace(getRen(),10,10);
        //bf2=new BouncingFace(getRen(),100,100);
        for (int i=0;i<level*10;i++)
           faces.push_back(new BouncingFace(getRen(),-1,-1,-1,-1,0,10));
        back=new Background(getRen());
        dt=.01; 
    }
    void loop() {
        bf->loop(dt);
        for(auto face:faces) face->loop(dt);
        //bf2->loop(dt);
        back->render(getRen());
        bf->render(getRen());
        //bf2->render(getRen());
        for(auto face:faces) face->render(getRen());  
        SDL_RenderPresent(getRen()); 
        SDL_Delay(1000.0*dt);
        SDL_Event event;
        if (SDL_PollEvent(&event)){
          if (event.type==SDL_KEYDOWN){
            if (event.key.keysym.sym==SDLK_ESCAPE) running=false;
            if (event.key.keysym.sym==SDLK_SPACE) bf->bounce();
          }
        }
    }
    ~MyGame(){
      delete bf;
      //delete bf2;
      delete back;
    }
};

int main(void)
{
  MyGame game(1);
  game.run();
  return 0;
}