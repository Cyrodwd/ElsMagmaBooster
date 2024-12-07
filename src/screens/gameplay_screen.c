#include "gameplay_screen.h"
#include "../constants.h"
#include "../contexts/game_context.h"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_render.h>

/* Static functions declaration */

static bool InitObstacles(EMB_GameplayResources* res);

/* Public functions */

bool EMB_InitGameplayScreen(EMB_GameplayResources *res)
{
    res->background = IMG_LoadTexture(embCORE.window.renderer, "resources/gameplay/background.png");
    if (res->background == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "UNABLE TO LOAD TEXTURE: %s\n", SDL_GetError());
        return false;
    }

    if (!EMB_InitPlayer(&res->player))
    {
        SDL_DestroyTexture(res->background);
        return false;
    }

    if (!InitObstacles(res))
    {
        SDL_DestroyTexture(res->background);
        return false;
    }

    return true;
}

void EMB_UpdateGameplayScreen(EMB_GameplayResources *res, float delta)
{
    EMB_UpdatePlayerTimers(&res->player, delta);
    EMB_UpdatePlayerInput(&res->player, &embCORE.keyboard);
    EMB_UpdatePlayerPhysics(&res->player, delta);

    for (int i = 0; i < 4; i++)
    {
        EMB_UpdateObstacle(&res->obstacles[i], delta);
    }
}

void EMB_RenderGameplayScreen(EMB_GameplayResources *res)
{
    const SDL_Rect rect = { 0, 0, EMB_RENDERER_WIDTH, EMB_RENDERER_HEIGHT };
    SDL_RenderCopy(embCORE.window.renderer, res->background, &rect, &rect);

    EMB_RenderPlayer(&res->player);

    for (int i = 0; i < 4; i++)
    {
        EMB_RenderObstacle(&res->obstacles[i]);
    }
}

void EMB_DestroyGameplayScreen(EMB_GameplayResources *res)
{
    EMB_DestroyPlayer(&res->player);
    for (int i = 0; i < 4; i++)
    {
        EMB_DestroyObstacle(&res->obstacles[i]);
    }
    SDL_DestroyTexture(res->background);
}

/* Static functions definition */

static bool InitObstacles(EMB_GameplayResources* res)
{
    // Unknown Moon Piece
    if (!EMB_InitObstacle(&res->obstacles[0], 104.2f, EMB_OBSTACLE_DIRECTION_VERTICAL))
    {
        return false;
    }

    // Fire ball
    if (!EMB_InitObstacle(&res->obstacles[1], 240.0f, EMB_OBSTACLE_DIRECTION_HORIZONTAL))
    {
        EMB_DestroyObstacle(&res->obstacles[0]);
        return false;
    }

    // Acid
    if (!EMB_InitObstacle(&res->obstacles[2], 150.5f, EMB_OBSTACLE_DIRECTION_VERTICAL))
    {
        EMB_DestroyObstacle(&res->obstacles[0]);
        EMB_DestroyObstacle(&res->obstacles[1]);
        return false;
    }

    // Cake
    if (!EMB_InitObstacle(&res->obstacles[3], 200.4f, EMB_OBSTACLE_DIRECTION_HORIZONTAL))
    {
        for (int i=0; i < 3; i++)
        {
            EMB_DestroyObstacle(&res->obstacles[i]);
        }
        return false;
    }

    return true;
}