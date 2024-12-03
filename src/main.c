/*
 * Copyright (c) 2018, 2019 Amine Ben Hassouna <amine.benhassouna@gmail.com>
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any
 * person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the
 * Software without restriction, including without
 * limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software
 * is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice
 * shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF
 * ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 * TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
 * SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 * IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

#include <time.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>

#include "game_context.h"

/* VERSION: v0.1 */

EMB_GameContext embCORE = { 0 };

int main(void)
{
    if (!EMB_InitLibs())
    {
        EMB_Quit();
        return 1;
    }
    
    srand(time(NULL));

    if (!EMB_InitGame())
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to load game resources and data.");
        EMB_Quit();
        return 1;
    }


    float delta = 0.0f;

    while (EMB_IsGameOpen())
    {
        EMB_HandleEvents();

        delta = EMB_GetDeltaTime();

        // I feel bad for EMB_Update, you have a very heavy task to do, forgive me lmao
        EMB_Update(delta);

        EMB_Render();
    }

    EMB_Quit();
    return 0;
}
