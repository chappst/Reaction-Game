#include "difficulty.h"
#include "common.h"
#include "interface.h"
#include "reaction_time.h"
#include "joystickSel.h"
#include "RGB.h"
#include "buzzer.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "update_scores.h"
#include "led_matrix.h"

#define NUM_ROUNDS 5

static const RGB rgbColour[] = {
    cRED,
    cGREEN,
    cBLUE
};

static void start_game(){
    // initLedMatrix();
    // initLedMatrix2();
    // initBuzzer();
    setBuzzer(30);
    sleepForMs(500);
    setBuzzer(0);
    //Could Light up RGB LED too
    setRGB(cOFF);
    srand(0);

    for(int i = 3; i > 0; i--){
        displayText(i);
        updateScores(i, i);
        sleepForMs(1000);
    }
    
    clearMatrix();
    clearMatrix2();

}


static void end_game(int difficulty){
    //Buzzer goes off again
    //light led of winner
    //display continue screen():
    if(JoystickDirection() == 3){
        choose_difficulty(difficulty);
    }else{
        // Go back to main screen
        // DISPLAY(main_menu)
    }
}

void play_easy(){

    start_game();

    int p1Score = 0;
    int p2Score = 0;

    for(int i = 1; i < NUM_ROUNDS+1; i++){
        setRGB(cRED);
        Reaction reaction = start_button_timing();

        if(reaction.timeout){
            i--;
            continue;
        }

        if (reaction.player1 < reaction.player2){
            p1Score++;
            printf("Player 1 wins! Score: %d\n", p1Score);
        }else{
            p2Score++;
            printf("Player 2 wins! Score: %d\n", p2Score);
        }
        setRGB(cOFF);
        updateScores(p1Score, p2Score);
        updateInterface(p1Score, p2Score, i, NUM_ROUNDS);
        sleepForMs(2000);
    }
    
    updateInterface(p1Score, p2Score, NUM_ROUNDS , NUM_ROUNDS);
    // end_game(EASY);

}

// void waitForButton(){
//     While(!buttonIsPressed() || //time runs out){
//         //Do nothing
//     }

// }

static void play_medium(){
    start_game();

    //Medium difficulty algorithm
    int randCol = rand() % 3; //Randomly choose colour

    setRGB(rgbColour[randCol]);

    // Start_button_timing(randCol);


    end_game(MEDIUM);

}

static void play_hard(){
    start_game();

    //Hard difficulty algorithm
    int randCol = rand() % 4; //Randomly choose colour

    // light_led(colour[randCol])
 

    end_game(HARD);


}

void choose_difficulty(int difficulty){

    switch(difficulty){
        case EASY:
            play_easy();
        case MEDIUM:
            play_medium();
        case HARD:
            play_hard();
        default:
            play_easy();
    }
}