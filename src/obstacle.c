#include "obstacle.h"
#include "constants.h"
#include "game_context.h"
#include "keyboard_context.h"
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_render.h>

static void EMB_UpdateObstaclePosition(EMB_Obstacle* obstacle, float delta);
static void EMB_ResetObstacle(EMB_Obstacle* obstacle);

bool EMB_InitObstacle(EMB_Obstacle *obstacle, float speed, EMB_ObstacleDirection direction)
{
    obstacle->hitbox = (SDL_FRect){0.0f, 0.0f, 16, 16 };
    obstacle->speed = speed;
    obstacle->direction = direction;

    EMB_ResetObstacle(obstacle);

    return true;
}

void EMB_UpdateObstacle(EMB_Obstacle *obstacle, float delta)
{
    if (EMB_GetKeyPressed(&embCORE.keyboard, SDL_SCANCODE_P))
    {
        obstacle->active = !obstacle->active;
    }

    if (EMB_GetKeyPressed(&embCORE.keyboard, SDL_SCANCODE_SPACE))
    {
        EMB_ResetObstacle(obstacle);
    }

    // Update hitbox
    obstacle->hitbox.x = obstacle->position.x;
    obstacle->hitbox.y = obstacle->position.y;

    if (obstacle->active)
    {
        if (EMB_HasIntersection(embCORE.Entities.player.hitbox, obstacle->hitbox))
        {
            SDL_Log("Collision detected!");
        }

        EMB_UpdateObstaclePosition(obstacle, delta);
    }
}

void EMB_RenderObstacle(const EMB_Obstacle *obstacle)
{
    const Uint8 color = obstacle->active ? 255 : 0;
    SDL_SetRenderDrawColor(embCORE.Display.window.renderer, color, 0, 0, 255);
    SDL_RenderFillRectF(embCORE.Display.window.renderer, &obstacle->hitbox);
}

void EMB_DestroyObstacle(EMB_Obstacle *obstacle)
{
    SDL_Log(".%2f. Freed.", obstacle->speed);
}

static void EMB_ResetObstacle(EMB_Obstacle* obstacle)
{
    obstacle->active = false;

    SDL_Log("POSITION: %.2f", obstacle->position.x);

    // Sets the position depending the direction
    if (obstacle->direction == EMB_OBSTACLE_DIRECTION_HORIZONTAL)
    {
        // Horizontal if you didn't read the condition lmao (left & right)
        obstacle->position.x = ( rand() % 2 == 0 ) ? 0.0f : EMB_SCREEN_WIDTH - 16; // 16 es un valor mágico por ahora, después le pongo un tamaño real
        obstacle->position.y = rand() % ( EMB_SCREEN_HEIGHT - 16 );
        obstacle->velocity.x = obstacle->position.x <= 0.0f ? 1 : -1;
    }
    else
    {
        // Vertical (default, up & down)
        obstacle->position.x = rand() % ( EMB_SCREEN_WIDTH - 16 );
        obstacle->position.y = ( rand() % 2 == 0 ) ? 0.0f : EMB_SCREEN_HEIGHT - 16;
        obstacle->velocity.y = obstacle->position.y <= 0.0f ? 1 : -1;
    }
}

static void EMB_UpdateObstaclePosition(EMB_Obstacle* obstacle, float delta)
{
    if (obstacle->direction == EMB_OBSTACLE_DIRECTION_HORIZONTAL)
    {
        obstacle->position.x += ( obstacle->velocity.x * obstacle->speed ) * delta;
    }
    else
    {
        obstacle->position.y += ( obstacle->velocity.y * obstacle->speed ) * delta;
    }
}