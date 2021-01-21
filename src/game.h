#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "snake.h"
#include "food.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const int move_speed = 1;
const int snake_size = 20;
const int food_size = 20;
const int font_size = 64;
Snake snake(WINDOW_WIDTH, WINDOW_HEIGHT, snake_size, move_speed);
Food food(WINDOW_WIDTH, WINDOW_HEIGHT, food_size);

SDL_Window* window = NULL;
SDL_Surface* screen_surface = NULL;
SDL_Renderer* renderer = NULL; 
SDL_Event e;
TTF_Font* score_font = NULL;

bool running;

void setup();
void exit();
void draw();
void input();
void logic();
void poll_events();
int main();

#endif