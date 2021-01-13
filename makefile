#OBJS define object files
OBJS = src/game.cpp src/snake.cpp src/food.cpp

#OBJ_NAME defines the name of the executable
OBJ_NAME = Game

all : $(OBJS)
	g++ $(OBJS) -o $(OBJ_NAME) -lSDL2 -Wall