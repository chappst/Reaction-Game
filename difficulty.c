#include "difficulty.h"

static void play_easy(){}



static void play_medium(){}

static void play_hard(){}

void choose_difficulty(int difficulty){

    switch(difficulty){
        case 1:
            play_easy();
        case 2:
            play_medium();
        case 3:
            play_hard();
        default:
            play_easy();
    }
}