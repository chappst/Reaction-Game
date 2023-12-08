#pragma once


enum{
    START_PAGE,
    EASY_PAGE,
    MEDIUM_PAGE,
    HARD_PAGE,
};

void initInterface();
void clearInterface();
void displayText(int page_num);
void updateInterface(int p1Score, int p2Score, int iteration, int num_rounds);
void displayContinue();

void displayEasy();
void displayMedium();
void displayHard();
