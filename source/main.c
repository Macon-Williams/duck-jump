#include "common.h"
#include "init.h"
#include "menu.h"

Game game;
Player player;
MenuButtons menu;
Text menuText;

enum gameState{MENU, RUNNING, SCORE, CLOSE};
enum gameState currentGameState = MENU;

Uint64 previousTicks, currentTicks, ticksPerSecond;
float elapsedSeconds;

void tick() {
    currentTicks = SDL_GetPerformanceCounter();
    Uint64 delta = currentTicks - previousTicks;
    // printf("delta: %llu\n", delta);
    previousTicks = currentTicks;
    ticksPerSecond = SDL_GetPerformanceFrequency();
    elapsedSeconds = delta / (float) ticksPerSecond;
    // printf("Elapsed seconds: %f\n", elapsedSeconds);
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
    printf("Cycle time: %f\n", CYCLE_TIME);
    float accumulated_seconds = 0.0f;

    SDL_Event event;
    
    while(1) {
        tick();
        player.loc_x = 200;
        player.loc_y = 250;

        while(currentGameState == MENU) {
            tick();
            accumulated_seconds += elapsedSeconds;
            printf("Accumulated_seconds: %f\n", accumulated_seconds);
            if (accumulated_seconds >= CYCLE_TIME) {
                accumulated_seconds -= CYCLE_TIME;
                checkSDLPollEventMenu(event);
                renderMainMenu();
                updateDuck();
                SDL_RenderPresent(game.renderer);
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
