#include "common.h"

void updateDuck(Player* player, Timer* timer, Menu* menu, bool moveable);
void renderPlayerSprite(Player* player);
void checkNearPlatform(Player* player, int loc_x, int size_x, int loc_y);
void checkCollision(Player* player, Menu* menu);
void updateXVelocity(Player* player, double deltaTime);
void gravity(Player* player, double deltaTime);