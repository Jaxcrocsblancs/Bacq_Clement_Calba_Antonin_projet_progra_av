SRC = main.c procedural.c affichage.c SDL_rotozoom.c
INC = include.h procedural.h define.h affichage.h SDL_rotozoom.h

# SRC = $(wildcard *.c)
# INC = $(wildcard *.h)

OBJ = $(SRC:.c=.o)
BIN = projet

CPPFLAGS = `sdl-config --cflags`
CFLAGS   = -std=c99 -Wall -Wextra -g
LDFLAGS  = `sdl-config --libs` -lm

.PHONY: all clean

all: $(BIN)

$(OBJ): $(INC)

$(BIN): $(OBJ)
	$(CC) $^ $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH) -o $@

clean:
	rm -f $(OBJ)
	rm -f $(BIN)
