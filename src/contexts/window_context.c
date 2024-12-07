#include <SDL2/SDL_hints.h>
#include <SDL2/SDL_log.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include "../constants.h"
#include "game_context.h"
#include "window_context.h"

static Uint32 frameStart = 0;

bool EMB_CreateWindowContext(EMB_WindowContext* ctx, const char* title, Uint32 fps)
{
    ctx->isReady = false;

    ctx->window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        EMB_RENDERER_WIDTH, EMB_RENDERER_HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    if (ctx->window == NULL)
    {
        EMB_ShowError();
        return false;
    }

    // Creating renderer
    ctx->renderer = SDL_CreateRenderer(ctx->window, -1, SDL_RENDERER_PRESENTVSYNC);

    if (ctx->renderer == NULL)
    {
        EMB_ShowError();
        return false;
    }

    // With this, the renderer will always keep this size (Screen size)
    if (SDL_RenderSetLogicalSize(ctx->renderer, EMB_RENDERER_WIDTH, EMB_RENDERER_HEIGHT) < 0)
    {
        EMB_ShowError();
        return false;
    }

    // Set render scale hint for nitid pixel-art
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"))
    {
        EMB_ShowError();
        return false;
    }

    ctx->fps = 0;
    ctx->fpsLimit = fps;
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

void EMB_SetFrameRate(EMB_WindowContext* ctx, unsigned fps)
{
    ctx->fpsLimit = SDL_clamp(fps, EMB_MIN_FPS, EMB_MAX_FPS); // Imagine playing at 0 or -1 FPS lmao
}

void EMB_UpdateFrameRate(EMB_WindowContext *ctx)
{
    Uint32 frameDelay = 1000 / ctx->fpsLimit;
    Uint32 currentTime = SDL_GetTicks();

    Uint32 frameTime = currentTime - frameStart;

    if (frameDelay > frameTime)
    {
        SDL_Delay(frameDelay - frameTime);
    }

    frameStart = SDL_GetTicks();
}