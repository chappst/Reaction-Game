#ifndef DIFFICULTY_H
#define DIFFICULTY_H





// static const int ledColour[3] = {RED, GREEN, BLUE};


static void start_game();

int end_game(int difficulty, int winner);

static void difficulty_easy();

static void difficulty_medium();

static void difficulty_hard();

int play_easy();

int choose_difficulty(int difficulty);


#endif