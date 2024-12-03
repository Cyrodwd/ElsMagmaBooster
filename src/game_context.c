#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include "constants.h"
#include "obstacle.h"
#include "game_context.h"

/* Static constants */

/* Static global variables */
static bool sdlReady = false;
static bool imgReady = false;
static bool mixReady = false;
static bool ttfReady = false;

static bool imageReady = false;

/* Static functions declaration */

static bool EMB_InitSDL(void);
static bool EMB_InitIMG(void);
static bool EMB_InitMix(void);
static bool EMB_InitTTF(void);


static void EMB_InitDelta(void);
static void EMB_UpdateDelta(Uint32 tickTime);

static void EMB_InitLimitFPS(void);
static void EMB_UpdateLimitFPS(Uint32 tickTime);

static void EMB_InitFrames(void);
static void EMB_UpdateFrames(void);

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

bool EMB_InitGame(void)
{
    /* Display settings */

    if (!EMB_CreateWindowContext(&embCORE.Display.window, "Els: Magma Booster | Cyrodwd"))
    {
        EMB_ShowError();
        return false;
    }

    /* Input */
    EMB_InitKeyboard(&embCORE.keyboard);

    /* Clock */
    EMB_InitFrames();

    /*  Textures */
    embCORE.Textures.gameplayBackground = IMG_LoadTexture(embCORE.Display.window.renderer, "resources/scr_gp_background.png");

    if (embCORE.Textures.gameplayBackground == NULL)
    {
        EMB_ShowError();
        return false;
    }
    imageReady = true;

    /* Sounds */

    /* Music */

    /* Fonts */

    /* EMB structures (player, obstacles, etc.) */
    if (!EMB_InitPlayer(&embCORE.Entities.player))
    {
        SDL_DestroyTexture(embCORE.Textures.gameplayBackground);
        return false;
    }

    if (!EMB_InitObstacle(&embCORE.Entities.obstacle, 140.0f, EMB_OBSTACLE_DIRECTION_VERTICAL))
    {
        EMB_DestroyPlayer(&embCORE.Entities.player);
        SDL_DestroyTexture(embCORE.Textures.gameplayBackground);
        return false;
    }

    return true;
}

void EMB_HandleEvents(void)
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT) EMB_CloseWindowContext(&embCORE.Display.window);
    }
}

void EMB_Update(float delta)
{
    /* Updatable behaviors */

    EMB_UpdateKeyboard(&embCORE.keyboard);

    EMB_UpdatePlayerInput(&embCORE.Entities.player, &embCORE.keyboard);
    EMB_UpdatePlayerPhysics(&embCORE.Entities.player, delta);

    EMB_UpdateObstacle(&embCORE.Entities.obstacle, delta);

    EMB_DisplayFPS();

    EMB_UpdateFrames();

    /* TODO: Switch update behaviour between screens */
}

void EMB_Render()
{
    EMB_ClearWindowContext(&embCORE.Display.window);

    /* Draw here bruh */

    const SDL_Rect rect = { 0, 0, EMB_SCREEN_WIDTH, EMB_SCREEN_HEIGHT };
    if (embCORE.Textures.gameplayBackground != NULL) SDL_RenderCopy(embCORE.Display.window.renderer, embCORE.Textures.gameplayBackground, &rect, &rect);

    EMB_RenderPlayer(&embCORE.Entities.player);

    EMB_RenderObstacle(&embCORE.Entities.obstacle);

    /* End Drawing */

    EMB_DisplayWindowContext(&embCORE.Display.window);
}

void EMB_Quit(void)
{
    /* Free resources here */
    if (imageReady)
    {
        SDL_DestroyTexture(embCORE.Textures.gameplayBackground);
        SDL_Log("Texture freed");
        imageReady = false;
    }

    EMB_DestroyObstacle(&embCORE.Entities.obstacle);
    EMB_DestroyPlayer(&embCORE.Entities.player);

    /* Freeing libraries */

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

void EMB_SetLimitFPS(Uint16 fps)
{
    embCORE.Display.fpsLimit = fps;
}

void EMB_DisplayFPS(void)
{
    static Uint32 frameCount = 0;
    static Uint32 lastTime = 0;
    Uint32 currentTime = SDL_GetTicks();

    frameCount++;

    if (currentTime - lastTime >= 1000)
    {
        float fps = frameCount * EMB_MIL2SEC / (currentTime - lastTime);
        SDL_Log("FPS: %.2f", fps);

        frameCount = 0;
        lastTime = currentTime;
    }
}

bool EMB_IsGameOpen(void)
{
    return EMB_IsWindowReady(&embCORE.Display.window);
}

float EMB_GetDeltaTime()
{
    return embCORE.Clock.delta;
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

/* Frame functions */

static void EMB_InitFrames(void)
{
    EMB_InitLimitFPS();
    EMB_InitDelta();
}

static void EMB_UpdateFrames(void)
{
    Uint32 tickTime = SDL_GetTicks();

    EMB_UpdateDelta(tickTime);
    EMB_UpdateLimitFPS(tickTime);
}

/* Delta time */

static void EMB_InitDelta(void)
{
    embCORE.Clock.lastTickTime = 0;
    embCORE.Clock.delta = 0;
}

static void EMB_UpdateDelta(Uint32 tickTime)
{
    embCORE.Clock.delta = ( tickTime - embCORE.Clock.lastTickTime ) / EMB_MIL2SEC;
    embCORE.Clock.lastTickTime = tickTime;
}

/* FPS limit */

static void EMB_InitLimitFPS(void)
{
    embCORE.Display.fpsLimit = EMB_DEFAULT_FPS_LIMIT;
}

static void EMB_UpdateLimitFPS(Uint32 tickTime)
{
    Uint32 frameDelay = 1000 / embCORE.Display.fpsLimit;
    Uint32 frameTime = SDL_GetTicks() - tickTime;

    if (frameDelay > frameTime)
    {
        SDL_Delay(frameDelay - frameTime);
    }
}