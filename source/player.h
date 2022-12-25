#include "common.h"

void updateDuck(Player* player, Timer* timer, Menu* menu);
void renderPlayerSprite(Player* player);
void checkCollision(Player* player, Menu* menu);
void updateXVelocity(Player* player, double deltaTime);
void gravity(Player* player, double deltaTime);