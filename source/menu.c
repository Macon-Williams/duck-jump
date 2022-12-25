#include "menu.h"

extern Game game;

void renderMainMenu(Menu* menu, Player player) {
    // Handles the main menu rendering
    SDL_SetRenderDrawColor(game.renderer, 0xC7, 0xC7, 0xC7, 0xFF);
    SDL_RenderClear(game.renderer);

    SDL_Rect textRenderQuad = {50, 50, 384, 64};
    SDL_RenderCopy(game.renderer, menu->titleText.text, NULL, &textRenderQuad);

    SDL_Rect playButtonRenderQuad = {menu->playButton.loc_x, menu->playButton.loc_y, menu->playButton.size_x, menu->playButton.size_y};
    SDL_RenderCopy(game.renderer, menu->playButton.buttonImage, &menu->playButton.buttonClip[menu->playButton.state], &playButtonRenderQuad);
    if (menu->playButton.state == MOUSE_DOWN) {
        menu->playButton.text_loc_x = menu->playButton.loc_x + (menu->playButton.size_x - menu->playButton.text_size_x) / 2 - 4;
        menu->playButton.text_loc_y = menu->playButton.loc_y + (menu->playButton.size_y - menu->playButton.text_size_y) / 2 + 4;
    } else {
        menu->playButton.text_loc_x = menu->playButton.loc_x + (menu->playButton.size_x - menu->playButton.text_size_x) / 2;
        menu->playButton.text_loc_y = menu->playButton.loc_y + (menu->playButton.size_y - menu->playButton.text_size_y) / 2;
    }
    SDL_Rect playTextRenderQuad = {menu->playButton.text_loc_x, menu->playButton.text_loc_y, menu->playButton.text_size_x, menu->playButton.text_size_y};
    SDL_RenderCopy(game.renderer, menu->playButton.buttonText, NULL, &playTextRenderQuad);

    SDL_Rect scoreButtonRenderQuad = {menu->scoreButton.loc_x, menu->scoreButton.loc_y, menu->scoreButton.size_x, menu->scoreButton.size_y};
    SDL_RenderCopy(game.renderer, menu->scoreButton.buttonImage, &menu->scoreButton.buttonClip[menu->scoreButton.state], &scoreButtonRenderQuad); // I cause a segmentation fault
    if (menu->scoreButton.state == MOUSE_DOWN) {
        menu->scoreButton.text_loc_x = menu->scoreButton.loc_x + (menu->scoreButton.size_x - menu->scoreButton.text_size_x) / 2 - 4;
        menu->scoreButton.text_loc_y = menu->scoreButton.loc_y + (menu->scoreButton.size_y - menu->scoreButton.text_size_y) / 2 + 4;
    } else {
        menu->scoreButton.text_loc_x = menu->scoreButton.loc_x + (menu->scoreButton.size_x - menu->scoreButton.text_size_x) / 2;
        menu->scoreButton.text_loc_y = menu->scoreButton.loc_y + (menu->scoreButton.size_y - menu->scoreButton.text_size_y) / 2;
    }
    SDL_Rect scoreTextRenderQuad = {menu->scoreButton.text_loc_x, menu->scoreButton.text_loc_y, menu->scoreButton.text_size_x, menu->scoreButton.text_size_y};
    SDL_RenderCopy(game.renderer, menu->scoreButton.buttonText, NULL, &scoreTextRenderQuad);

    SDL_Rect optionButtonRenderQuad = {menu->optionButton.loc_x, menu->optionButton.loc_y, menu->optionButton.size_x, menu->optionButton.size_y};
    SDL_RenderCopy(game.renderer, menu->optionButton.buttonImage, &menu->optionButton.buttonClip[menu->optionButton.state], &optionButtonRenderQuad);
    if (menu->optionButton.state == MOUSE_DOWN) {
        menu->optionButton.text_loc_x = menu->optionButton.loc_x + (menu->optionButton.size_x - menu->optionButton.text_size_x) / 2 - 4;
        menu->optionButton.text_loc_y = menu->optionButton.loc_y + (menu->optionButton.size_y - menu->optionButton.text_size_y) / 2 + 4;
    } else {
        menu->optionButton.text_loc_x = menu->optionButton.loc_x + (menu->optionButton.size_x - menu->optionButton.text_size_x) / 2;
        menu->optionButton.text_loc_y = menu->optionButton.loc_y + (menu->optionButton.size_y - menu->optionButton.text_size_y) / 2;
    }
    SDL_Rect optionTextRenderQuad = {menu->optionButton.text_loc_x, menu->optionButton.text_loc_y, menu->optionButton.text_size_x, menu->optionButton.text_size_y};
    SDL_RenderCopy(game.renderer, menu->optionButton.buttonText, NULL, &optionTextRenderQuad);

    SDL_Rect exitButtonRenderQuad = {menu->exitButton.loc_x, menu->exitButton.loc_y, menu->exitButton.size_x, menu->exitButton.size_y};
    SDL_RenderCopy(game.renderer, menu->exitButton.buttonImage, &menu->exitButton.buttonClip[menu->exitButton.state], &exitButtonRenderQuad);
    if (menu->exitButton.state == MOUSE_DOWN) {
        menu->exitButton.text_loc_x = menu->exitButton.loc_x + (menu->exitButton.size_x - menu->exitButton.text_size_x) / 2 - 4;
        menu->exitButton.text_loc_y = menu->exitButton.loc_y + (menu->exitButton.size_y - menu->exitButton.text_size_y) / 2 + 4;
    } else {
        menu->exitButton.text_loc_x = menu->exitButton.loc_x + (menu->exitButton.size_x - menu->exitButton.text_size_x) / 2;
        menu->exitButton.text_loc_y = menu->exitButton.loc_y + (menu->exitButton.size_y - menu->exitButton.text_size_y) / 2;
    }
    SDL_Rect exitTextRenderQuad = {menu->exitButton.text_loc_x, menu->exitButton.text_loc_y, menu->exitButton.text_size_x, menu->exitButton.text_size_y};
    SDL_RenderCopy(game.renderer, menu->exitButton.buttonText, NULL, &exitTextRenderQuad);

    SDL_Rect menuPlatformRenderQuad = {(player.loc_x - player.size_x / 2), menu->menuPlatform.loc_y, menu->menuPlatform.size_x, menu->menuPlatform.size_y};
    SDL_RenderCopy(game.renderer, menu->menuPlatform.sprite, NULL, &menuPlatformRenderQuad);
}

