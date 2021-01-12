#include <iostream>
#include <unistd.h>
#include <SDL2/SDL.h>


struct snake_tail{
    int x;
    int y;
    snake_tail* tail;
};

struct snake_head{
    int x;
    int y;
    int length;
    snake_tail* tail;
};

struct food_{
    int x;
    int y;
};

bool running;
const int HEIGHT = 480;
const int WIDTH = 640;
const int move_speed = 10;
const int frame_delay = 100;
const int snake_size = 20;
const int food_size = 20;
snake_head snake;
food_ food; 
enum e_dir {LEFT = 0, UP = 1, RIGHT = 2, DOWN = 3};
e_dir dir;

SDL_Window* window = NULL;
SDL_Surface* screen_surface = NULL;
SDL_Renderer* gRenderer = NULL; 
SDL_Event e;

void setup(){

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

    snake.x = WIDTH/2;
    snake.y = HEIGHT/2;
    snake.length = 1;
    snake_tail tail;
    tail.x = 1;
    tail.y = 1;
    tail.tail = NULL;
    snake.tail = &tail;
    dir = UP;
    srand(time(NULL));
    food.x = rand() % WIDTH;
    food.y = rand() % HEIGHT;
    std::cout << "a\n";
}

void exit(){
    running = false;
    SDL_Quit();
}

void draw(){
    //Clear the screen
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);

    //Draw snake head
    SDL_Rect rect = {snake.x, snake.y, snake_size, snake_size};
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(gRenderer, &rect);

    //Draw snake tail
    snake_tail* tail = snake.tail;
    for(int i = 0; i < snake.length; i++){
        rect = {tail->x, tail->y, snake_size, snake_size};
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(gRenderer, &rect);
        tail = tail->tail;
    }

    //Draw food
    rect = {food.x, food.y, food_size, food_size};
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRect(gRenderer, &rect);

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
    //Move snake tail
    snake_tail* prev = NULL;
    snake_tail* tail = NULL;
    for(int i = 0; i < snake.length; i++){
        if(i = 0){ //tail just behind head
            tail = snake.tail;
            tail->x = snake.x;
            tail->y = snake.y;
        }
        else{
            prev = tail;
            tail = prev->tail;
            tail->x = prev->x;
            tail->y = prev->y;
        }
    }

    //Move snake head
    switch (dir){
        case UP:
            snake.y -= move_speed;
            break;
        case LEFT:
            snake.x -= move_speed;
            break;
        case DOWN:
            snake.y += move_speed;
            break;
        case RIGHT:
            snake.x += move_speed;
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
        logic();
        draw();
        SDL_Delay(frame_delay);
    }
    return 0;
}
