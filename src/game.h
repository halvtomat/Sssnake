#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include "snake.h"
#include "food.h"
#include "score.h"

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const int move_speed = 1;
const int snake_size = 20;
const int food_size = 20;
const int font_size = 256;
const std::string font_path = "/home/daniel/Documents/Sssnake/src/media/BebasNeue-Regular.ttf";

Snake snake(WINDOW_WIDTH, WINDOW_HEIGHT, snake_size, move_speed);
Food food(WINDOW_WIDTH, WINDOW_HEIGHT, food_size);
Score score(WINDOW_WIDTH, WINDOW_HEIGHT, font_path, font_size);

SDL_Window* window = NULL;
SDL_Surface* screen_surface = NULL;
SDL_Renderer* renderer = NULL; 
SDL_Event e;

bool running;

void setup();
void exit();
void draw();
void input();
void logic();
void poll_events();
int main();

#endif