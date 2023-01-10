#include "common.h"

extern Game game;
extern Player player;

void initPlatforms(Platform* platform, int numOfPlatforms);
void updateScore();
void checkNearPlatforms(Platform* platforms);
bool collision(Platform* platform);
void generatePlatforms(SDL_Rect* camera, int score, int* offset, Platform* platforms, int numOfPlatforms);
void renderGame(Platform* platform, PlatformTexture* pTextures, SDL_Rect* camera);
void load();
void checkSDLPollEventGame(SDL_Event event);
