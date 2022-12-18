#include "common.h"
#include "physics.h"

void renderMainMenu();
void updateDuck();
void renderSprite(int x, int y, SDL_Texture* sprite, SDL_Rect* clip);
void checkCollision();
void checkSDLPollEventMenu(SDL_Event event);
