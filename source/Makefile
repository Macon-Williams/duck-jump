# Files to compile
OBJS = main.c init.c menu.c

# Compiler to use
CC = gcc

# Compiler flags
COMPILER_FLAGS = -Wall

# Linker flags
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

OBJ_EXEC = Game.x86_64

all: $(OBJS)
		$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_EXEC) -g
		

