#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <SDL2/SDL_rect.h>
#include <stdbool.h>

typedef enum {
    EMB_OBSTACLE_DIRECTION_HORIZONTAL,
    EMB_OBSTACLE_DIRECTION_VERTICAL
} EMB_ObstacleDirection;

typedef struct
{
    bool active;
    char padding[3]; // just padding lmao

    // Falling/Moving speed
    float speed;

    // Direction to spawn and move forward
    EMB_ObstacleDirection direction;

    union {
        float x; // Used only when direction is horizontal
        float y; // Used only when direction is vertical
    } velocity;

    SDL_FPoint position;
    SDL_FRect hitbox;
} EMB_Obstacle;

bool EMB_InitObstacle(EMB_Obstacle* obstacle, float speed, EMB_ObstacleDirection direction);
void EMB_UpdateObstacle(EMB_Obstacle* obstacle, float delta);
void EMB_RenderObstacle(const EMB_Obstacle* obstacle);
void EMB_DestroyObstacle(EMB_Obstacle* obstacle);

#endif /* OBSTACLE_H */