#include <stdlib.h>
#include <iostream>
#include <vector>
#include <SDL_main.h>
#include <SDL.h>
#include "Game.h"
#include "BouncingFace.h"
#include "Background.h"

using namespace std;

float vx = 20;

class MyGame : public Game {
    float dt;
    BouncingFace *bf;
    vector<BouncingFace *> faces;
    Background *back;
    bool paused; 
    SDL_Texture *pauseTexture;
    SDL_RendererFlip flip; // Flip state for character

public:
    MyGame(int level = 1) : Game(), paused(false), pauseTexture(nullptr), flip(SDL_FLIP_NONE) {
        srand(level);
        bf = new BouncingFace(getRen(), 5, 200, 0, 0, 0, 600 - 96);
        back = new Background(getRen());
        dt = .01;

        SDL_Surface *pauseSurface = SDL_LoadBMP("pause.bmp");
        if (pauseSurface) {
            pauseTexture = SDL_CreateTextureFromSurface(getRen(), pauseSurface);
            SDL_FreeSurface(pauseSurface);
        } else {
            cerr << "Failed to load pause image" << endl;
        }
    }

    void loop() {
        if (!paused) {
            bf->loop(dt);
            for (auto face : faces) face->loop(dt);
        }

        back->render(getRen());

        // Render character with flipping
        bf->render(getRen(), flip);

        for (auto face : faces) face->render(getRen());

        if (paused && pauseTexture) {
            SDL_Rect pauseRect = {200, 150, 400, 300};
            SDL_RenderCopy(getRen(), pauseTexture, NULL, &pauseRect);
        }

        SDL_RenderPresent(getRen());
        SDL_Delay(1000.0 * dt);

        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        running = false;
                        break;
                    case SDLK_SPACE:
                        if (!paused && bf->getY() >= 600 - 96) {
                            bf->setVy(-200);
                        }
                        break;
                    case SDLK_a:
                        if (!paused) {
                            bf->setVx(-150);
                            flip = SDL_FLIP_HORIZONTAL; // Flip left
                        }
                        break;
                    case SDLK_d:
                        if (!paused) {
                            bf->setVx(150);
                            flip = SDL_FLIP_NONE; // Reset flip (right)
                        }
                        break;
                    case SDLK_m:
                        paused = !paused;
                        break;
                }
            }
            else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_a:
                    case SDLK_d:
                        if (!paused) bf->setVx(0);
                        break;
                }
            }
        }
    }

    ~MyGame() {
        delete bf;
        delete back;
        if (pauseTexture) SDL_DestroyTexture(pauseTexture);
    }
};

int main(int argc, char *argv[]) {
    MyGame game(1);
    game.run();
    return 0;
}
