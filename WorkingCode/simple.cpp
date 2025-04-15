#include <stdlib.h>
#include <iostream>
#include <vector>
#include <SDL_main.h>
#include <SDL.h>
#include "Game.h"
#include "BouncingFace.h"
#include "Background.h"
#include "Enemy.h"

using namespace std;

float vx = 20;

class MyGame : public Game {
    float dt;
    BouncingFace *bf;
    Enemy *cyclops;
    Enemy *fury;
    vector<BouncingFace *> faces;
    Background *back;
    bool paused;
    // bool showCyclops;
    // bool showFury;
    bool mapMode;
    bool inAreaOne = false;
    bool inAreaTwo = false;
    bool inAreaThree = false;
    bool inAreaFour = false;
    bool running;

    SDL_Texture *pauseTexture;
    SDL_Texture *newAreaOneTexture;
    SDL_Texture *newAreaTwoTexture;
    SDL_Texture *newAreaThreeTexture;
    SDL_Texture *newAreaFourTexture;
    // SDL_Texture *cyclopsTexture;
    // SDL_Texture *furyTexture;
    SDL_Texture *mapTexture;
    SDL_Texture *greekTextTexture;

    SDL_RendererFlip flip;

public:
    MyGame(int level = 1) : Game(), paused(false), mapMode(false),inAreaOne(false), inAreaTwo(false), inAreaThree(false), inAreaFour(false), 
                            pauseTexture(nullptr), newAreaOneTexture(nullptr), newAreaTwoTexture(nullptr), newAreaThreeTexture(nullptr), newAreaFourTexture(nullptr),
                            running(true), mapTexture(nullptr), greekTextTexture(nullptr), flip(SDL_FLIP_NONE) {
        srand(level);
        bf = new BouncingFace(getRen(), 5, 200, 0, 0, 0, 600 - 96);
        back = new Background(getRen());
        //will eventually make a loop to read enemies from a file
        cyclops = new Enemy("Cyclops.bmp", getRen(), false, 378, 661, 422, 100, 0, 0, 0, 0);
        fury = new Enemy("fury.bmp", getRen(), true, 150, 150, 200, 450, 0, 0, 0, 0);
        dt = .01;

        // Load pause image
        SDL_Surface *pauseSurface = SDL_LoadBMP("pause.bmp");
        if (pauseSurface) {
            pauseTexture = SDL_CreateTextureFromSurface(getRen(), pauseSurface);
            SDL_FreeSurface(pauseSurface);
        } else {
            cerr << "Failed to load pause image" << endl;
        }

        // Load new area image one
        SDL_Surface *newAreaOneSurface = SDL_LoadBMP("areaOne.bmp");
        if (newAreaOneSurface) {
            newAreaOneTexture = SDL_CreateTextureFromSurface(getRen(), newAreaOneSurface);
            SDL_FreeSurface(newAreaOneSurface);
        } else {
            cerr << "Failed to load new area image 1" << endl;
        }
        SDL_Surface *newAreaTwoSurface = SDL_LoadBMP("areaTwo.bmp");
        if (newAreaTwoSurface) {
            newAreaTwoTexture = SDL_CreateTextureFromSurface(getRen(), newAreaTwoSurface);
            SDL_FreeSurface(newAreaTwoSurface);
        } else {
            cerr << "Failed to load new area image 2" << endl;
        }
        SDL_Surface *newAreaThreeSurface = SDL_LoadBMP("areaThree.bmp");
        if (newAreaThreeSurface) {
            newAreaThreeTexture = SDL_CreateTextureFromSurface(getRen(), newAreaThreeSurface);
            SDL_FreeSurface(newAreaThreeSurface);
        } else {
            cerr << "Failed to load new area image 3" << endl;
        }
        SDL_Surface *newAreaFourSurface = SDL_LoadBMP("areaFour.bmp");
        if (newAreaFourSurface) {
            newAreaFourTexture = SDL_CreateTextureFromSurface(getRen(), newAreaFourSurface);
            SDL_FreeSurface(newAreaFourSurface);
        } else {
            cerr << "Failed to load new area image 4" << endl;
        }

        // Load Cyclops image
        // SDL_Surface *cyclopsSurface = SDL_LoadBMP("Cyclops.bmp");
        // if (cyclopsSurface) {
        //     SDL_SetColorKey(cyclopsSurface, SDL_TRUE, SDL_MapRGB(cyclopsSurface->format, 0, 255, 0));
        //     cyclopsTexture = SDL_CreateTextureFromSurface(getRen(), cyclopsSurface);
        //     SDL_FreeSurface(cyclopsSurface);
        // } else {
        //     cerr << "Failed to load Cyclops image" << endl;
        // }

        // Load Fury image
        // SDL_Surface *furySurface = SDL_LoadBMP("fury.bmp");
        // if (furySurface) {
        //     SDL_SetColorKey(furySurface, SDL_TRUE, SDL_MapRGB(furySurface->format, 0, 255, 255));
        //     furyTexture = SDL_CreateTextureFromSurface(getRen(), furySurface);
        //     SDL_FreeSurface(furySurface);
        // } else {
        //     cerr << "Failed to load Fury image" << endl;
        // }

        // Load map image
        SDL_Surface* mapSurface = SDL_LoadBMP("map.bmp");
        if (mapSurface) {
            mapTexture = SDL_CreateTextureFromSurface(getRen(), mapSurface);
            SDL_FreeSurface(mapSurface);
        } else {
            cerr << "Failed to load map image" << endl;
        }
        // SDL_Surface* mapSurface = SDL_LoadBMP("areaOne.bmp");
        // if (mapSurface) {
        //     mapTexture = SDL_CreateTextureFromSurface(getRen(), mapSurface);
        //     SDL_FreeSurface(mapSurface);
        // } else {
        //     cerr << "Failed to load map image" << endl;
        // }
        
       
    }

