#include "common.h"
#include "init.h"

extern Game game;
extern Player player;

void initPlayer();
void moveDuck(double deltaTime, bool moveable);
void moveCamera(SDL_Rect* camera);
void renderPlayerSprite(SDL_Rect* camera);
void moveX(double deltaTime);
void gravity(double deltaTime);