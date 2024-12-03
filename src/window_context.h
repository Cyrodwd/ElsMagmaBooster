#ifndef WINDOW_CONTEXT_H
#define WINDOW_CONTEXT_H

#include <SDL2/SDL_render.h>
#include <stdbool.h>

typedef struct {
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool isReady;
} EMB_WindowContext;

// Creates a window lmao
bool EMB_CreateWindowContext(EMB_WindowContext* ctx, const char* title);
// Close the window and destroy the window context
void EMB_CloseWindowContext(EMB_WindowContext* ctx);
// Destroy the window and the renderer (Don't call it directly, use EMB_CloseWindowContext instead)
void EMB_DestroyWindowContext(EMB_WindowContext* ctx);
// Returns true if window is already, basically if it is still open
bool EMB_IsWindowReady(EMB_WindowContext* ctx);

/* Renderer */

// Clear window color
void EMB_ClearWindowContext(EMB_WindowContext* ctx);
// Display window renderer (SDL_RenderPresent lol)
static inline void EMB_DisplayWindowContext(EMB_WindowContext* ctx)
{
    SDL_RenderPresent(ctx->renderer);
}

#endif // WINDOW_CONTEXT_H