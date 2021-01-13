#include "food.h"

Food::Food(int window_width, int window_height, int size){
    WINDOW_WIDTH = window_width;
    WINDOW_HEIGHT = window_height;
    this->size = size;
    srand(time(NULL));
    x = rand() % WINDOW_WIDTH/size;
    y = rand() % WINDOW_HEIGHT/size;
}

Food::~Food(){
    //Food is destroyed
}

void Food::move(){
    x = rand() % WINDOW_WIDTH/size;
    y = rand() % WINDOW_HEIGHT/size;
}

void Food::draw(SDL_Renderer* renderer){
    SDL_Rect rect = {x*size, y*size, size, size};
    SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRect(renderer, &rect);
}

int Food::get_x(){
    return x;
}

int Food::get_y(){
    return y;
}