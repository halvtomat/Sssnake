#ifndef SCORE_H
#define SCORE_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Score{
    public:
        Score(int window_width, int window_height, std::string font_path, int font_size);
        ~Score();
        void draw(SDL_Renderer* renderer);
        void set(int x);
        int get();
        bool error = false;
    private:
        int WINDOW_WIDTH;
        int WINDOW_HEIGHT;
        int score = 0;
        TTF_Font* font = NULL;
        SDL_Texture* texture = NULL;
        SDL_Surface* surface = NULL;
        SDL_Color color = {0, 0, 0};
};

#endif