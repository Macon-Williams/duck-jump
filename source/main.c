#include "common.h"
#include "init.h"
#include "player.h"
#include "menu.h"

Game game;

const float CYCLE_TIME = 1.0f / FRAME_RATE;

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

    initSDL();
    initFont(&menu.titleText);
    initTextures(&player, &menu);
    initMenuButtons(&menu, menu.titleText.font);

    float accumulated_seconds = 0.0f;
    game.gameState = MENU;

    while(1) {
        tick(&physicsTimer);    // Start the first physics tick
        
        while(game.gameState == MENU) {
            checkSDLPollEventMenu(event, &menu, &player);       // Check for events
            tick(&physicsTimer);                                // Tick the physics timer
            updateDuck(&player, &physicsTimer, &menu, true);   // Update the duck position on the screen
            renderMainMenu(&menu, player);                      // Render the main menu buttons & text
            renderPlayerSprite(&player);                        // Render the duck sprite
            SDL_RenderPresent(game.renderer);                   // Present the updated render to the screen
        }

        while(game.gameState == RUNNING) {
            
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
