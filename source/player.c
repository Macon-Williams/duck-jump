#include "player.h"

extern Game game;

void updateDuck(Player* player, Timer* timer, Menu* menu, bool moveable) {
    checkNearPlatform(player, menu->menuPlatform.loc_x, menu->menuPlatform.size_x, menu->menuPlatform.loc_y);
    checkCollision(player, menu);
    gravity(player, (double) timer->deltaTime);
    if (moveable)
        updateXVelocity(player, (double) timer->deltaTime);
}

void renderPlayerSprite(Player* player) {
    SDL_Rect renderQuad = {(int) player->loc_x, (int) player->loc_y, player->size_x, player->size_y};
    SDL_RenderCopy(game.renderer, player->duckSprite, &player->duckClip[player->frame], &renderQuad);
}

void checkNearPlatform(Player* player, int loc_x, int size_x, int loc_y) {
    if (player->loc_x > loc_x && player->loc_x < (loc_x + size_x)) {
        if (player->loc_y + player->size_y >= loc_y - 40) {
            player->frame = 1;
        } else {
            player->frame = 0;
        }
    } else {
        player->frame = 0;
    }
}

void checkCollision(Player* player, Menu* menu) {
    if (player->loc_y + player->size_y >= menu->menuPlatform.loc_y)
        player->velocity_y = -600; // Jump
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