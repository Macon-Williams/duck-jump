#include "common.h"
#include "init.h"
#include "player.h"
#include "menu.h"
#include "game.h"

Game game;

void quit() {
    IMG_Quit();
    SDL_Quit();
    exit(EXIT_SUCCESS);
}

int main(void) {
    Player player;
    Menu menu;
    Timer physicsTimer, gameTimer;
    SDL_Event event;
    Platform platforms[MAX];
    PlatformTexture pTextures;
    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    int offset = PLATFORM_OFFSET;

    initSDL();
    initFont(&menu.titleText);
    initTextures(&player, &menu, &pTextures);
    initGameObjects(&platforms);
    initMenuButtons(&menu, menu.titleText.font);

    game.gameState = MENU;

    while(1) {
        tick(&physicsTimer);    // Start the first physics tick
        
        while(game.gameState == MENU) {
            checkSDLPollEventMenu(event, &menu, &player);                   // Check for events
            tick(&physicsTimer);                                            // Tick the physics timer
            moveDuck(&player, &physicsTimer, false);                        // Update the duck position on the screen & check for collisions
            checkNearMenuPlatform(&player, &menu.menuPlatform);
            checkMenuCollision(&player, &menu.menuPlatform);
            renderMainMenu(&menu, player, &pTextures);                      // Render the main menu buttons & text
            renderPlayerSprite(&player, &camera);                           // Render the duck sprite
            SDL_RenderPresent(game.renderer);                               // Present the updated render to the screen
        }

        generatePlatforms(&camera, 0, &offset, &platforms, MAX);
        player.lost = false;

        while(game.gameState == RUNNING) {
            checkSDLPollEventGame(event, &player);
            tick(&physicsTimer);
            moveDuck(&player, &physicsTimer, true);
            checkNearPlatforms(&player, &platforms);
            moveCamera(&camera, &player);
            generatePlatforms(&camera, player.score, &offset, &platforms, MAX);
            renderGame(&platforms, &pTextures, &camera);
            renderPlayerSprite(&player, &camera);
            SDL_RenderPresent(game.renderer);
            if (player.lost) game.gameState = CLOSE;
        }

        while(game.gameState == SCORE) {
        
        }

        if (game.gameState == CLOSE) {
            quit();
        }
    }

    // Will never see the light of day, but this stops compiler errors :)
    return 0;
}
