#include <iostream>
#include <unistd.h>
#include <ncurses.h>

bool running;
const int height = 20;
const int width = 20;
int snake_x, snake_y, length, food_x, food_y; 
enum e_dir {LEFT = 0, UP = 1, RIGHT = 2, DOWN = 3};
e_dir dir;

void setup(){
    initscr();
    running = true;
    dir = UP;
    snake_x = width/2;
    snake_y = height/2;
    food_x = rand() % width;
    food_y = rand() % height;
}

void draw(){
    system("clear");

    for(int i = 0; i < width+2; i++){
        printw("#");
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
}

void input(){
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
    setup();
    while(running){
        draw();
        input();
        logic();
        sleep(1);
    }
    endwin();
    return 0;
}
