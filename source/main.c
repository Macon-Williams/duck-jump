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

void renderSprite(int x, int y, SDL_Texture* sprite, SDL_Rect* clip) {
    SDL_Rect renderQuad = {x, y, 64, 64};
    SDL_RenderCopy(game.renderer, sprite, clip, &renderQuad);
}

int main(void) {
    initSDL();
    initTextures();
    initFont();
    initButtons();

    SDL_Event event;
    int frame = 0;
    
    while(1) {
        while(currentGameState == MENU) {
            checkSDLPollEventMenu(event);

            renderMainMenu();
            renderSprite((SCREEN_WIDTH - 64)/3, (SCREEN_HEIGHT - 64) /2, player.duckSprite, &player.duckClip[frame]);

            SDL_RenderPresent(game.renderer);
            SDL_Delay(20);

           ++frame;
           if (frame >= 2) {
               frame = 0;
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
