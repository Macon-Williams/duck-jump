#include "game.h"

// TODO: Implement
void updateScore(Player *player) {

}

void checkNearPlatforms(Player* player, Platform* platforms) {
    for (int i = 0; i < MAX; i++) {
        if (player->loc_x + player->size_x > platforms[i].loc_x && player->loc_x < (platforms[i].loc_x + platforms[i].size_x)) {
            if (player->loc_y + player->size_y >= platforms[i].loc_y - 50 && player->velocity_y > 0) { // 50 pixels away from the platform, switch to frame 2, player is near
                player->frame = 1;
                if (collision(player, &platforms[i])) {
                    player->velocity_y = -JUMP_HEIGHT; // Jump
                }
            } else {
                player->frame = 0;
            }
        } else {
        player->frame = 0;
        }
    }
}

bool collision(Player* player, Platform* platform) {
    if (player->loc_x + player->size_x > platform->loc_x && player->loc_x < platform->loc_x + platform->size_x) {
        if ((player->loc_y + player->size_y >= platform->loc_y) && (player->loc_y + player->size_y < platform->loc_y + platform->size_y) && player->velocity_y > 0){
            return true;
        }
    }
    return false;
}

void generatePlatforms(int offset, Platform* platform, int numOfPlatforms) {
    int default_space = 48;
    double y_spacing = (double) offset * (double) 0.001f;
    if (y_spacing > 300.0) {
        y_spacing = 300.0;
    }

    for (int i = 0; i < numOfPlatforms; i++) {
        if (platform[i].off_screen) {
            platform[i].loc_x = (rand() % (SCREEN_WIDTH - 128));
            platform[i].loc_y = SCREEN_HEIGHT - (y_spacing + default_space);
            platform[i].size_x = 128;
            platform[i].size_y = 24;
            default_space +=48;
        }

    }
}

// TODO: Implement
void renderGame(Player* player, Platform* platform, PlatformTexture* pTextures) {
    SDL_SetRenderDrawColor(game.renderer, 0xC7, 0xC7, 0xC7, 0xFF);
    SDL_RenderClear(game.renderer);

    for (int i = 0; i < MAX; i++) {
        SDL_Rect platformQuad = {platform[i].loc_x, platform[i].loc_y, platform[i].size_x, platform[i].size_y};
        SDL_RenderCopy(game.renderer, pTextures->defaultTexture, NULL, &platformQuad);
    }
}

void load() {
    SDL_SetRenderDrawColor(game.renderer, 0xa3, 0x9a, 0x90, 0xFF);
    SDL_RenderClear(game.renderer);

    SDL_Rect textRenderQuad = {SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 30, 200, 60};
    SDL_RenderCopy(game.renderer, game.loadingText, NULL, &textRenderQuad);
}

// TODO: Implement
void checkSDLPollEventGame(SDL_Event event, Player* player) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            game.gameState = CLOSE;
        }

        const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
        if (keyboardState[SDL_SCANCODE_RIGHT] | keyboardState[SDL_SCANCODE_D]) {
            player->move_x = 1;
        }
        if (keyboardState[SDL_SCANCODE_LEFT] | keyboardState[SDL_SCANCODE_A]) {
            player->move_x = -1;
        }
        if (!keyboardState[SDL_SCANCODE_LEFT] && !keyboardState[SDL_SCANCODE_D] && !keyboardState[SDL_SCANCODE_RIGHT] && !keyboardState[SDL_SCANCODE_A]) {
            player->move_x = 0;
        }
    }
}
