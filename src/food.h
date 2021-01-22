#ifndef FOOD_H
#define FOOD_H

#include <ctime>
#include <SDL2/SDL.h>
class Food{
    public:
        Food(int window_width, int window_height, int size);
        ~Food();
        void move();
        void draw(SDL_Renderer* renderer);
        int get_x();
        int get_y();
    private:
        int WINDOW_WIDTH;
        int WINDOW_HEIGHT; 
        int x;
        int y;
        int size;
};

#endif