    void loop() {
        // Process events
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
                    case SDLK_m:
                        
                        mapMode = !mapMode;
                        break;
                    case SDLK_SPACE:
                        if (!paused && !mapMode && bf->getY() >= 600 - 96)
                            bf->setVy(-280);
                        break;
                    case SDLK_a:
                        if (!paused && !mapMode) {
                            bf->setVx(-150);
                            flip = SDL_FLIP_HORIZONTAL;
                        }
                        break;
                    case SDLK_d:
                        if (!paused && !mapMode) {
                            bf->setVx(150);
                            flip = SDL_FLIP_NONE;
                        }
                        break;
    
                    
                    case SDLK_1:
                        if (mapMode) {
                            cout << "Selected new area 1" << endl;
                            inAreaOne = true;
                            inAreaTwo = inAreaThree = inAreaFour = false;
                            mapMode = false;  
                        }
                        break;
                    case SDLK_2:
                        if (mapMode) {
                            cout << "Selected new area 2" << endl;
                            inAreaTwo = true;
                            inAreaOne = inAreaThree = inAreaFour = false;
                            mapMode = false;
                        }
                        break;
                    case SDLK_3:
                        if (mapMode) {
                            cout << "Selected new area 3" << endl;
                            inAreaThree = true;
                            inAreaOne = inAreaTwo = inAreaFour = false;
                            mapMode = false;
                        }
                        break;
                    case SDLK_4:
                        if (mapMode) {
                            cout << "Selected new area 4" << endl;
                            inAreaFour = true;
                            inAreaOne = inAreaTwo = inAreaThree = false;
                            mapMode = false;
                        }
                        break;
                        
                    case SDLK_t:
                        
                        paused = !paused;
                        break;
                    case SDLK_l:
                        // showCyclops = !showCyclops;
                        cyclops->setEnabled(!cyclops->getEnabled());
                        break;
                    case SDLK_k:
                        // showFury = !showFury;
                        fury->setEnabled(!fury->getEnabled());
                        break;
                    case SDLK_b:
                        // Back to original area
                        cout << "Back to the original area" << endl;
                        inAreaOne = inAreaTwo = inAreaThree = inAreaFour = false;
                        mapMode = false;
                        paused  = false;
                        break;
                    default:
                        break;
                }
            }
            else if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_a:
                    case SDLK_d:
                        if (!paused && !mapMode)
                            bf->setVx(0);
                        break;
                    default:
                        break;
                }
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (event.button.button == SDL_BUTTON_LEFT && !paused && !mapMode)
                    bf->attack();
            }
        }
    
        
        if (!mapMode && !paused) {
            bf->loop(dt);
            cyclops->loop(dt, bf->getX());
            fury->loop(dt, bf->getX());
            for (auto face : faces)
                face->loop(dt);

        }
    
        
        SDL_RenderClear(getRen());
    
        
        if (mapMode && mapTexture) {
            // In map mode: hide the gameplay entirely and show only the map and any overlays.
            SDL_RenderCopy(getRen(), mapTexture, NULL, NULL);
            if (greekTextTexture) {
                SDL_Rect textRect = {100, 500, 600, 80};
                SDL_RenderCopy(getRen(), greekTextTexture, NULL, &textRect);
            }
        }
        else if (inAreaOne && newAreaOneTexture) {
            SDL_RenderCopy(getRen(), newAreaOneTexture, NULL, NULL);
        }
        else if (inAreaTwo && newAreaTwoTexture) {
            SDL_RenderCopy(getRen(), newAreaTwoTexture, NULL, NULL);
        }
        else if (inAreaThree && newAreaThreeTexture) {
            SDL_RenderCopy(getRen(), newAreaThreeTexture, NULL, NULL);
        }
        else if (inAreaFour && newAreaFourTexture) {
            SDL_RenderCopy(getRen(), newAreaFourTexture, NULL, NULL);
        }
        else {
            // If no other mode is active, render the original background.
            back->render(getRen());
        }
    
        // If we’re NOT in map mode, render the game objects 
        if (!mapMode) {
            bf->render(getRen(), flip);
            fury->render(getRen());
            cyclops->render(getRen());
            for (auto face : faces)
                face->render(getRen());
            // rest of the  elements or overlays now show (pause screen, cyclops, fury, etc.)
            if (paused && pauseTexture) {
                SDL_Rect pauseRect = {200, 150, 400, 300};
                SDL_RenderCopy(getRen(), pauseTexture, NULL, &pauseRect);
            }
            // if (showCyclops && cyclopsTexture) {
            //     SDL_Rect cyclopsRect = {800 - 378, 100, 378, 661};
            //     SDL_RenderCopy(getRen(), cyclopsTexture, NULL, &cyclopsRect);
            // }
            // if (showFury && furyTexture) {
            //     SDL_Rect furyRect = {200, 600 - 150, 150, 150};
            //     SDL_RenderCopy(getRen(), furyTexture, NULL, &furyRect);
            // }
        }
    
        SDL_RenderPresent(getRen());
        SDL_Delay(1000.0 * dt);
    }
    
    

    ~MyGame() {
        delete bf;
        //eventually make a loop to delete enemies
        delete cyclops;
        delete fury;
        delete back;
        if (pauseTexture) SDL_DestroyTexture(pauseTexture);
        if (newAreaOneTexture) SDL_DestroyTexture(newAreaOneTexture);
        if (newAreaTwoTexture) SDL_DestroyTexture(newAreaTwoTexture);
        if (newAreaThreeTexture) SDL_DestroyTexture(newAreaThreeTexture);
        if (newAreaFourTexture) SDL_DestroyTexture(newAreaFourTexture);

        // if (cyclopsTexture) SDL_DestroyTexture(cyclopsTexture);
        // if (furyTexture) SDL_DestroyTexture(furyTexture);
        if (mapTexture) SDL_DestroyTexture(mapTexture);
        if (greekTextTexture) SDL_DestroyTexture(greekTextTexture);
    }
};

