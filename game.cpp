#include <iostream>
#include <unistd.h>
#include <SDL2/SDL.h>

bool running;
const int HEIGHT = 480;
const int WIDTH = 640;
int snake_x, snake_y, length, food_x, food_y; 
enum e_dir {LEFT = 0, UP = 1, RIGHT = 2, DOWN = 3};
e_dir dir;

void setup(SDL_Window* window, SDL_Surface* screen_surface){
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << "\n";
    else{
        window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
        if(window == NULL)
            std::cout << "Window could not be created SDL_Error: " << SDL_GetError() << "\n";
        else{
            screen_surface = SDL_GetWindowSurface(window);
            SDL_FillRect(screen_surface, NULL, SDL_MapRGB(screen_surface->format, 0xFF, 0xFF, 0xFF));
            SDL_UpdateWindowSurface(window);
            SDL_Delay(2000);
        }
    }
    running = true;
    dir = UP;
    snake_x = WIDTH/2;
    snake_y = HEIGHT/2;
    food_x = rand() % WIDTH;
    food_y = rand() % HEIGHT;
}

void draw(){
    /*
    system("clear");

    for(int i = 0; i < width+2; i++){
        //printw("#");
    }
    printw("\n");

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width+2; j++){
            if(j == 0 || j == width+1) printw("#");
            else if(i == snake_y && j == snake_x) printw("@");
            else if(i == food_y && j == food_x) printw("+");
            else printw(" ");
        }
        printw("\n");
    }

    for(int i = 0; i < width+2; i++){
        printw("#");
    }
    printw("\n");
    */
}

void input(){
    /*
    if(int in = getch() != ERR){
        switch (in){
        case 'w':
            dir = UP;
            break;
        case 'a':
            dir = LEFT;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'd':
            dir = RIGHT;
            break;
        default:
            break;
        }
    }
*/
}

void logic(){
    switch (dir){
        case UP:
            snake_y++;
            break;
        case LEFT:
            snake_x--;
            break;
        case DOWN:
            snake_y--;
            break;
        case RIGHT:
            snake_x++;
            break;
        default:
            break;
        }
}

int main(int argc, char const *argv[]){
    SDL_Window* window = NULL;
    SDL_Surface* screen_surface = NULL;
    setup(window, screen_surface);
    while(running){
        draw();
        input();
        logic();
        sleep(1);
        SDL_Quit();
        running = false;
    }
    return 0;
}
