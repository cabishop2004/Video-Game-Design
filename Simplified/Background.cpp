#include <stdlib.h>
#include <iostream>
#include <vector>
#include "SDL.h"
#include "Background.h"

using namespace std;
    Background::Background(SDL_Renderer *ren) {
      ready=false;
      b = SDL_LoadBMP("background.bmp");
      if (!b){
          cerr << "Failed to load image"<<endl;
          return;
      }
      
      bt=SDL_CreateTextureFromSurface(ren,b);
      if (!bt){
        cerr << "Failed to create texture" <<endl;
        return;
      }
      brect.x = 0; //the x coordinate
      brect.y = 0; //the y coordinate
      brect.w = 800; //the width of the texture
      brect.h = 600; //the height of the texture
      ready=true;
    }
    void Background::render(SDL_Renderer *ren){ SDL_RenderCopy(ren, bt, NULL, &brect);  }