int main(int argc, char *argv[]) {
    MyGame game(1);
    game.run();
    return 0;
}





























































































































































// #include <stdlib.h>
// #include <iostream>
// #include <vector>
// #include <SDL_main.h>
// #include <SDL.h>
// #include "Game.h"
// #include "BouncingFace.h"
// #include "Background.h"

// using namespace std;

// float vx = 20;

// class MyGame : public Game {
//     float dt;
//     BouncingFace *bf;
//     vector<BouncingFace *> faces;
//     Background *back;
//     bool paused;
//     bool showCyclops;
//     bool showFury;
//     SDL_Texture *pauseTexture;
//     SDL_Texture *cyclopsTexture;
//     SDL_Texture *furyTexture;
//     SDL_RendererFlip flip;

// public:
//     MyGame(int level = 1) : Game(), paused(false), showCyclops(true), showFury(true), 
//                             pauseTexture(nullptr), cyclopsTexture(nullptr), furyTexture(nullptr), flip(SDL_FLIP_NONE) {
//         srand(level);
//         bf = new BouncingFace(getRen(), 5, 200, 0, 0, 0, 600 - 96);
//         back = new Background(getRen());
//         dt = .01;

//         // Load pause image
//         SDL_Surface *pauseSurface = SDL_LoadBMP("pause.bmp");
//         if (pauseSurface) {
//             pauseTexture = SDL_CreateTextureFromSurface(getRen(), pauseSurface);
//             SDL_FreeSurface(pauseSurface);
//         } else {
//             cerr << "Failed to load pause image" << endl;
//         }

