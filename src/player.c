#include <SDL2/SDL_log.h>
#include "constants.h"
#include "game_context.h"

bool EMB_InitPlayer(EMB_Player* player)
{
    player->hitbox = (SDL_FRect){0.0f, 0.0f, 32, 32};

    player->speed = 230.0f;
    player->boosterImpulse = -150.0f;

    player->position = (SDL_FPoint){0.0f, 0.0f};
    player->velocity = (SDL_FPoint){0.0f, 0.0f};

    return true;
}

void EMB_UpdatePlayerInput(EMB_Player *player, EMB_KeyboardState *keyboard)
{
    player->velocity.x = ( EMB_GetKeyDown(keyboard, EMB_INPUT_RIGHT) - EMB_GetKeyDown(keyboard, EMB_INPUT_LEFT) );

    // Jump
    if( EMB_GetKeyDown(keyboard, EMB_INPUT_BOOST) )
    {
        player->velocity.y = player->boosterImpulse;
    }
}

void EMB_UpdatePlayerPhysics(EMB_Player* player, float delta)
{
    player->velocity.y += EMB_GRAVITY * delta;

    player->position.x += ( player->velocity.x * player->speed ) * delta;
    player->position.y += player->velocity.y * delta;

    player->hitbox.x = player->position.x;
    player->hitbox.y = player->position.y;
}

void EMB_RenderPlayer(const EMB_Player* player)
{
    SDL_SetRenderDrawColor(embCORE.Display.window.renderer, 255, 192, 203, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRectF(embCORE.Display.window.renderer, &player->hitbox);
}

void EMB_DestroyPlayer(EMB_Player* player)
{
    SDL_Log("Freeing player...");
    (void) player;
    /* Empty lol. Free textures and sounds */
}