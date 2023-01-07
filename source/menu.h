#include "common.h"
#include "timer.h"

void renderMainMenu(Menu* menu, Player player, PlatformTexture* pTextures);
void checkNearMenuPlatform(Player* player, Platform* platform);
void checkMenuCollision(Player* player, Platform* platform);
void checkSDLPollEventMenu(SDL_Event event, Menu* menu, Player* player);