//         // Load Cyclops image
//         SDL_Surface *cyclopsSurface = SDL_LoadBMP("Cyclops.bmp");
//         if (cyclopsSurface) {
//             SDL_SetColorKey(cyclopsSurface, SDL_TRUE, SDL_MapRGB(cyclopsSurface->format, 0, 255, 0));
//             cyclopsTexture = SDL_CreateTextureFromSurface(getRen(), cyclopsSurface);
//             SDL_FreeSurface(cyclopsSurface);
//         } else {
//             cerr << "Failed to load Cyclops image" << endl;
//         }

//         // Load Fury image
//         SDL_Surface *furySurface = SDL_LoadBMP("fury.bmp");
//         if (furySurface) {
//             SDL_SetColorKey(furySurface, SDL_TRUE, SDL_MapRGB(furySurface->format, 0, 255, 255)); // Green transparency
//             furyTexture = SDL_CreateTextureFromSurface(getRen(), furySurface);
//             SDL_FreeSurface(furySurface);
//         } else {
//             cerr << "Failed to load Fury image" << endl;
//         }
//     }

//     void loop() {
//         if (!paused) {
//             bf->loop(dt);
//             for (auto face : faces) face->loop(dt);
//         }

//         back->render(getRen());

//         // Render character with flipping
//         bf->render(getRen(), flip);

//         for (auto face : faces) face->render(getRen());

//         // Render pause screen
//         if (paused && pauseTexture) {
//             SDL_Rect pauseRect = {200, 150, 400, 300};
//             SDL_RenderCopy(getRen(), pauseTexture, NULL, &pauseRect);
//         }

//         // Render Cyclops if enabled
//         if (showCyclops && cyclopsTexture) {
//             SDL_Rect cyclopsRect = {800 - 378, 100, 378, 661};
//             SDL_RenderCopy(getRen(), cyclopsTexture, NULL, &cyclopsRect);
//         }

//         // Render Fury if enabled
//         if (showFury && furyTexture) {
//             SDL_Rect furyRect = {200, 600 - 150, 150, 150}; // Position and size
//             SDL_RenderCopy(getRen(), furyTexture, NULL, &furyRect);
//         }

//         SDL_RenderPresent(getRen());
//         SDL_Delay(1000.0 * dt);

//         SDL_Event event;
//         while (SDL_PollEvent(&event)) {
//             if (event.type == SDL_QUIT) {
//                 running = false;
//             }
//             else if (event.type == SDL_KEYDOWN) {
//                 switch (event.key.keysym.sym) {
//                     case SDLK_ESCAPE:
//                         running = false;
//                         break;
//                     case SDLK_SPACE:
//                         if (!paused && bf->getY() >= 600 - 96) {
//                             bf->setVy(-280);
//                         }
//                         break;
//                     case SDLK_a:
//                         if (!paused) {
//                             bf->setVx(-150);
//                             flip = SDL_FLIP_HORIZONTAL;
//                         }
//                         break;
//                     case SDLK_d:
//                         if (!paused) {
//                             bf->setVx(150);
//                             flip = SDL_FLIP_NONE;
//                         }
//                         break;
//                     case SDLK_m:
//                         paused = !paused;
//                         break;
//                     case SDLK_l:
//                         showCyclops = !showCyclops;
//                         break;
//                     case SDLK_k:
//                         showFury = !showFury; // Toggle Fury display
//                         break;
//                 }
//             }
//             else if (event.type == SDL_KEYUP) {
//                 switch (event.key.keysym.sym) {
//                     case SDLK_a:
//                     case SDLK_d:
//                         if (!paused) bf->setVx(0);
//                         break;
//                 }
//             }
//             else if (event.type == SDL_MOUSEBUTTONDOWN) {  // Detect mouse click for attack
//                 if (event.button.button == SDL_BUTTON_LEFT && !paused) {
//                     bf->attack();
//                 }
//             }
//         }
//     }

//     ~MyGame() {
//         delete bf;
//         delete back;
//         if (pauseTexture) SDL_DestroyTexture(pauseTexture);
//         if (cyclopsTexture) SDL_DestroyTexture(cyclopsTexture);
//         if (furyTexture) SDL_DestroyTexture(furyTexture);
//     }
// };

// int main(int argc, char *argv[]) {
//     MyGame game(1);
//     game.run();
//     return 0;
// }
