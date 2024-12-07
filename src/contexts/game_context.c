#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_video.h>
#include "game_context.h"

/* Static constants */

/* Static global variables */
static bool sdlReady = false;
static bool imgReady = false;
static bool mixReady = false;
static bool ttfReady = false;

/* Static functions declaration */

static bool EMB_InitSDL(void);
static bool EMB_InitIMG(void);
static bool EMB_InitMix(void);
static bool EMB_InitTTF(void);

/* Public functions implementations */

void EMB_ShowError(void)
{
    SDL_LogError(SDL_LOG_CATEGORY_ERROR,"Els: Magma Booster (*ERROR*): %s\n", SDL_GetError());
}

bool EMB_InitLibs(void)
{
    /* Initializing SDL libraries */

    if (!EMB_InitSDL()) return false;
    if (!EMB_InitIMG()) return false;
    if (!EMB_InitMix()) return false;
    if (!EMB_InitTTF()) return false;

    return true;
}

bool EMB_InitGameContext(EMB_GameContext* ctx, Uint32 fps)
{
    /* Display settings */

    if (!EMB_CreateWindowContext(&ctx->window, "Els: Magma Booster | Cyrodwd", fps))
    {
        EMB_ShowError();
        return false;
    }

    /* Screens */
    if (!EMB_InitGameplayScreen(&ctx->gameplay))
    {
        return false;
    }

    embCORE.currScreen = EMB_SCREEN_GAMEPLAY;

    return true;
}

void EMB_HandleEvents(EMB_GameContext* ctx)
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT) EMB_CloseWindowContext(&ctx->window);
    }
}

void EMB_UpdateGameContext(EMB_GameContext* ctx, float delta)
{
    /* TODO: Switch update behaviour between screens */

    EMB_UpdateGameplayScreen(&ctx->gameplay, delta);
}

void EMB_RenderGameContext(EMB_GameContext* ctx)
{
    EMB_ClearWindowContext(&ctx->window);

    /* Draw below owo */

    EMB_RenderGameplayScreen(&ctx->gameplay);

    /* Draw above -w- */

    EMB_DisplayWindowContext(&ctx->window);
}

void EMB_DestroyGameContext(EMB_GameContext *ctx)
{
    EMB_DestroyGameplayScreen(&ctx->gameplay);
}

bool EMB_IsGameOpen(EMB_GameContext* ctx)
{
    return EMB_IsWindowReady(&ctx->window);
}

void EMB_Quit(void)
{
    // Freeing SDL_ttf if initialized
    if (ttfReady)
    {
        TTF_Quit();
        ttfReady = false;
    }

    // Freeing SDL_mixer if initialized...
    if (mixReady)
    {
        Mix_CloseAudio();
        Mix_Quit();
        mixReady = false;
    }

    // Freeing SDL_image if initialized lmao.
    if (imgReady)
    {
        IMG_Quit();
        imgReady = false;
    }

    // SDL, literally freeing SDL.
    if (sdlReady)
    {
        SDL_Quit();
        sdlReady = false;
    }
}


/* General functions */

bool EMB_HasIntersection(SDL_FRect rect1, SDL_FRect rect2)
{
    return ( ( (rect1.x < ( rect2.x + rect2.w ) && ( rect1.x + rect1.w ) > rect2.x ) &&
        (rect1.y < ( rect2.y + rect2.h ) && ( rect1.y + rect1.h ) > rect2.y ) ) );
}

/* Static functions implementation */

static bool EMB_InitSDL(void)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
    {
        EMB_ShowError();
        return false;
    }

    sdlReady = true;
    return true;
}

static bool EMB_InitIMG(void)
{
    if ( IMG_Init(IMG_INIT_PNG) < 0 )
    {
        EMB_ShowError();
        return false;
    }

    imgReady = true;
    return true;
}

static bool EMB_InitMix(void)
{
    if ( Mix_Init(MIX_INIT_OGG) == 0 )
    {
        EMB_ShowError();
        return false;
    }

    mixReady = true; // Just to free Mixer if can't open audio

    /* Open the audio configurations */
    if ( Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0 )
    {
        EMB_ShowError();
        return false;
    }

    return true;
}

static bool EMB_InitTTF(void)
{
    if ( TTF_Init() < 0 )
    {
        EMB_ShowError();
        return false;
    }

    ttfReady = true;
    return true;
}