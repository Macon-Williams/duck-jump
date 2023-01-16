#include "player.h"

void initPlayer() {
    // Load player sprite graphic
    player.duckSprite = loadTexture(PLAYER_SPRITE_PATH);
    initClip(player.duckClip, 2, 16, 16);   // 2 frames, each frame is 16x16

    // Initializing variables to get rid of garbage data
    player.size_x = 64;     // Rendered size x on screen
    player.size_y = 64;     // Rendered size y on screen
    player.loc_x = 150;     // Starting position X
    player.loc_y = 250;     // Starting position Y
    player.velocity_x = 0;  // Starting velocity X
    player.velocity_y = 0;  // Starting velocity Y
    player.move_x = 0;      // Keyboard input X
    player.move_y = 0;      // Keyboard input Y (Unused)
    player.frame = 0;       // Current sprite frame
    player.score = 0;       // Player's current score
    player.flipped = false; // Player default is facing right
    player.lost = false;    // Player hasn't lost the game... yet
}

// Handles side to side duck movement as well as gravity
void moveDuck(double deltaTime, bool moveable) {
    gravity(deltaTime);
    if (moveable)
        moveX(deltaTime);
}

// Moves camera to focus on player
void moveCamera(SDL_Rect* camera) {
    if (player.velocity_y < 0 && player.loc_y + player.size_y <= camera->y + (SCREEN_HEIGHT / 2) + (player.size_y / 2)) {
        camera->y = (player.loc_y + player.size_y / 2) - SCREEN_HEIGHT / 2;
        player.score = abs(camera->y);
    }
}

// Renders the player sprite on screen
void renderPlayerSprite(SDL_Rect* camera) {
    SDL_Rect renderQuad = {(int) player.loc_x, (int) player.loc_y - camera->y, player.size_x, player.size_y};
    if (player.flipped) {
        SDL_RenderCopyEx(game.renderer, player.duckSprite, &player.duckClip[player.frame], &renderQuad, 0, NULL, SDL_FLIP_HORIZONTAL);
    } else {
        SDL_RenderCopyEx(game.renderer, player.duckSprite, &player.duckClip[player.frame], &renderQuad, 0, NULL, 0);
    }

    if (player.loc_y > camera->y + SCREEN_HEIGHT) {
        player.lost = true;
    }
}

// Handles X movement on screen
/* I needed a way to smoothly move the character from side to side depending on keyboard input.
 * This method first calculates acceleration (taking into account which direction the acceleration is).
 * Afterwards it applies this acceleration to the velocity until the velocity becomes too high, then
 * the input is ignored.
*/ 
void moveX(double deltaTime) {
    double acceleration;
    if (player.move_x) {
        acceleration = PLAYER_MOVEMENT_ACCELERAITON * 5 * player.move_x;
    } else {
        acceleration = -5 * player.velocity_x;
        if (fabs(player.velocity_x) < 1) player.velocity_x = 0;
    }

    player.velocity_x += acceleration * deltaTime;

    if (fabs(player.velocity_x) > MAX_PLAYER_SPEED) player.velocity_x = MAX_PLAYER_SPEED * player.move_x;
    player.loc_x += player.velocity_x * deltaTime;

    if (player.loc_x + player.size_x / 2 >= SCREEN_WIDTH) {
        player.loc_x -= SCREEN_WIDTH;
    } 
    if (player.loc_x + player.size_x / 2 <= 0) {
        player.loc_x += SCREEN_WIDTH;
    } 
}

// Handles gravity input on screen
void gravity(double deltaTime) {
    player.velocity_y += (GRAVITY * deltaTime);
    player.loc_y += (player.velocity_y * deltaTime);
    if (player.velocity_y > 0) {
        player.frame = 1;      
    } else {
        player.frame = 0;
    }
}
