#OBJS define object files
OBJS = src/game.cpp src/snake.cpp src/food.cpp src/score.cpp

#OBJ_NAME defines the name of the executable
OBJ_NAME = Game

CFLAGS = -lSDL2 -Wall -lSDL2_ttf

all : $(OBJS)
	g++ $(OBJS) -o $(OBJ_NAME) $(CFLAGS)