#include <stdlib.h>
#include <iostream>
#include <vector>
#include "SDL.h"
#include "BouncingFace.h"

using namespace std;

   void BouncingFace::bounceX() { vx*=-1; }
   void BouncingFace::bounceY() { vy*=-1; }
   void BouncingFace::bounce() { // Bounce in both x and y
     bounceX();
     bounceY();
   }
   BouncingFace::BouncingFace(SDL_Renderer *ren,
      float ax0,float ay0,
      float vx0,float vy0,
      float x0,float y0) {
     ready=false;
     surface = SDL_LoadBMP("face.bmp");
     if (!surface){
        cerr << "Failed to load image"<<endl;
        return;
     }
     SDL_SetColorKey(surface,SDL_TRUE,
       SDL_MapRGBA(surface->format,0,255,0,255)
       );
     t=SDL_CreateTextureFromSurface(ren,surface);
     if (!t){
       cerr << "Failed to create texture" <<endl;
       return;
     }
      rect.x = 0; //the x coordinate
      rect.y = 0; //the y coordinate
      rect.w = 96; //the width of the texture
      rect.h = 96; //the height of the texture
      ax=ax0;
      ay=ay0;
      if (vx0==-1) vx=rand() % (100 - -100) + -100;  // rand()%(max-min)+min;
      else vx=vx0;
      if (vy0==-1) vy=rand() % (100 - -100) + -100;
      else vy=vy0;
      if (x0==-1) x=rand() % 800;
      else x=x0;
      if (y0==-1) y=rand()%600;
      else y=y0; 
     ready=true;
   }
   void BouncingFace::loop(float dt){
      vx+=ax*dt;
      vy+=ay*dt;
      x+=vx*dt;
      y+=vy*dt;
      rect.x=x;
      rect.y=y;
      if (rect.x>800-96) vx*=-1;
      if (rect.x<1)vx*=-1;
      if (rect.y>600-96) {
        ay*=-1;
        vy*=-1;
      }
      if (rect.y<1) {
        ay*=-1;
        vy*=-1;
      }
   }
   void BouncingFace::render(SDL_Renderer *ren){ SDL_RenderCopy(ren, t, NULL, &rect); }
