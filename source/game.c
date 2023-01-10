#include "game.h"

void initPlatforms(Platform* platform, int numOfPlatforms) {
    for (int i = 0; i < numOfPlatforms; i++) {
        platform[i].size_x = *(int *) malloc(sizeof(int));
        platform[i].size_y = *(int *) malloc(sizeof(int));
        platform[i].loc_x = *(int *) malloc(sizeof(int));
        platform[i].loc_y = *(int *) malloc(sizeof(int));
        platform[i].off_screen = true;
    }
}

// TODO: Implement
void updateScore() {

}

void checkNearPlatforms(Platform* platforms) {
    for (int i = 0; i < MAX; i++) {
        if (collision(&platforms[i]))
            player.velocity_y = -JUMP_HEIGHT; // Jump
    }
}

bool collision(Platform* platform) {
    if (player.loc_x + player.size_x > platform->loc_x && player.loc_x < platform->loc_x + platform->size_x) {
        if ((player.loc_y + player.size_y >= platform->loc_y) && (player.loc_y + player.size_y < platform->loc_y + platform->size_y) && player.velocity_y > 0){
            return true;
        }
    }
    return false;
}

void generatePlatforms(SDL_Rect* camera, int score, int* offset, Platform* platform, int numOfPlatforms) {
    float spacing;
    for (int i = 0; i < numOfPlatforms; i++) {
        if (platform[i].loc_y > camera->y + SCREEN_HEIGHT + 20) {
            platform[i].off_screen = true;
        }
    }

    for (int i = 0; i < numOfPlatforms; i++) {
        spacing = (float) score / 20 + 1;
        if (spacing > 160.0) {
            spacing = 160.0;
        }

        if (platform[i].off_screen) {
            platform[i].loc_x = (rand() % (SCREEN_WIDTH - 128));
            platform[i].loc_y = SCREEN_HEIGHT - *offset;
            platform[i].size_x = 128;
            platform[i].size_y = 24;
            platform[i].off_screen = false;        
            *offset += PLATFORM_OFFSET + (rand() % (int) spacing);

        }
    }
}

// TODO: Implement
void renderGame(Platform* platform, PlatformTexture* pTextures, SDL_Rect* camera) {
    SDL_SetRenderDrawColor(game.renderer, 0xC7, 0xC7, 0xC7, 0xFF);
    SDL_RenderClear(game.renderer);

    for (int i = 0; i < MAX; i++) {
        SDL_Rect platformQuad = {platform[i].loc_x, platform[i].loc_y - camera->y, platform[i].size_x, platform[i].size_y};
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
void checkSDLPollEventGame(SDL_Event event) {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            game.gameState = CLOSE;
        }

        const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
        if (keyboardState[SDL_SCANCODE_RIGHT] || keyboardState[SDL_SCANCODE_D]) {
            player.move_x = 1;
            player.flipped = false;
        }
        if (keyboardState[SDL_SCANCODE_LEFT] || keyboardState[SDL_SCANCODE_A]) {
            player.move_x = -1;
            player.flipped = true;
        }
        if (!keyboardState[SDL_SCANCODE_LEFT] && !keyboardState[SDL_SCANCODE_D] && !keyboardState[SDL_SCANCODE_RIGHT] && !keyboardState[SDL_SCANCODE_A]) {
            player.move_x = 0;
        }
    }
}
