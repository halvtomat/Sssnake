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

    if(TTF_Init() < 0){
        std::cout << "SDL_ttf could not be initialized! SDL_ttf Error: " << SDL_GetError() << "\n";
        running = false;
    }    
    score_font = TTF_OpenFont("/home/daniel/Documents/Sssnake/src/media/BebasNeue-Regular.ttf", font_size);
    if(score_font == NULL){
        std::cout << "TTF_OpenFont could not load font! TTF_Error: " << TTF_GetError() << "\n";
        running = false;
    }
}

void exit(){
    snake.~Snake();
    food.~Food();
    TTF_Quit();
    SDL_Quit();
}

void draw(){
    //Clear the screen
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(renderer);

    //Draw snake and food
    snake.draw(renderer);
    food.draw(renderer);

    //Draw score
    SDL_Color black = {0, 0, 0};
    std::string score_string = std::to_string(snake.get_length());
    SDL_Surface* score_surface = TTF_RenderText_Solid(score_font, score_string.c_str(), black);
    SDL_Texture* score_texture = SDL_CreateTextureFromSurface(renderer, score_surface);
    SDL_Rect score_rect = {WINDOW_WIDTH-40, 40, 40, 40};

    SDL_RenderCopy(renderer, score_texture, NULL, &score_rect);

    SDL_FreeSurface(score_surface);
    SDL_DestroyTexture(score_texture);

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
    exit();
    return 0;
}