#include "init.h"

extern Game game;

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
    game.renderer = SDL_CreateRenderer(game.window, -1, SDL_RENDERER_ACCELERATED);
    if (!game.renderer) {
        printf("Failed to create renderer! SDL Error: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Initialize the font engine
    if (TTF_Init() < 0) {
        printf("Unable to initialize TTF fonts! See error: %s", TTF_GetError());
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

void initTextures(Player* player, Menu* menu) {
    // Load the texture files
    player->duckSprite = loadTexture(PLAYER_SPRITE_PATH);
    initClip(player->duckClip, 2, 16, 16);

    player->size_x = 64;
    player->size_y = 64;
    player->loc_x = 200;
    player->loc_y = 250;
    player->velocity_x = 0;
    player->velocity_y = 0;
    player->move_x = 0;
    player->move_y = 0;
    player->frame = 0;

    menu->playButton.buttonImage = loadTexture(PLAY_BUTTON_SPRITE_PATH);
    initClip(menu->playButton.buttonClip, 3, 108, 44);

    menu->scoreButton.buttonImage = loadTexture(BUTTON_SPRITE_PATH);
    initClip(menu->scoreButton.buttonClip, 3, 96, 26);

    menu->optionButton.buttonImage = loadTexture(BUTTON_SPRITE_PATH);
    initClip(menu->optionButton.buttonClip, 3, 96, 26);

    menu->exitButton.buttonImage = loadTexture(BUTTON_SPRITE_PATH);
    initClip(menu->exitButton.buttonClip, 3, 96, 26);

    menu->menuPlatform.sprite = loadTexture(PLATFORM_SPRITE_PATH);
    menu->menuPlatform.loc_y = 500;
    menu->menuPlatform.size_x = 128;
    menu->menuPlatform.size_y = 32;
}

SDL_Texture *generateText(char* text, SDL_Color textColor, TTF_Font* font) {
    SDL_Surface* tempMenuTextSurface = TTF_RenderUTF8_Solid(font, text, textColor);
    if (!tempMenuTextSurface) {
        printf("Unable to render text: %s! SDL_ttf Error: %s\n", text, TTF_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Texture* tempMenuTextTexture = SDL_CreateTextureFromSurface(game.renderer, tempMenuTextSurface);
    SDL_FreeSurface(tempMenuTextSurface);
    return tempMenuTextTexture;
}

void initFont(Text* text) {
    // Initializes a font within a text object
    
    text->font = TTF_OpenFont(FONT_PATH, 48);
    if (!text->font) {
        printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
}

void initButtons(Menu* menu, TTF_Font* font) {
    SDL_Color textColor = {0, 0, 0};

    // Generate text images
    menu->titleText.text = generateText("Duck Jump", textColor, font);
    menu->playButton.buttonText = generateText("Play", textColor, font);
    menu->scoreButton.buttonText = generateText("High Scores", textColor, font);
    menu->optionButton.buttonText = generateText("Options", textColor, font);
    menu->exitButton.buttonText = generateText("Exit", textColor, font);

    // Set buttons in a MOUSE_OUT state
    menu->playButton.state = MOUSE_OUT;
    menu->scoreButton.state = MOUSE_OUT;
    menu->optionButton.state = MOUSE_OUT;
    menu->exitButton.state = MOUSE_OUT;

    // Set size and location for the play button
    menu->playButton.size_x = PLAY_BUTTON_SIZE_X;
    menu->playButton.size_y = PLAY_BUTTON_SIZE_Y;
    menu->playButton.text_size_x = PLAY_BUTTON_SIZE_X - 35;     // Text slightly smaller than the button width
    menu->playButton.text_size_y = PLAY_BUTTON_SIZE_Y - 20;     // Text slightly smaller than the button height
    menu->playButton.loc_x = ((SCREEN_WIDTH - PLAY_BUTTON_SIZE_X) * 8) / 9;     // Location in the right side of the screen
    menu->playButton.loc_y = (SCREEN_HEIGHT - PLAY_BUTTON_SIZE_Y) / 2;          // Location half way down the screen
    menu->playButton.text_loc_x = menu->playButton.loc_x + (menu->playButton.size_x - menu->playButton.text_size_x) / 2;        // Center the text inside the button
    menu->playButton.text_loc_y = menu->playButton.loc_y + (menu->playButton.size_y - menu->playButton.text_size_y) / 2;        // Center the text inside the button

    menu->scoreButton.size_x = BUTTON_SIZE_X;
    menu->scoreButton.size_y = BUTTON_SIZE_Y;
    menu->scoreButton.text_size_x = BUTTON_SIZE_X - 20;     // Text slightly smaller than the button width
    menu->scoreButton.text_size_y = BUTTON_SIZE_Y - 10;     // Text slightly smaller than the button height
    menu->scoreButton.loc_x = menu->playButton.loc_x + ((menu->playButton.size_x - menu->scoreButton.size_x) / 2);  // Location centered with the play button
    menu->scoreButton.loc_y = menu->playButton.loc_y + menu->playButton.size_y + 20;                                // Location below the play button with a padding of 20 pixels
    menu->scoreButton.text_loc_x = menu->scoreButton.loc_x + (menu->scoreButton.size_x - menu->scoreButton.text_size_x) / 2;    // Text centered in the button
    menu->scoreButton.text_loc_y = menu->scoreButton.loc_y + (menu->scoreButton.size_y - menu->scoreButton.text_size_y) / 2;    // Text ceneterd in the button

    menu->optionButton.size_x = BUTTON_SIZE_X;
    menu->optionButton.size_y = BUTTON_SIZE_Y;
    menu->optionButton.text_size_x = BUTTON_SIZE_X - 40;    // Text slightly smaller than the button width
    menu->optionButton.text_size_y = BUTTON_SIZE_Y - 10;    // Text slightly smaller than the button height
    menu->optionButton.loc_x = menu->scoreButton.loc_x;                                     // Location centered with the score button
    menu->optionButton.loc_y = menu->scoreButton.loc_y + menu->scoreButton.size_y + 20;     // Location below the score button with a padding of 20 pixels
    menu->optionButton.text_loc_x = menu->optionButton.loc_x + (menu->optionButton.size_x - menu->optionButton.text_size_x) / 2;    // Text centered in the button
    menu->optionButton.text_loc_y = menu->optionButton.loc_y + (menu->optionButton.size_y - menu->optionButton.text_size_y) / 2;    // Text centered in the button

    menu->exitButton.size_x = BUTTON_SIZE_X;
    menu->exitButton.size_y = BUTTON_SIZE_Y;
    menu->exitButton.text_size_x = BUTTON_SIZE_X - 80;  // Text slightly smaller than the button width
    menu->exitButton.text_size_y = BUTTON_SIZE_Y - 10;  // Text slightly smaller than the button height
    menu->exitButton.loc_x = menu->optionButton.loc_x;                                      // Location centered with the option button
    menu->exitButton.loc_y = menu->optionButton.loc_y + menu->optionButton.size_y + 20;     // Location below the option button with a padding of 20 pixels
    menu->exitButton.text_loc_x = menu->exitButton.loc_x + (menu->exitButton.size_x - menu->exitButton.text_size_x) / 2;    // Text centered in the button
    menu->exitButton.text_loc_y = menu->exitButton.loc_y + (menu->exitButton.size_y - menu->exitButton.text_size_y) / 2;    // Text centered in the button
}
