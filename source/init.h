#include "common.h"

void initSDL();
SDL_Texture *loadTexture(char* path);
void initClip(SDL_Rect* tempClip, int numOfSprites, int spriteWidth, int spriteHeight);
void initTextures();
void initFont();
void initButtons();
