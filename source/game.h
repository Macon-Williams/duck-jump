#include "common.h"
#include "main.c"

extern Game game;

void updateScore(Player* player);
void generatePlatforms(int score);
void renderGame(Player* player);
void checkSDLPollEventMenu(SDL_Event event, Player* player);
