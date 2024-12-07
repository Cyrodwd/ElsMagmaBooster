#include "keyboard_context.h"

void EMB_InitKeyboard(EMB_KeyboardState* keyboard)
{
    SDL_memset(keyboard, 0, SDL_NUM_SCANCODES);
}

void EMB_UpdateKeyboard(EMB_KeyboardState* keyboard)
{
    SDL_memcpy(keyboard->prevState, keyboard->currState, sizeof(keyboard->prevState));

    const Uint8* actualState = SDL_GetKeyboardState(NULL);
    SDL_memcpy(keyboard->currState, actualState, sizeof(keyboard->currState));
}

bool EMB_GetKeyDown(EMB_KeyboardState* keyboard, int key)
{
    bool down = false;

    if (key > 0 && key < SDL_NUM_SCANCODES)
    {
        if (keyboard->currState[key] == 1) down = true;
    }

    return down;
}

bool EMB_GetKeyPressed(EMB_KeyboardState* keyboard, int key)
{
    bool pressed = false;

    if (key > 0 && key < SDL_NUM_SCANCODES)
    {
        if (keyboard->prevState[key] == 0 && keyboard->currState[key] == 1) pressed = true;
    }

    return pressed;
}