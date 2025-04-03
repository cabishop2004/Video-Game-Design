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
    bool showCyclops;
    bool showFury;
    SDL_Texture *pauseTexture;
    SDL_Texture *cyclopsTexture;
    SDL_Texture *furyTexture;
    SDL_RendererFlip flip;

public:
    MyGame(int level = 1) : Game(), paused(false), showCyclops(true), showFury(true), 
                            pauseTexture(nullptr), cyclopsTexture(nullptr), furyTexture(nullptr), flip(SDL_FLIP_NONE) {
        srand(level);
        bf = new BouncingFace(getRen(), 5, 200, 0, 0, 0, 600 - 96);
        back = new Background(getRen());
        dt = .01;

        // Load pause image
        SDL_Surface *pauseSurface = SDL_LoadBMP("pause.bmp");
        if (pauseSurface) {
            pauseTexture = SDL_CreateTextureFromSurface(getRen(), pauseSurface);
            SDL_FreeSurface(pauseSurface);
        } else {
            cerr << "Failed to load pause image" << endl;
        }

        // Load Cyclops image
        SDL_Surface *cyclopsSurface = SDL_LoadBMP("Cyclops.bmp");
        if (cyclopsSurface) {
            SDL_SetColorKey(cyclopsSurface, SDL_TRUE, SDL_MapRGB(cyclopsSurface->format, 0, 255, 0));
            cyclopsTexture = SDL_CreateTextureFromSurface(getRen(), cyclopsSurface);
            SDL_FreeSurface(cyclopsSurface);
        } else {
            cerr << "Failed to load Cyclops image" << endl;
        }

        // Load Fury image
        SDL_Surface *furySurface = SDL_LoadBMP("fury.bmp");
        if (furySurface) {
            SDL_SetColorKey(furySurface, SDL_TRUE, SDL_MapRGB(furySurface->format, 0, 255, 255)); // Green transparency
            furyTexture = SDL_CreateTextureFromSurface(getRen(), furySurface);
            SDL_FreeSurface(furySurface);
        } else {
            cerr << "Failed to load Fury image" << endl;
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

        // Render pause screen
        if (paused && pauseTexture) {
            SDL_Rect pauseRect = {200, 150, 400, 300};
            SDL_RenderCopy(getRen(), pauseTexture, NULL, &pauseRect);
        }

        // Render Cyclops if enabled
        if (showCyclops && cyclopsTexture) {
            SDL_Rect cyclopsRect = {800 - 378, 100, 378, 661};
            SDL_RenderCopy(getRen(), cyclopsTexture, NULL, &cyclopsRect);
        }

        // Render Fury if enabled
        if (showFury && furyTexture) {
            SDL_Rect furyRect = {200, 600 - 150, 150, 150}; // Position and size
            SDL_RenderCopy(getRen(), furyTexture, NULL, &furyRect);
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
                            flip = SDL_FLIP_HORIZONTAL;
                        }
                        break;
                    case SDLK_d:
                        if (!paused) {
                            bf->setVx(150);
                            flip = SDL_FLIP_NONE;
                        }
                        break;
                    case SDLK_m:
                        paused = !paused;
                        break;
                    case SDLK_l:
                        showCyclops = !showCyclops;
                        break;
                    case SDLK_k:
                        showFury = !showFury; // Toggle Fury display
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
            else if (event.type == SDL_MOUSEBUTTONDOWN) {  // Detect mouse click for attack
                if (event.button.button == SDL_BUTTON_LEFT && !paused) {
                    bf->attack();
                }
            }
        }
    }

    ~MyGame() {
        delete bf;
        delete back;
        if (pauseTexture) SDL_DestroyTexture(pauseTexture);
        if (cyclopsTexture) SDL_DestroyTexture(cyclopsTexture);
        if (furyTexture) SDL_DestroyTexture(furyTexture);
    }
};

int main(int argc, char *argv[]) {
    MyGame game(1);
    game.run();
    return 0;
}
