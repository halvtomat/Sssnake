#include "score.h"

Score::Score(std::string font_path){

}

Score::~Score(){

}

void Score::draw(SDL_Renderer* renderer){

}

void Score::set(int x){
    score = x;
}

int Score::get(){
    return score;
}