# Files to compile
OBJS = main.c init.c menu.c timer.c player.c game.c

# Compiler to use
CC = gcc

# Compiler flags
# COMPILER_FLAGS = -Wall
COMPILER_FLAGS = -Wall -F /Library/Frameworks

# Linker flags
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

OBJ_EXEC = Game

all: $(OBJS)
		$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_EXEC) -g
		

