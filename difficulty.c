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
#include "leds.h"

#define NUM_ROUNDS 5

static const RGB rgbColour[] = {
    cRED,
    cGREEN,
    cYELLOW
};

static void choose_RGBled(int colour){

    switch(colour){
        case RED:
            setRGB(cRED);
            break;
        case GREEN:
            setRGB(cGREEN);
            break;
        case YELLOW:
            setRGB(cYELLOW);
            printf("Setting to yellow!\n");
            break;
        default:
            break;
    }
}

static void rand_led_on(int colour){

    switch(colour){
        case 0:
            LED_turnOn('r');
            break;
        case 1:
            LED_turnOn('g');
            break;
        case 2:
            LED_turnOn('y');
            break;
        default:
            break;
    }
}

static void rand_led_off(){

    LED_turnOff('r');
    LED_turnOff('g');
    LED_turnOff('y');
}



static void start_game(){
    // initLedMatrix();
    // initLedMatrix2();
    // initBuzzer();
    clearInterface();
    clearMatrix();
    clearMatrix2();
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
        clearMatrix();
        clearMatrix2();
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
        Reaction reaction = start_button_timing(RED);

        if(reaction.timeout){
            i--;
            setRGB(cOFF);
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
        sleepForMs(rand()%2500);
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

int play_medium(){

    start_game();

    int p1Score = 0;
    int p2Score = 0;

    for(int i = 1; i < NUM_ROUNDS+1; i++){
        int randCol = rand() % 3; //Randomly choose colour
        choose_RGBled(randCol);
        Reaction reaction = start_button_timing(randCol);

        if(reaction.timeout){
            i--;
            setRGB(cOFF);
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

int play_hard(){

    start_game();

    int p1Score = 0;
    int p2Score = 0;

    for(int i = 1; i < NUM_ROUNDS+1; i++){
        int randCol = rand() % 3; //Randomly choose colour
        rand_led_on(randCol);
        Reaction reaction = start_button_timing(randCol);

        if(reaction.timeout){
            i--;
            rand_led_off();
            continue;
        }

        if (reaction.player1 < reaction.player2){
            p1Score++;
            printf("Player 1 wins! Score: %d\n", p1Score);
        }else{
            p2Score++;
            printf("Player 2 wins! Score: %d\n", p2Score);
        }
        rand_led_off();
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

int choose_difficulty(int difficulty){

    
    clearInterface();

    int winner;

    switch(difficulty){
        case EASY:

            winner = play_easy();
            break;
        case MEDIUM:

            winner = play_medium();
            break;
        case HARD:

            winner = play_hard();
            break;
        default:

            winner = play_easy();
            break;
    }
    return winner;
}