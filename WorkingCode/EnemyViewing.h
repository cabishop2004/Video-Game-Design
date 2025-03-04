#ifndef MONSTERVIEWING_H
#define MONSTERVIEWING_H

#include <SDL.h>

class MonsterViewing {
    SDL_Texture *monsterTexture;
    SDL_Rect monsterRect;
    SDL_Renderer *renderer;

public:
    MonsterViewing(SDL_Renderer *ren, const char *filePath);
    ~MonsterViewing();
    void update(float dt);
    void render(SDL_Renderer *ren);
};

#endif
