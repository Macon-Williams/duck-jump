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
    initButtons(&menu, menu.titleText.font);

    float accumulated_seconds = 0.0f;
    game.gameState = MENU;

    while(1) {
        tick(&gameTimer);       // Start the first game tick
        tick(&physicsTimer);    // Start the first physics tick
        
        while(game.gameState == MENU) {
            tick(&gameTimer);
            accumulated_seconds += gameTimer.deltaTime;

            if (accumulated_seconds >= CYCLE_TIME - FLT_EPSILON) {
                accumulated_seconds = 0;
                checkSDLPollEventMenu(event, &menu, &player);
                tick(&physicsTimer);
                updateDuck(&player, &physicsTimer, &menu);
                renderMainMenu(&menu, player);
                renderPlayerSprite(&player);
                SDL_RenderPresent(game.renderer);
                //SDL_Delay(5);
            // } else {
            //     SDL_Delay((CYCLE_TIME - FLT_EPSILON - accumulated_seconds) * 1000);
            }
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
