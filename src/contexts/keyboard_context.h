#ifndef KEYBOARD_CONTEXT_H
#define KEYBOARD_CONTEXT_H

#include <SDL2/SDL_keyboard.h>
#include <stdbool.h>

typedef struct
{
    Uint8 prevState[SDL_NUM_SCANCODES];
    Uint8 currState[SDL_NUM_SCANCODES];
} EMB_KeyboardState;

/* embCORE has its own keyboard state, so this function will modify it */

void EMB_InitKeyboard(EMB_KeyboardState* keyboard);
void EMB_UpdateKeyboard(EMB_KeyboardState* keyboard);
bool EMB_GetKeyDown(EMB_KeyboardState* keyboard, int key);
bool EMB_GetKeyPressed(EMB_KeyboardState* keyboard, int key);

#endif /* KEYBOARD_CONTEXT_H */