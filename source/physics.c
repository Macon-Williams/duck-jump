#include "physics.h"

void updateXVelocity(Player* player, float acceleration) {
    if (player->velocity_x <= 15 && player->velocity_x >= -15) { // Terminal veloctiy is 10
            player->velocity_x = player->velocity_x + (acceleration * player->movement_time_x);
    }
}

void updateYVelocity(Player* player, float acceleration) {
    if (player->velocity_y <= 15 && player->velocity_y >= -15) {
        player->velocity_y = player->velocity_y + acceleration;
    }
    player->loc_y = player->loc_y + player->velocity_y;
}