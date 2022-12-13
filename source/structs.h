#ifndef STRUCTS_H
#define STRUCTS_H


typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
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
    Button playButton;
    Button exitButton;
    Button scoreButton;
    Button optionButton;
} MenuButtons;

typedef struct {
    TTF_Font *menuFont;
    SDL_Texture *titleText;
    // SDL_Texture *buttonPlayText;
    // SDL_Texture *buttonScoreText;
    // SDL_Texture *buttonOptionText;
    // SDL_Texture *buttonExitText;
} Text;

typedef struct {
    SDL_Texture *duckSprite;
    SDL_Rect duckClip[2];
    char name[10];
} Player;

#endif