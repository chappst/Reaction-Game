#ifndef DIFFICULTY_H
#define DIFFICULTY_H





// static const int ledColour[3] = {RED, GREEN, BLUE};


static void start_game();

static void choose_RGBled(int colour);

static void rand_led_on(int colour);

static void rand_led_off();

int end_game(int difficulty, int winner);

static void difficulty_easy();

static void difficulty_medium();

static void difficulty_hard();

int play_easy();

int choose_difficulty(int difficulty);


#endif