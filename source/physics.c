#include "physics.h"

void updateXVelocity(Player* player, double deltaTime) {
    double acceleration;
    if (player->move_x) {
        acceleration = player->move_x * PLAYER_MOVEMENT_ACCELERAITON;
        player->loc_x = player->loc_x + 300 * player->move_x * deltaTime + player->velocity_x * deltaTime + 0.5f * acceleration * deltaTime * deltaTime;
        player->velocity_x = player->velocity_x + acceleration * deltaTime;
        
    } else {
        player->velocity_x = 0;
        // if (player->velocity_x > 0) {
        //     player->velocity_x = player->velocity_x - 2;
        // } else if (player->velocity_x < 0) {
        //     player->velocity_x = player->velocity_x + 2;
        // }
    }
}

void gravity(Player* player, double deltaTime) {
    player->loc_y = player->loc_y + player->velocity_y * deltaTime + 0.5f * GRAVITY * deltaTime * deltaTime;
    player->velocity_y = player->velocity_y + GRAVITY * deltaTime;
}
