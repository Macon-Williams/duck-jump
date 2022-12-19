#include "common.h"
#include "init.h"
#include "menu.h"

Game game;
Player player;
MenuButtons menu;
Text menuText;

enum gameState{MENU, RUNNING, SCORE, CLOSE};
enum gameState currentGameState = MENU;

void tick() {
    game.currentTicks = SDL_GetPerformanceCounter();
    Uint64 delta = game.currentTicks - game.previousTicks;
    game.previousTicks = game.currentTicks;
    game.ticksPerSecond = SDL_GetPerformanceFrequency();
    game.elapsedSeconds = (double) delta / (double) game.ticksPerSecond;
}

void quit() {
    IMG_Quit();
    SDL_Quit();
    exit(EXIT_SUCCESS);
}

int main(void) {
    initSDL();
    initTextures();
    initFont();
    initButtons();  

    const int UPDATE_FREQUENCY = FRAME_RATE;
    const float CYCLE_TIME = 1.0f / UPDATE_FREQUENCY;
    float accumulated_seconds = 0.0f;

    SDL_Event event;

    while(1) {
        tick();
        player.loc_x = 200;
        player.loc_y = 250;

        while(currentGameState == MENU) {
            tick();
            // accumulated_seconds += game.elapsedSeconds;
            // if (accumulated_seconds >= CYCLE_TIME) {
                accumulated_seconds -= CYCLE_TIME;
                renderMainMenu();
                checkSDLPollEventMenu(event);
                SDL_RenderPresent(game.renderer);
            // }
            updateDuck();


        }

        while(currentGameState == RUNNING) {

        }

        while(currentGameState == SCORE) {
        
        }

        if (currentGameState == CLOSE) {
            quit();
        }
    }

    // Will never see the light of day, but this stops compiler errors :)
    return 0;
}
