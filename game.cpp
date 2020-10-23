#include <iostream>
#include <unistd.h>
#include <ncurses.h>

bool running;
int height, width;
int snake_x, snake_y, length, food_x, food_y; 
enum e_dir {LEFT = 0, UP = 1, RIGHT = 2, DOWN = 3};
e_dir dir;

const char edgechar = '#';
const char snakeheadchar = '@';

void draw_window(){
    for(int i = 0; i < width; i++){
        move(0,i);
        addch(edgechar);
    }

    for(int i = 0; i < width; i++){
        move(height-1,i);
        addch(edgechar);
    }

    for(int i = 0; i < height; i++){
        move(i,0);
        addch(edgechar);
    }

    for(int i = 0; i < height; i++){
        move(i,width-1);
        addch(edgechar);
    }
    return;
}

void setup(){
    initscr();
    nodelay(stdscr,TRUE);
    keypad(stdscr,TRUE);
    noecho();
    curs_set(0);
    getmaxyx(stdscr, height, width);
    running = true;
    dir = UP;
    snake_x = width/2;
    snake_y = height/2;
    food_x = rand() % width;
    food_y = rand() % height;
    draw_window();
}

void draw_snake(){
    move(snake_y,snake_x);
    addch(snakeheadchar);
    refresh();
}

void input(){
    int in = getch();
    switch (in){
        case KEY_UP:
            dir = UP;
            break;
        case KEY_LEFT:
            dir = LEFT;
            break;
        case KEY_DOWN:
            dir = DOWN;
            break;
        case KEY_RIGHT:
            dir = RIGHT;
            break;
        default:
            break;
    }

}
void logic(){
    switch (dir){
        case UP:
            snake_y--;
            break;
        case LEFT:
            snake_x--;
            break;
        case DOWN:
            snake_y++;
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
        draw_snake();
        input();
        logic();
        usleep(50000);
    }
    nodelay(stdscr, FALSE);
    getch();
    endwin();
    return 0;
}
