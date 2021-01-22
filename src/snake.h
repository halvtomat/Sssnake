#ifndef SNAKE_H
#define SNAKE_H

#include <SDL2/SDL.h>

class Snake{
    public:
        Snake(int window_width, int window_height, int size, int move_speed);
        ~Snake();
        void add_tail();
        void draw(SDL_Renderer* renderer);
        void move();
        void change_dir(int new_dir);
        int get_x();
        int get_y();
        int get_length();
        bool collision();
    private:
        int WINDOW_WIDTH;
        int WINDOW_HEIGHT; 
        int size;
        int move_speed;
        int length;
        enum e_dir {LEFT = 0, UP = 1, RIGHT = 2, DOWN = 3} dir;
        struct snake_part{
            int x;
            int y;
            snake_part* tail;
        } head;
        void free_tail();
};

#endif