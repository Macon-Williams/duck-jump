#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
    Uint64 previousTicks, currentTicks, ticksPerSecond;
    double deltaTime;
} Timer;

typedef struct {
    TTF_Font *font;
    SDL_Texture *text;
} Text;

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *loadingText;
    SDL_Texture *enterText;
    Timer timer;
    enum gameState {MENU, RUNNING, SCORE, CLOSE} gameState;
} Game;

typedef struct {
    SDL_Texture *buttonImage;
    SDL_Texture *buttonText;
    SDL_Rect buttonClip[3];
    int loc_x, loc_y;
    int size_x, size_y;
    int text_loc_x, text_loc_y;
    int text_size_x, text_size_y;
    enum buttonState{MOUSE_OUT, MOUSE_OVER, MOUSE_DOWN} state;
} Button;

typedef struct {
    int loc_x, loc_y;
    int size_x, size_y;
    int bounce_value;
    bool off_screen;
} Platform;

typedef struct {
    SDL_Texture *defaultTexture;
} PlatformTexture;

typedef struct {
    Text titleText;
    Button playButton;
    Button exitButton;
    Button scoreButton;
    Button optionButton;
    Platform menuPlatform;
} Menu;

typedef struct {
    SDL_Texture *duckSprite;
    SDL_Rect duckClip[2];
    int frame;
    int score;
    double loc_x, loc_y;
    int size_x, size_y;
    double velocity_x, velocity_y;
    int move_x, move_y;
    char name[10];
} Player;

#endif