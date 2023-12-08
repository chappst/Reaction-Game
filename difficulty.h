#ifndef DIFFICULTY_H
#define DIFFICULTY_H

enum game_difficulty{
    EASY,
    MEDIUM,
    HARD,
};

enum ledColours{
    RED,
    GREEN,
    BLUE, 
};



// static const int ledColour[3] = {RED, GREEN, BLUE};


static void start_game();

static void end_game(int);

static void difficulty_easy();

static void difficulty_medium();

static void difficulty_hard();

void play_easy();

void choose_difficulty(int difficulty);


#endif