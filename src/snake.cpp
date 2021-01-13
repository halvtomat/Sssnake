#include "snake.h"

void Snake::free_tail(){
    snake_part* curr = head.tail;
    snake_part* tmp;
    while(curr != NULL){
        tmp = curr;
        curr = curr->tail;
        free(tmp);
    }
}

Snake::Snake(int window_width, int window_height, int size, int move_speed){
    WINDOW_WIDTH = window_width;
    WINDOW_HEIGHT = window_height;
    this->size = size;
    this->move_speed = move_speed;

    head = {WINDOW_WIDTH/2/size, WINDOW_HEIGHT/2/size, NULL};
    dir = UP;
}
Snake::~Snake(){
    free_tail();
}

void Snake::add_tail(){
    snake_part* new_tail = (snake_part*)malloc(sizeof(snake_part));
    *new_tail = {head.x, head.y, NULL};
    if(length != 0){
        snake_part* last = head.tail;
        for(int i = 1; i < length; i++)
            last = last->tail;
        last->tail = new_tail;
    }
    else{
        head.tail = new_tail;
    }
    length = length + 1;
}

void Snake::draw(SDL_Renderer* renderer){
    //Draw snake head
    SDL_Rect rect = {head.x*size, head.y*size, size, size};
    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(renderer, &rect);

    //Draw snake tail
    snake_part* tail = head.tail;
    for(int i = 0; i < length; i++){
        rect = {tail->x*size, tail->y*size, size, size};
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(renderer, &rect);
        tail = tail->tail;
    }
}

void Snake::move(){
        //Move snake tail
    int prev_x, prev_y;
    snake_part* tail = NULL;
    for(int i = 0; i < length; i++){
        if(i == 0){ //tail just behind head
            tail = head.tail;
            prev_x = tail->x;
            prev_y = tail->y;
            tail->x = head.x;
            tail->y = head.y;
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
            head.y -= move_speed;
            break;
        case LEFT:
            head.x -= move_speed;
            break;
        case DOWN:
            head.y += move_speed;
            break;
        case RIGHT:
            head.x += move_speed;
            break;
        default:
            break;
        }
    //Window-edge teleporting
    if(head.x*size > WINDOW_WIDTH)
        head.x = 0;
    if(head.x*size < 0)
        head.x = WINDOW_WIDTH/size;
    if(head.y*size > WINDOW_HEIGHT)
        head.y = 0;
    if(head.y*size < 0)
        head.y = WINDOW_HEIGHT/size;
}

void Snake::change_dir(int new_dir){
    switch(new_dir){
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
        default:
            break;
    }
}
int Snake::get_x(){
    return head.x;
}
int Snake::get_y(){
    return head.y;
}
int Snake::get_length(){
    return length;
}