void checkSDLPollEventMenu(SDL_Event event, Menu* menu, Player* player) {
    if (SDL_PollEvent(&event) != 0) {
        if (event.type == SDL_QUIT) {
            game.gameState = CLOSE;
            
        }
        if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) {
            int x, y; // Mouse position
            SDL_GetMouseState(&x, &y); // Set mouse position

            if (x < (menu->playButton.loc_x + menu->playButton.size_x) && x > menu->playButton.loc_x && y < (menu->playButton.loc_y + menu->playButton.size_y) && y > menu->playButton.loc_y) {
                if (event.type == SDL_MOUSEMOTION) {
                    menu->playButton.state = MOUSE_OVER;
                } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                    menu->playButton.state = MOUSE_DOWN;
                } else if (event.type == SDL_MOUSEBUTTONUP) {
                    menu->playButton.state = MOUSE_OVER;
                }
            } else {
                menu->playButton.state = MOUSE_OUT;
            }

            if (x < (menu->scoreButton.loc_x + menu->scoreButton.size_x) && x > menu->scoreButton.loc_x && y < (menu->scoreButton.loc_y + menu->scoreButton.size_y) && y > menu->scoreButton.loc_y) {
                if (event.type == SDL_MOUSEMOTION) {
                    menu->scoreButton.state = MOUSE_OVER;
                } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                    menu->scoreButton.state = MOUSE_DOWN;
                } else if (event.type == SDL_MOUSEBUTTONUP) {
                    menu->scoreButton.state = MOUSE_OVER;
                }
            } else {
                menu->scoreButton.state = MOUSE_OUT;
            }

            if (x < (menu->optionButton.loc_x + menu->optionButton.size_x) && x > menu->optionButton.loc_x && y < (menu->optionButton.loc_y + menu->optionButton.size_y) && y > menu->optionButton.loc_y) {
                if (event.type == SDL_MOUSEMOTION) {
                    menu->optionButton.state = MOUSE_OVER;
                } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                    menu->optionButton.state = MOUSE_DOWN;
                } else if (event.type == SDL_MOUSEBUTTONUP) {
                    menu->optionButton.state = MOUSE_OVER;
                }
            } else {
                menu->optionButton.state = MOUSE_OUT;
            }

            if (x < (menu->exitButton.loc_x + menu->exitButton.size_x) && x > menu->exitButton.loc_x && y < (menu->exitButton.loc_y + menu->exitButton.size_y) && y > menu->exitButton.loc_y) {
                if (event.type == SDL_MOUSEMOTION) {
                    menu->exitButton.state = MOUSE_OVER;
                } else if (event.type == SDL_MOUSEBUTTONDOWN) {
                    menu->exitButton.state = MOUSE_DOWN;
                } else if (event.type == SDL_MOUSEBUTTONUP) {
                    menu->exitButton.state = MOUSE_OVER;
                    game.gameState = CLOSE;
                }
            } else {
                menu->exitButton.state = MOUSE_OUT;
            }
        }
        if (event.type == SDL_KEYDOWN) {
            switch(event.key.keysym.sym) {
                case SDLK_RIGHT:
                    player->move_x = 1;
                    break;
                case SDLK_LEFT:
                    player->move_x = -1;
                    break;
                default:
                    break;
            }
        }
        if (event.type == SDL_KEYUP) {
            switch(event.key.keysym.sym) {
                case SDLK_RIGHT:
                // Fall through
                case SDLK_LEFT:
                    player->move_x = 0;
                    break;
                default:
                    break;
            }
        }
    }
}