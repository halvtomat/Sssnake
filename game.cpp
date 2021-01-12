#include <iostream>
#include <unistd.h>
#include <SDL2/SDL.h>

bool running;
const int HEIGHT = 480;
const int WIDTH = 640;
const int move_speed = 10;
const int frame_delay = 100;
int snake_x, snake_y, length, food_x, food_y; 
enum e_dir {LEFT = 0, UP = 1, RIGHT = 2, DOWN = 3};
e_dir dir;

SDL_Window* window = NULL;
SDL_Surface* screen_surface = NULL;
SDL_Renderer* gRenderer = NULL; 
SDL_Event e;

void setup(){
    snake_x = WIDTH/2;
    snake_y = HEIGHT/2;
    dir = UP;
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
    else{
        window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
        if(window == NULL)
            std::cout << "Window could not be created SDL_Error: " << SDL_GetError() << "\n";
        else{
            gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if(gRenderer == NULL)
                std::cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << "\n";
        }
    }
    running = true;
    dir = UP;
    snake_x = WIDTH/2;
    snake_y = HEIGHT/2;
    food_x = rand() % WIDTH;
    food_y = rand() % HEIGHT;
}

void exit(){
    running = false;
    SDL_Quit();
}

void draw(){
    //Clear the screen
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);

    //Draw snake
    SDL_Rect head = {snake_x, snake_y, 20, 20};
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(gRenderer, &head);

    //Update Screen
    SDL_RenderPresent(gRenderer);
}

void input(int k){
    switch (k){
        case SDLK_UP:
            dir = UP;
            break;
        case SDLK_LEFT:
            dir = LEFT;
            break;
        case SDLK_DOWN:
            dir = DOWN;
            break;
        case SDLK_RIGHT:
            dir = RIGHT;
            break;
        case SDLK_ESCAPE:
            exit();
            break;
        default:
            break;
    }
}

void logic(){
    switch (dir){
        case UP:
            snake_y -= move_speed;
            break;
        case LEFT:
            snake_x -= move_speed;
            break;
        case DOWN:
            snake_y += move_speed;
            break;
        case RIGHT:
            snake_x += move_speed;
            break;
        default:
            break;
        }
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
        poll_events();
        draw();
        logic();
        SDL_Delay(frame_delay);
    }
    return 0;
}
