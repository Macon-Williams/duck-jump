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

void checkNearPlatform(Player* player, Platform* platform) {
    if (player->loc_x > platform->loc_x && player->loc_x < (platform->loc_x + platform->size_x)) {
        if (player->loc_y + player->size_y >= platform->loc_y - 50) { // 50 pixels away from the platform, switch to frame 2
            player->frame = 1;
        } else {
            player->frame = 0;
        }
    } else {
        player->frame = 0;
    }
}

void checkCollision(Player* player, Platform* platform) {
    if (player->loc_x > platform->loc_x && player->loc_x < (platform->loc_x + platform->size_x)) {
        if (player->loc_y + player->size_y >= platform->loc_y)
            player->velocity_y = -(JUMP_HEIGHT); // Jump
    }
}

// TODO: Need better X movement for duck
void updateXVelocity(Player* player, double deltaTime) {
    double acceleration;
    if (player->move_x) {
        acceleration = player->move_x * PLAYER_MOVEMENT_ACCELERAITON;
        if (player->velocity_x < 500 || player->velocity_x > 500) {

            player->loc_x = player->loc_x + 300 * player->move_x * deltaTime + player->velocity_x * deltaTime + 0.5f * acceleration * deltaTime * deltaTime;
            player->velocity_x = player->velocity_x + acceleration * deltaTime;
        }
    } else {
        player->velocity_x = 0;
    }
    
}

void gravity(Player* player, double deltaTime) {
    player->loc_y = player->loc_y + player->velocity_y * deltaTime + 0.5f * GRAVITY * deltaTime * deltaTime;
    player->velocity_y = player->velocity_y + GRAVITY * deltaTime;
}
