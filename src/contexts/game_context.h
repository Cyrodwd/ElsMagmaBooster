#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <stdbool.h>
#include "window_context.h"
#include "keyboard_context.h"
#include "../screens/gameplay_screen.h"
#include "../entities/obstacle.h"
#include "../entities/player.h"

typedef enum { EMB_SCREEN_MENU, EMB_SCREEN_GAMEPLAY, EMB_SCREEN_GAMEOVER } EMB_Screens;

typedef struct
{
    EMB_Screens currScreen;
    
    Uint32 score;

    EMB_WindowContext window;
    EMB_GameplayResources gameplay;
    EMB_KeyboardState keyboard;

} EMB_GameContext;

extern EMB_GameContext embCORE;

// Initialize SDL, SDL_image, SDL_mixer and SDL_ttf
bool EMB_InitLibs(void);
// Load resources and set variables
bool EMB_InitGameContext(EMB_GameContext* ctx, Uint32 fps);
// Handle events
void EMB_HandleEvents(EMB_GameContext* ctx);
// Update each frame positions
void EMB_UpdateGameContext(EMB_GameContext* ctx, float delta);
// Render screen
void EMB_RenderGameContext(EMB_GameContext* ctx);

void EMB_DestroyGameContext(EMB_GameContext* ctx);
// Free resources
void EMB_Quit(void);
// Show errors with SDL_GetError
void EMB_ShowError(void);
// Returns true if game window stills open or running
bool EMB_IsGameOpen(EMB_GameContext* ctx);

/* General functions */
// Checks collision between two rectangles
bool EMB_HasIntersection(SDL_FRect rect1, SDL_FRect rect2);



#endif