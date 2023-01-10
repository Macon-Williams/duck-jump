#include "common.h"
#include "init.h"
#include "player.h"
#include "menu.h"
#include "game.h"

Game game;
Player player;


void quit() {
    IMG_Quit();
    SDL_Quit();
    exit(EXIT_SUCCESS);
}

int main(void) {
    Menu menu;
    SDL_Event event;
    Platform platforms[MAX];
    PlatformTexture pTextures;
    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

    initSDL();
    initFont(&menu.titleText);
    initPlayer();
    initTextures(&menu, &pTextures);
    initMenuButtons(&menu, menu.titleText.font);

    game.gameState = MENU;
    int offset = PLATFORM_OFFSET;

    while(1) {
        tick(&game.timer);    // Start the first physics tick
        
        while(game.gameState == MENU) {
            checkSDLPollEventMenu(event, &menu, &player);                    // Check for events
            tick(&game.timer);                                               // Tick the physics timer
            moveDuck(game.timer.deltaTime, false);                           // Update the duck position on the screen & check for collisions
            checkNearMenuPlatform(&player, &menu.menuPlatform);
            checkMenuCollision(&player, &menu.menuPlatform);
            renderMainMenu(&menu, player, &pTextures);                       // Render the main menu buttons & text
            renderPlayerSprite(&camera);                                     // Render the duck sprite
            SDL_RenderPresent(game.renderer);                                // Present the updated render to the screen
        }
        initPlatforms(&platforms, MAX);
        generatePlatforms(&camera, 0, &offset, &platforms, MAX);
        player.lost = false;

        while(game.gameState == RUNNING) {
            checkSDLPollEventGame(event);
            tick(&game.timer);
            moveDuck(game.timer.deltaTime, true);
            checkNearPlatforms(&platforms);
            moveCamera(&camera);
            generatePlatforms(&camera, player.score, &offset, &platforms, MAX);
            renderGame(&platforms, &pTextures, &camera);
            renderPlayerSprite(&camera);
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
