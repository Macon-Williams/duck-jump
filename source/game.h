#include "common.h"

extern Game game;

void updateScore(Player* player);
void checkNearPlatforms(Player* player, Platform* platforms);
bool collision(Player* player, Platform* platform);
void generatePlatforms(SDL_Rect* camera, int score, int* offset, Platform* platforms, int numOfPlatforms);
void renderGame(Platform* platform, PlatformTexture* pTextures, SDL_Rect* camera);
void load();
void checkSDLPollEventGame(SDL_Event event, Player* player);
