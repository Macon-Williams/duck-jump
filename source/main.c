#include "common.h"
#include "init.h"
#include "menu.h"

Game game;
Player player;
MenuButtons menu;
Text menuText;

enum gameState{MENU, RUNNING, SCORE, CLOSE};
enum gameState currentGameState = MENU;

Timer physicsTimer;

void gameTick() {
    game.timer.currentTicks = SDL_GetPerformanceCounter();
    Uint64 delta = game.timer.currentTicks - game.timer.previousTicks;
    game.timer.previousTicks = game.timer.currentTicks;
    game.timer.ticksPerSecond = SDL_GetPerformanceFrequency();
    game.timer.deltaTime = (double) delta / (double) game.timer.ticksPerSecond;
}

void physicsTick() {
    physicsTimer.currentTicks = SDL_GetPerformanceCounter();
    Uint64 delta = physicsTimer.currentTicks - physicsTimer.previousTicks;
    physicsTimer.previousTicks = physicsTimer.currentTicks;
    physicsTimer.ticksPerSecond = SDL_GetPerformanceFrequency();
    physicsTimer.deltaTime = (double) delta / (double) physicsTimer.ticksPerSecond;
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
        gameTick();
        physicsTick();
        player.loc_x = 200;
        player.loc_y = 250;
        
        while(currentGameState == MENU) {
            gameTick();
            accumulated_seconds += game.timer.deltaTime;

            if (accumulated_seconds > CYCLE_TIME - FLT_EPSILON) {
                accumulated_seconds += game.timer.deltaTime;
                physicsTick();
                renderMainMenu();
                updateDuck();
                checkSDLPollEventMenu(event);
                SDL_RenderPresent(game.renderer);
            } else {
                SDL_Delay(1);
            }
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
