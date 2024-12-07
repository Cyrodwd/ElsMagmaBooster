#ifndef GAMEPLAY_SCREEN_H
#define GAMEPLAY_SCREEN_H

#include <SDL2/SDL_render.h>
#include "../entities/obstacle.h"
#include "../entities/player.h"

typedef struct {
    /* Textures */
    SDL_Texture* background;

    /* Entities */
    EMB_Player player;
    EMB_Obstacle obstacles[4];

    /* TODO: Timers */

    /* TODO: Sounds */

    /* TODO: Music */

} EMB_GameplayResources;

// Initialize resources that will be used in gameplay screen
bool EMB_InitGameplayScreen(EMB_GameplayResources* res);
// Update physics, collisions, etc., in game
void EMB_UpdateGameplayScreen(EMB_GameplayResources* res, float delta);
// Render objects in screen
void EMB_RenderGameplayScreen(EMB_GameplayResources* res);
// Reset objects positions, collisions, values, etc. when screen changed or restarted
void EMB_ResetGameplayScreen(EMB_GameplayResources* res);
// Destroys all resources
void EMB_DestroyGameplayScreen(EMB_GameplayResources* res);

#endif /* GAME_GAMEPLAY_SCREEN_H*/