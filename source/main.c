#include "common.h"
#include "init.h"
#include "player.h"
#include "menu.h"
#include "game.h"

Game game;
//const float CYCLE_TIME = 1.0f / FRAME_RATE;

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

    initSDL();
    initFont(&menu.titleText);
    initTextures(&player, &menu, &pTextures);
    initGameObjects(&platforms);
    initMenuButtons(&menu, menu.titleText.font);

    float accumulated_seconds = 0.0f;
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
            renderPlayerSprite(&player, &camera);                                    // Render the duck sprite
            SDL_RenderPresent(game.renderer);                               // Present the updated render to the screen
        }

        generatePlatforms(0, &platforms, MAX);

        while(game.gameState == RUNNING) {
            checkSDLPollEventGame(event, &player);
            tick(&physicsTimer);
            moveDuck(&player, &physicsTimer, true);
            checkNearPlatforms(&player, &platforms);
            camera.y = (player.loc_y + player.size_y / 2) - SCREEN_HEIGHT / 2;
            renderGame(&platforms, &pTextures, &camera);
            renderPlayerSprite(&player, &camera);
            SDL_RenderPresent(game.renderer);
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
