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

#include <SDL2/SDL_log.h>
#include <stdlib.h>

#include "components/timer.h"
#include "constants.h"
#include "contexts/game_context.h"
#include "contexts/keyboard_context.h"
#include "contexts/window_context.h"

/* VERSION: v0.1.1 */

EMB_GameContext embCORE = { 0 };

int main(void)
{
    if (!EMB_InitLibs())
    {
        EMB_Quit();
        return 1;
    }
    
    srand(time(NULL));

    if (!EMB_InitGameContext(&embCORE, EMB_DEFAULT_FPS_LIMIT))
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Unable to load game resources and data.");
        EMB_Quit();
        return 1;
    }

    EMB_InitKeyboard(&embCORE.keyboard);

    float delta = 0.0f;

    while (EMB_IsGameOpen(&embCORE))
    {
        EMB_HandleEvents(&embCORE);

        delta = EMB_GetFrameTime();

        EMB_UpdateKeyboard(&embCORE.keyboard);
        EMB_UpdateGameContext(&embCORE, delta);
        
        EMB_RenderGameContext(&embCORE);
        EMB_UpdateFrameRate(&embCORE.window);
    }

    EMB_DestroyGameContext(&embCORE);
    EMB_Quit();
    return 0;
}
