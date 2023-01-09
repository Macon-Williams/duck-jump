#include "player.h"

extern Game game;

void moveDuck(Player* player, Timer* timer, bool moveable) {
    gravity(player, (double) timer->deltaTime);
    if (moveable)
        updateXVelocity(player, (double) timer->deltaTime);
}

void moveCamera(SDL_Rect* camera, Player* player) {
    if (player->velocity_y < 0 && player->loc_y + player->size_y <= camera->y + (SCREEN_HEIGHT / 2) + (player->size_y / 2)) {
        camera->y = (player->loc_y + player->size_y / 2) - SCREEN_HEIGHT / 2;
        player->score = abs(camera->y);
    }
}

void renderPlayerSprite(Player* player, SDL_Rect* camera) {
    SDL_Rect renderQuad = {(int) player->loc_x, (int) player->loc_y - camera->y, player->size_x, player->size_y};
    if (player->flipped) {
        SDL_RenderCopyEx(game.renderer, player->duckSprite, &player->duckClip[player->frame], &renderQuad, 0, NULL, SDL_FLIP_HORIZONTAL);
    } else {
        SDL_RenderCopyEx(game.renderer, player->duckSprite, &player->duckClip[player->frame], &renderQuad, 0, NULL, 0);
    }

    if (player->loc_y > camera->y + SCREEN_HEIGHT) {
        player->lost = true;
    }
}

void updateXVelocity(Player* player, double deltaTime) {
    double acceleration;
    if (player->move_x) {
        acceleration = PLAYER_MOVEMENT_ACCELERAITON * 5 * player->move_x;
    } else {
        acceleration = -5 * player->velocity_x;
        if (fabs(player->velocity_x) < 1) player->velocity_x = 0;
    }

    if (player->loc_x + player->size_x >= SCREEN_WIDTH && player->move_x > 0) {
        player->velocity_x = 0;
    } else if (player->loc_x <= 0 && player->move_x < 0) {
        player->velocity_x = 0;
    } else {
        player->velocity_x += acceleration * deltaTime;
    }

    if (fabs(player->velocity_x) > MAX_PLAYER_SPEED) player->velocity_x = MAX_PLAYER_SPEED * player->move_x;
    player->loc_x += player->velocity_x * deltaTime;
}

void gravity(Player* player, double deltaTime) {
    player->velocity_y += (GRAVITY * deltaTime);
    player->loc_y += (player->velocity_y * deltaTime);
    if (player->velocity_y > 0) {
        player->frame = 1;      
    } else {
        player->frame = 0;
    }
}
