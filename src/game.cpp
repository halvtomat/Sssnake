#include "game.h"

void setup(){
    running = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
        running = false;
    }
    else{
        window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
        if(window == NULL){
            std::cout << "Window could not be created SDL_Error: " << SDL_GetError() << "\n";
            running = false;
        }
        else{
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if(renderer == NULL){
                std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << "\n";
                running = false;
            }
        }
    }
    if(score.error)
        running = false;
}

void exit(){
    snake.~Snake();
    food.~Food();
    score.~Score();
    SDL_Quit();
}

void draw(){
    //Clear the screen
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    //Draw snake and food and score
    snake.draw(renderer);
    food.draw(renderer);
    score.draw(renderer);

    //Update Screen
    SDL_RenderPresent(renderer);
}

void input(int k){
    if(k == SDLK_ESCAPE)
        running = false;
    else
        snake.change_dir(k);
}

void logic(){
    if(snake.collision()){
        running = false;
    }
    //Check if food is eaten
    if(snake.get_x() == food.get_x() && snake.get_y() == food.get_y()){
        snake.add_tail();
        score.set(snake.get_length());
        food.move();
    }
    snake.move();
}

void poll_events(){
    while(SDL_PollEvent(&e) != 0){
        if(e.type == SDL_QUIT)
            running = false;
        if(e.type == SDL_KEYDOWN)
            input(e.key.keysym.sym);
    }
}

int main(){
    setup();
    while(running){
        unsigned int start = SDL_GetTicks();
        logic();
        draw();
        poll_events();
        SDL_Delay(start + 48 - SDL_GetTicks());
    }
    std::cout << "Final score: " << score.get() << "\n";
    exit();
    return 0;
}