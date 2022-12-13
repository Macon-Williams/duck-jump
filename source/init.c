#include "init.h"

// Access global variables from main.c
extern Game game;
extern Player player;
extern MenuButtons menu;
extern Text menuText;

void initSDL() {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not be initialized! SDL Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Create a game window
    game.window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
                                    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!game.window) {
        printf("Failed to create window! SDL Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Create a game renderer
    game.renderer = SDL_CreateRenderer(game.window, -1, SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);
    if (!game.renderer) {
        printf("Failed to create renderer! SDL Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
}

SDL_Texture *loadTexture(char* path) {
    SDL_Texture *newTexture = IMG_LoadTexture(game.renderer, path);
    if (!newTexture) {
        printf("Unable to load image %s! IMG_Load error: %s\n", path, IMG_GetError());
        exit(EXIT_FAILURE);
    }
    return newTexture;
}

void initClip(SDL_Rect* tempClip, int numOfSprites, int spriteWidth, int spriteHeight) {
    int x_pos = 0;

    for (int i = 0; i < numOfSprites; i++) {
        tempClip[i].x = x_pos;
        tempClip[i].y = 0;
        tempClip[i].w = spriteWidth;
        tempClip[i].h = spriteHeight;

        x_pos = x_pos + spriteWidth;
    }
}

void initTextures() {
    // Load the texture files
    player.duckSprite = loadTexture(PLAYER_SPRITE_PATH);
    initClip(player.duckClip, 2, 16, 16);

    menu.playButton.buttonImage = loadTexture(PLAY_BUTTON_SPRITE_PATH);
    initClip(menu.playButton.buttonClip, 3, 108, 44);

    menu.scoreButton.buttonImage = loadTexture(BUTTON_SPRITE_PATH);
    initClip(menu.scoreButton.buttonClip, 3, 96, 26);

    menu.optionButton.buttonImage = loadTexture(BUTTON_SPRITE_PATH);
    initClip(menu.optionButton.buttonClip, 3, 96, 26);

    menu.exitButton.buttonImage = loadTexture(BUTTON_SPRITE_PATH);
    initClip(menu.exitButton.buttonClip, 3, 96, 26);
}

SDL_Texture *generateText(char* text, SDL_Color textColor) {
    SDL_Surface* tempMenuTextSurface = TTF_RenderUTF8_Solid(menuText.menuFont, text, textColor);
    if (!tempMenuTextSurface) {
        printf("Unable to render menu text! SDL_ttf Error: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Texture* tempMenuTextTexture = SDL_CreateTextureFromSurface(game.renderer, tempMenuTextSurface);
    SDL_FreeSurface(tempMenuTextSurface);
    return tempMenuTextTexture;
}

void initFont() {
    if (TTF_Init() < 0) {
        printf("Unable to initialize TTF fonts! See error: %s", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    
    menuText.menuFont = TTF_OpenFont("../assets/StayPixelRegular.ttf", 48);
    if (!menuText.menuFont) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Color textColor = {0, 0, 0};

    menuText.titleText = generateText("Duck Jump", textColor);
    menu.playButton.buttonText = generateText("Play", textColor);
    menu.scoreButton.buttonText = generateText("High Scores", textColor);
    menu.optionButton.buttonText = generateText("Options", textColor);
    menu.exitButton.buttonText = generateText("Exit", textColor);
}

void initButtons() {

    menu.playButton.size_x = PLAY_BUTTON_SIZE_X;
    menu.playButton.size_y = PLAY_BUTTON_SIZE_Y;
    menu.playButton.text_size_x = PLAY_BUTTON_SIZE_X - 35;
    menu.playButton.text_size_y = PLAY_BUTTON_SIZE_Y - 20;
    menu.playButton.loc_x = ((SCREEN_WIDTH - PLAY_BUTTON_SIZE_X) * 8) / 9;
    menu.playButton.loc_y = (SCREEN_HEIGHT - PLAY_BUTTON_SIZE_Y) / 2;
    menu.playButton.text_loc_x = menu.playButton.loc_x + (menu.playButton.size_x - menu.playButton.text_size_x) / 2;
    menu.playButton.text_loc_y = menu.playButton.loc_y + (menu.playButton.size_y - menu.playButton.text_size_y) / 2;

    menu.scoreButton.size_x = BUTTON_SIZE_X;
    menu.scoreButton.size_y = BUTTON_SIZE_Y;
    menu.scoreButton.text_size_x = BUTTON_SIZE_X - 20;
    menu.scoreButton.text_size_y = BUTTON_SIZE_Y - 10;
    menu.scoreButton.loc_x = menu.playButton.loc_x + ((menu.playButton.size_x - menu.scoreButton.size_x) / 2);
    menu.scoreButton.loc_y = menu.playButton.loc_y + menu.playButton.size_y + 20;
    menu.scoreButton.text_loc_x = menu.scoreButton.loc_x + (menu.scoreButton.size_x - menu.scoreButton.text_size_x) / 2;
    menu.scoreButton.text_loc_y = menu.scoreButton.loc_y + (menu.scoreButton.size_y - menu.scoreButton.text_size_y) / 2;

    menu.optionButton.size_x = BUTTON_SIZE_X;
    menu.optionButton.size_y = BUTTON_SIZE_Y;
    menu.optionButton.text_size_x = BUTTON_SIZE_X - 40;
    menu.optionButton.text_size_y = BUTTON_SIZE_Y - 10;
    menu.optionButton.loc_x = menu.scoreButton.loc_x;
    menu.optionButton.loc_y = menu.scoreButton.loc_y + menu.scoreButton.size_y + 20;
    menu.optionButton.text_loc_x = menu.optionButton.loc_x + (menu.optionButton.size_x - menu.optionButton.text_size_x) / 2;
    menu.optionButton.text_loc_y = menu.optionButton.loc_y + (menu.optionButton.size_y - menu.optionButton.text_size_y) / 2;

    menu.exitButton.size_x = BUTTON_SIZE_X;
    menu.exitButton.size_y = BUTTON_SIZE_Y;
    menu.exitButton.text_size_x = BUTTON_SIZE_X - 80;
    menu.exitButton.text_size_y = BUTTON_SIZE_Y - 10;
    menu.exitButton.loc_x = menu.optionButton.loc_x;
    menu.exitButton.loc_y = menu.optionButton.loc_y + menu.optionButton.size_y + 20;
    menu.exitButton.text_loc_x = menu.exitButton.loc_x + (menu.exitButton.size_x - menu.exitButton.text_size_x) / 2;
    menu.exitButton.text_loc_y = menu.exitButton.loc_y + (menu.exitButton.size_y - menu.exitButton.text_size_y) / 2;
}
