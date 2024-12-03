#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL_rect.h>
#include <stdbool.h>
#include "keyboard_context.h"

typedef struct {
    float speed;
    float boosterImpulse;

    SDL_FPoint velocity;
    SDL_FPoint position;

    SDL_FRect hitbox;
} EMB_Player;

/* Game is singleplayer, embCORE has its own player :U */

bool EMB_InitPlayer(EMB_Player* player);
void EMB_UpdatePlayerInput(EMB_Player* player, EMB_KeyboardState* keyboard);
void EMB_UpdatePlayerPhysics(EMB_Player* player, float delta);
void EMB_RenderPlayer(const EMB_Player* player);
void EMB_DestroyPlayer(EMB_Player* player);

#endif /* PLAYER_H */