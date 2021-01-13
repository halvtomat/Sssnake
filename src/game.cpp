#include <iostream>
#include <SDL2/SDL.h>
#include "snake.h"
#include "food.h"

bool running;
const int HEIGHT = 720;
const int WIDTH = 1280;
const int move_speed = 1;
const int snake_size = 20;
const int food_size = 20;
Snake snake(WIDTH, HEIGHT, snake_size, move_speed);
Food food(WIDTH, HEIGHT, food_size); 

SDL_Window* window = NULL;
SDL_Surface* screen_surface = NULL;
SDL_Renderer* renderer = NULL; 
SDL_Event e;

void setup(){
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
    else{
        window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
        if(window == NULL)
            std::cout << "Window could not be created SDL_Error: " << SDL_GetError() << "\n";
        else{
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if(renderer == NULL)
                std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << "\n";
        }
    }
    running = true;
}

void exit(){
    snake.~Snake();
    food.~Food();
    running = false;
    SDL_Quit();
}

void draw(){
    //Clear the screen
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    snake.draw(renderer);
    food.draw(renderer);

    //Update Screen
    SDL_RenderPresent(renderer);
}

void input(int k){
    if(k == SDLK_ESCAPE){
        exit();
        return;
    }
    else{
        snake.change_dir(k);
    }
}

void logic(){
    //Check if food is eaten
    if(snake.get_x() == food.get_x() && snake.get_y() == food.get_y()){
        snake.add_tail();
        food.move();
    }
    snake.move();
}

void poll_events(){
    while(SDL_PollEvent(&e) != 0){
        if(e.type == SDL_QUIT)
            exit();
        if(e.type == SDL_KEYDOWN)
            input(e.key.keysym.sym);
    }
}

int main(int argc, char const *argv[]){
    setup();
    while(running){
        unsigned int start = SDL_GetTicks();
        logic();
        draw();
        poll_events();
        SDL_Delay(start + 32 - SDL_GetTicks());
    }
    return 0;
}
