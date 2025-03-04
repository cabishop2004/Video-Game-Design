#include "EnemyViewing.h"
#include <iostream>

MonsterViewing::MonsterViewing(SDL_Renderer *ren, const char *filePath) : renderer(ren) {
    SDL_Surface *monsterSurface = SDL_LoadBMP(filePath);
    if (!monsterSurface) {
        std::cerr << "Failed to load monster image" << std::endl;
        monsterTexture = nullptr;
    } else {
        monsterTexture = SDL_CreateTextureFromSurface(renderer, monsterSurface);
        SDL_FreeSurface(monsterSurface);
    }

    monsterRect = {600, 300, 100, 100}; // Fixed position
}

MonsterViewing::~MonsterViewing() {
    if (monsterTexture) {
        SDL_DestroyTexture(monsterTexture);
    }
}

void MonsterViewing::update(float dt) {
    // Future logic: Could animate or move the monster
}

void MonsterViewing::render(SDL_Renderer *ren) {
    if (!monsterTexture) return;

    SDL_RenderCopy(ren, monsterTexture, NULL, &monsterRect);
}
