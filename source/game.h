#include "common.h"

extern Game game;

void updateScore(Player* player);
void generatePlatforms(int score);
void renderGame(Player* player);
void checkSDLPollEventGame(SDL_Event event, Player* player);
