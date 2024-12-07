#include "player.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_render.h>
#include "../constants.h"
#include "../contexts/game_context.h"

bool EMB_InitPlayer(EMB_Player* player)
{
    player->lifes = 15;
    player->currScore = 0;

    player->speed = 230.0f;
    player->boosterImpulse = -150.0f;

    player->position = (SDL_FPoint){0.0f, 0.0f};
    player->velocity = (SDL_FPoint){0.0f, 0.0f};

    EMB_CreateTimer(&player->scoreTimer, 1.0f);
    EMB_StartTimer(&player->scoreTimer);
    player->hitbox = (SDL_FRect){0.0f, 0.0f, 46, 47};

    player->source = (SDL_Rect){0, 0, 14, 15};
    player->destination = (SDL_FRect){player->position.x, player->position.y, player->hitbox.w, player->hitbox.h};

    player->texture = IMG_LoadTexture(embCORE.window.renderer, "resources/gameplay/quote.png");
    if (player->texture == NULL)
    {
        return false;
    }

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

    player->destination.x = player->position.x;
    player->destination.y = player->position.y;

    player->hitbox.x = player->position.x;
    player->hitbox.y = player->position.y;
}

void EMB_UpdatePlayerTimers(EMB_Player *player, float delta)
{
    EMB_UpdateTimer(&player->scoreTimer, delta);

    SDL_Log("SCORE TIMER: %.2f\nSCORE: %d\n", player->scoreTimer.elapsed, player->currScore);

    if ( EMB_TimerHasStopped(&player->scoreTimer) )
    {
        player->currScore += 100;
        EMB_StartTimer(&player->scoreTimer);
    }
}

void EMB_RenderPlayer(const EMB_Player* player)
{
    SDL_SetRenderDrawColor(embCORE.window.renderer, 255, 192, 203, SDL_ALPHA_OPAQUE);
    SDL_RenderCopyF(embCORE.window.renderer, player->texture, &player->source, &player->destination);
}

void EMB_DestroyPlayer(EMB_Player* player)
{
    SDL_Log("Freeing player...");
    SDL_DestroyTexture(player->texture);
    /* Empty lol. Free textures and sounds */
}