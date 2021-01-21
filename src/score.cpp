#include "score.h"

Score::Score(int window_width, int window_height, std::string font_path, int font_size){
    WINDOW_WIDTH = window_width;
    WINDOW_HEIGHT = window_height;

    if(TTF_Init() < 0){
        std::cout << "SDL_ttf could not be initialized! SDL_ttf Error: " << SDL_GetError() << "\n";
        error = true;
    }    

    font = TTF_OpenFont("/home/daniel/Documents/Sssnake/src/media/BebasNeue-Regular.ttf", font_size);
    
    if(font == NULL){
        std::cout << "TTF_OpenFont could not load font! TTF_Error: " << TTF_GetError() << "\n";
        error = true;
    }
}

Score::~Score(){
    TTF_Quit();
}

void Score::draw(SDL_Renderer* renderer){
    SDL_Rect rect = {WINDOW_WIDTH-40, 40, 40, 40};
    surface = TTF_RenderText_Solid(font, std::to_string(score).c_str(), color);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Score::set(int x){
    score = x;
}

int Score::get(){
    return score;
}