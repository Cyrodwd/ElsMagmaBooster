#ifndef PLAYER_H
#define PLAYER_H

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <stdbool.h>
#include "../components/timer.h"
#include "../contexts/keyboard_context.h"

typedef struct {
    Uint8 lifes;
    short currScore;
    char padding;
    
    float speed;
    float boosterImpulse;

    SDL_FPoint velocity;
    SDL_FPoint position;

    EMB_Timer scoreTimer;
    SDL_FRect hitbox;

    SDL_Rect source;
    SDL_FRect destination;
    SDL_Texture* texture;
} EMB_Player;

bool EMB_InitPlayer(EMB_Player* player);
void EMB_UpdatePlayerInput(EMB_Player* player, EMB_KeyboardState* keyboard);
void EMB_UpdatePlayerPhysics(EMB_Player* player, float delta);
void EMB_UpdatePlayerTimers(EMB_Player* player, float delta);
void EMB_RenderPlayer(const EMB_Player* player);
void EMB_DestroyPlayer(EMB_Player* player);

#endif /* PLAYER_H */