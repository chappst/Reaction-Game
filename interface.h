#pragma once


enum{
    START_PAGE,
    EASY_PAGE,
    MEDIUM_PAGE,
    HARD_PAGE,
};

void updateInterface(int p1Score, int p2Score, int iteration);

void displayEasy();
void displayMedium();
void displayHard();
