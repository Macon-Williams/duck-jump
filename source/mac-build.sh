gcc main.c init.c menu.c timer.c player.c game.c -o Game  `pkg-config --cflags --libs sdl2 sdl2_mixer sdl2_image sdl2_ttf`
