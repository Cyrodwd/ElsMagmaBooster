#include "timer.h"
#include <SDL2/SDL_timer.h>

static Uint32 lastFrameTime = 0;

void EMB_CreateTimer(EMB_Timer *timer, float duration)
{
    timer->completed = false;
    timer->running = false;

    timer->duration = duration;
    timer->elapsed = 0.0f;
}

void EMB_UpdateTimer(EMB_Timer *timer, float delta)
{
    if (timer->running)
    {
        timer->elapsed += delta;

        if(timer->elapsed >= timer->duration)
        {
            timer->completed = true;
            EMB_StopTimer(timer);
        }
    }
}

void EMB_StartTimer(EMB_Timer *timer)
{
    timer->running = true;
    EMB_ResetTimer(timer);
}

void EMB_ResumeTimer(EMB_Timer *timer)
{
    if (!timer->running && !timer->completed)
        timer->running = true;
}

void EMB_StopTimer(EMB_Timer *timer)
{
    timer->running = false;
}

void EMB_ResetTimer(EMB_Timer *timer)
{
    timer->elapsed = 0.0f;
    timer->completed = false;
}

void EMB_StopAndResetTimer(EMB_Timer *timer){
    EMB_StopTimer(timer);
    EMB_ResetTimer(timer);
}

bool EMB_TimerIsRunning(const EMB_Timer *timer)
{
    return timer->running;
}

bool EMB_TimerHasStopped(const EMB_Timer *timer)
{
    return ( !timer->running || timer->completed );
}

float EMB_GetFrameTime(void)
{
    Uint32 currTime = SDL_GetTicks();
    float frameTime = ( currTime - lastFrameTime ) / 1000.0f;
    lastFrameTime = currTime;
    return frameTime;
}

