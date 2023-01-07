#include "common.h"

void moveDuck(Player* player, Timer* timer, bool moveable);
void renderPlayerSprite(Player* player);
void updateXVelocity(Player* player, double deltaTime);
void gravity(Player* player, double deltaTime);