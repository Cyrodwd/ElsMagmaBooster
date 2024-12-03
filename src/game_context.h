#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H

#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <stdbool.h>
#include "window_context.h"
#include "keyboard_context.h"
#include "obstacle.h"
#include "player.h"

typedef struct
{
    EMB_KeyboardState keyboard;

    struct {
        EMB_WindowContext window;
        Uint16 fpsLimit; // In-Game FPS Limit
    } Display;

    struct {
        SDL_Texture* gameplayBackground;
    } Textures;

    struct {
        EMB_Obstacle obstacle;
        EMB_Player player;
    } Entities;

    struct {
        Uint32 lastTickTime;
        float delta;
    } Clock;
} EMB_GameContext;

extern EMB_GameContext embCORE;

// Initialize SDL, SDL_image, SDL_mixer and SDL_ttf
bool EMB_InitLibs(void);
// Load resources and set variables
bool EMB_InitGame(void);
// Handle events
void EMB_HandleEvents(void);
// Update each frame positions
void EMB_Update(float delta);
// Render screen
void EMB_Render(void);
// Free resources
void EMB_Quit(void);
// Set target FPS (For future, this will be used until SETTINGS screens are implemented)
void EMB_SetLimitFPS(Uint16 fps);
// Display FPS during game as text
void EMB_DisplayFPS(void);
// Show errors with SDL_GetError
void EMB_ShowError(void);
// Returns true if game window stills open or running
bool EMB_IsGameOpen(void);
// Obtains the time between the last frame with the current one
float EMB_GetDeltaTime(void);

/* General functions */
// Checks collision between two rectangles
bool EMB_HasIntersection(SDL_FRect rect1, SDL_FRect rect2);



#endif