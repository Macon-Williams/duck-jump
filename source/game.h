#include "common.h"

extern Game game;

void updateScore(Player* player);
void checkNearPlatforms(Player* player, Platform* platforms);
bool collision(Player* player, Platform* platform);
void generatePlatforms(int score, Platform* platforms);
void renderGame(Player* player, Platform* platform, PlatformTexture* pTextures);
void load();
void checkSDLPollEventGame(SDL_Event event, Player* player);
