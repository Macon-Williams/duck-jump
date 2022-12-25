#include "common.h"

void initSDL();
SDL_Texture *loadTexture(char* path);
void initClip(SDL_Rect* tempClip, int numOfSprites, int spriteWidth, int spriteHeight);
void initTextures(Player* player, Menu* menu);
SDL_Texture *generateText(char* text, SDL_Color textColor, TTF_Font* menuFont);
void initFont(Text* text);
void initButtons(Menu* menu, TTF_Font* font);
