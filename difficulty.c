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
    clearInterface();
    setRGB(cOFF);
    setBuzzer(30);
    sleepForMs(500);
    setBuzzer(0);
    //Could Light up RGB LED too
    setRGB(cOFF);
    srand(0);

    for(int i = 3; i > 0; i--){
        updateScores(i, i);
        sleepForMs(1000);
    }
    
    clearMatrix();
    clearMatrix2();
    sleepForMs(1000);

}


int end_game(int difficulty, int winner){
    //Buzzer goes off again
    setBuzzer(30);
    sleepForMs(500);
    setBuzzer(0);

    clearMatrix();
    clearMatrix2();
    

    //light led of winner
    //display continue screen():
    displayContinue(winner);


    int dir;
    do{
        dir = JoystickDirection();


    }while(dir == 0);

    if(JoystickDirection() == 1){
        clearInterface();
        choose_difficulty(difficulty);
    }else{
        // Go back to main screen

    }
}

int play_easy(){

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
        sleepForMs(rand()%3500);
    }

    // if(p1Score > p1Score){
    //     updateScores();
    // }else{
    //     updateScores();
    // }
    
    updateInterface(p1Score, p2Score, NUM_ROUNDS , NUM_ROUNDS);
    
    return (p1Score > p2Score) ? 1:2; // return who won
    

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


    

}

static void play_hard(){
    start_game();

    //Hard difficulty algorithm
    int randCol = rand() % 4; //Randomly choose colour

    // light_led(colour[randCol])
 

    


}

int choose_difficulty(int difficulty){

    
    clearInterface();

    int winner;

    switch(difficulty){
        case EASY:

            winner = play_easy();
            break;
        case MEDIUM:

            play_medium();
            break;
        case HARD:

            play_hard();
            break;
        default:

            winner = play_easy();
            break;
    }
    return winner;
}