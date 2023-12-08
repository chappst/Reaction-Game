#ifndef DIFFICULTY_H
#define DIFFICULTY_H

typedef enum{
    EASY,
    MEDIUM,
    HARD,
};

typedef enum ledColours{
    RED,
    GREEN,
    BLUE, 
};



static const int redRGB[3] = {1,0,0};
static const int greenRGB[3] = {0,1,0};
static const int blueRGB[3] = {0,0,1};

static const int rgbColour[3][3] = {redRGB, greenRGB, blueRGB};

static const int ledColour[3] = {RED, GREEN, BLUE};


static void start_game();

static void end_game(difficulty);

static void difficulty_easy();

static void difficulty_medium();

static void difficulty_hard();

void choose_difficulty(int difficulty);


#endif