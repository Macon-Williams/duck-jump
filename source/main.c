#include "common.h"
#include "init.h"
#include "menu.h"

Game game;
Player player;
MenuButtons menu;
Text menuText;

enum gameState{MENU, RUNNING, SCORE, CLOSE};
enum gameState currentGameState = MENU;

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

    SDL_Event event;
    
    while(1) {
        player.loc_x = 200;
        player.loc_y = 250;

        while(currentGameState == MENU) {
            checkSDLPollEventMenu(event);
            renderMainMenu();
            updateDuck();
            SDL_RenderPresent(game.renderer);
            SDL_Delay(20);

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
