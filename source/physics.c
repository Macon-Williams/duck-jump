#include "physics.h"

void updateXVelocity(Player* player, float deltaTime) {
    float acceleration;
    if (player->move_x) {
        acceleration = player->move_x * PLAYER_MOVEMENT_ACCELERAITON;
        player->velocity_x = player->velocity_x + acceleration;

    } else {
        if (player->velocity_x > 0) {
            player->velocity_x = player->velocity_x - 2;
        } else if (player->velocity_x < 0) {
            player->velocity_x = player->velocity_x + 2;
        }
    }

    player->loc_x = player->loc_x + (player->velocity_x * deltaTime);
}

void gravity(Player* player, float deltaTime) {
    player->velocity_y = player->velocity_y + GRAVITY;
    player->loc_y = player->loc_y + (player->velocity_y * deltaTime);
}