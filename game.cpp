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
const int move_speed = 1;
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
    snake = {WIDTH/2/snake_size, HEIGHT/2/snake_size, 0, NULL};
    dir = UP;
    srand(time(NULL));
    food = {rand() % WIDTH/snake_size, rand() % HEIGHT/snake_size};
}

void free_tail(){
    snake_tail* head = snake.tail;
    snake_tail* tmp;
    while(head != NULL){
        tmp = head;
        head = head->tail;
        free(tmp);
    }
}

void exit(){
    free_tail();
    running = false;
    SDL_Quit();
}

void add_tail(){
    //std::cout << "snake length = " << snake.length << "\n";
    snake_tail* new_tail = (snake_tail*)malloc(sizeof(snake_tail));
    *new_tail = {snake.x, snake.y, NULL};
    if(snake.length != 0){
        snake_tail* last = snake.tail;
        for(int i = 1; i < snake.length; i++)
            last = last->tail;
        last->tail = new_tail;
    }
    else{
        snake.tail = new_tail;
    }
    snake.length = snake.length + 1;
}

void move_food(){
    food = {rand() % WIDTH/snake_size, rand() % HEIGHT/snake_size};
}

void draw(){
    //Clear the screen
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(gRenderer);

    //Draw snake head
    SDL_Rect rect = {snake.x*snake_size, snake.y*snake_size, snake_size, snake_size};
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(gRenderer, &rect);

    //Draw snake tail
    snake_tail* tail = snake.tail;
    for(int i = 0; i < snake.length; i++){
        rect = {tail->x*snake_size, tail->y*snake_size, snake_size, snake_size};
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(gRenderer, &rect);
        tail = tail->tail;
    }

    //Draw food
    rect = {food.x*snake_size, food.y*snake_size, food_size, food_size};
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0xFF, 0xFF);
    SDL_RenderFillRect(gRenderer, &rect);

    //Update Screen
    SDL_RenderPresent(gRenderer);
}

void input(int k){
    switch (k){
        case SDLK_UP:
            if(dir == LEFT || dir == RIGHT)
                dir = UP;
            break;
        case SDLK_LEFT:
            if(dir == UP || dir == DOWN)
                dir = LEFT;
            break;
        case SDLK_DOWN:
            if(dir == LEFT || dir == RIGHT)
                dir = DOWN;
            break;
        case SDLK_RIGHT:
            if(dir == UP || dir == DOWN)
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
    //std::cout << "snake(x,y) = (" << snake.x << "," << snake.y << ")\nfood(x,y) = (" << food.x << "," << food.y << ")\n";
    //Check if food is eaten
    if(snake.x == food.x && snake.y == food.y){
        add_tail();
        move_food();
    }

    //Move snake tail
    int prev_x, prev_y;
    snake_tail* tail = NULL;
    for(int i = 0; i < snake.length; i++){
        if(i == 0){ //tail just behind head
            tail = snake.tail;
            prev_x = tail->x;
            prev_y = tail->y;
            tail->x = snake.x;
            tail->y = snake.y;
        }
        else{
            int tmp_x, tmp_y;
            tail = tail->tail;
            tmp_x = tail->x;
            tmp_y = tail->y;
            tail->x = prev_x;
            tail->y = prev_y;
            prev_x = tmp_x;
            prev_y = tmp_y;
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
        logic();
        draw();
        SDL_Delay(frame_delay);
        poll_events();
    }
    return 0;
}
