#include "common.h"

void initSDL();
SDL_Texture *loadTexture(char* path);
void initClip(SDL_Rect* tempClip, int numOfSprites, int spriteWidth, int spriteHeight);
void initTextures(Player* player, Menu* menu, PlatformTexture* pTextures);
SDL_Texture *generateText(char* text, SDL_Color textColor, TTF_Font* menuFont);
void initGameObjects(Platform *platforms);
void initFont(Text* text);
void initMenuButtons(Menu* menu, TTF_Font* font);
