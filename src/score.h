#ifndef SCORE_H
#define SCORE_H

#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

class Score{
    public:
        Score(std::string font_path);
        ~Score();
        void draw(SDL_Renderer* renderer);
        void set(int x);
        int get();
    private:
        int score;
        TTF_Font* score_font = NULL;
};

#endif