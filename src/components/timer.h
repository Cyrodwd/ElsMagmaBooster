#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL_timer.h>
#include <stdbool.h>
#include <SDL2/SDL_stdinc.h>

typedef struct EMB_Timer {
    bool running;
    bool completed;
    
    float duration;
    float elapsed;
} EMB_Timer;

// Creates a new timer
void EMB_CreateTimer(EMB_Timer* timer, float duration);
// Update the time with frame time
void EMB_UpdateTimer(EMB_Timer* timer, float delta);
// Starts running the time of a timer
void EMB_StartTimer(EMB_Timer* timer);
// Resumes the timer if stopped
void EMB_ResumeTimer(EMB_Timer* timer);
// Stops the elapsed time of a timer (It doesn't reset it)
void EMB_StopTimer(EMB_Timer* timer);
// Resets the elapsed time of a timer (It doesn't stop it)
void EMB_ResetTimer(EMB_Timer* timer);
// Stops and resets the elapsed time of a timer
void EMB_StopAndResetTimer(EMB_Timer* timer);
// Function to check if timer is actually running or not
bool EMB_TimerIsRunning(const EMB_Timer* timer);
// Function to check if timer elasped time has stopped or reached to the max duration
bool EMB_TimerHasStopped(const EMB_Timer* timer);
// Returns the time elapsed between the last frame with the current one
float EMB_GetFrameTime(void);

#endif /* TIMER_H*/