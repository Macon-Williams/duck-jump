#include "player.h"

extern Game game;

void moveDuck(Player* player, Timer* timer, bool moveable) {
    gravity(player, (double) timer->deltaTime);
    if (moveable)
        updateXVelocity(player, (double) timer->deltaTime);
}

void renderPlayerSprite(Player* player) {
    SDL_Rect renderQuad = {(int) player->loc_x, (int) player->loc_y, player->size_x, player->size_y};
    SDL_RenderCopy(game.renderer, player->duckSprite, &player->duckClip[player->frame], &renderQuad);
}

void updateXVelocity(Player* player, double deltaTime) {
    double acceleration;
    if (player->move_x) {
        acceleration = PLAYER_MOVEMENT_ACCELERAITON * 5 * player->move_x;
    } else {
        acceleration = -5 * player->velocity_x;
        if (fabs(player->velocity_x) < 1) player->velocity_x = 0;
    }

    player->velocity_x += acceleration * deltaTime;
    if (fabs(player->velocity_x) > MAX_PLAYER_SPEED) player->velocity_x = MAX_PLAYER_SPEED * player->move_x;
    player->loc_x += player->velocity_x * deltaTime;
}

void gravity(Player* player, double deltaTime) {
    //printf("Player gravity: %f\n delta time: %lf\nPlayer location: %lf", player->velocity_y, deltaTime, player->loc_y);
    player->velocity_y += (GRAVITY * deltaTime);
    player->loc_y += (player->velocity_y * deltaTime);
}
