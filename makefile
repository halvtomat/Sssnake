#OBJS define object files
OBJS = game.cpp snake.cpp

#OBJ_NAME defines the name of the executable
OBJ_NAME = Game

all : $(OBJS)
	g++ $(OBJS) -o $(OBJ_NAME) -lSDL2 -Wall
