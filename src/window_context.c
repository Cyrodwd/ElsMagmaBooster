#include <SDL2/SDL_log.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>
#include "constants.h"
#include "window_context.h"

bool EMB_CreateWindowContext(EMB_WindowContext* ctx, const char* title)
{
    ctx->isReady = false;

    ctx->window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        EMB_SCREEN_WIDTH, EMB_SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    if (ctx->window == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "UNABLE TO CREATE WINDOW: %s\n", SDL_GetError());
        return false;
    }

    // Creating renderer
    ctx->renderer = SDL_CreateRenderer(ctx->window, -1, SDL_RENDERER_PRESENTVSYNC);

    if (ctx->renderer == NULL)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "UNABLE TO CREATE RENDERER: %s\n", SDL_GetError());
        return false;
    }

    // With this, the renderer will always keep this size (Screen size)
    SDL_RenderSetLogicalSize(ctx->renderer, EMB_SCREEN_WIDTH, EMB_SCREEN_HEIGHT);

    ctx->isReady = true;

    return true;
}

void EMB_CloseWindowContext(EMB_WindowContext* ctx)
{
    ctx->isReady = false;
    EMB_DestroyWindowContext(ctx);
}

void EMB_DestroyWindowContext(EMB_WindowContext* ctx)
{
    if (ctx->renderer != NULL)
    {
        SDL_DestroyRenderer(ctx->renderer);
        ctx->renderer = NULL;
    }
    if (ctx->window != NULL)
    {
        SDL_DestroyWindow(ctx->window);
        ctx->window = NULL;
    }
}

bool EMB_IsWindowReady(EMB_WindowContext* ctx)
{
    return ctx->isReady;
}

void EMB_ClearWindowContext(EMB_WindowContext* ctx)
{
    SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 0, 255);
    SDL_RenderClear(ctx->renderer);
}