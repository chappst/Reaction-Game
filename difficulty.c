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

static const RGB rgbColour[] = {
    cRED,
    cGREEN,
    cBLUE
};

static void start_game(){
    // setBuzzer(50);
    //Could Light up RGB LED too
    setRGB(cOFF);
    srand(0);
    sleepForMs(2000);

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

    for(int i = 0; i <= 3; i++){
        setRGB(cRED);
        Reaction reaction = start_button_timing();
        if (reaction.player1 < reaction.player2){
            p1Score++;
            printf("Player 1 wins! Score: %d\n", p1Score);
        }else{
            p2Score++;
            printf("Player 2 wins! Score: %d\n", p2Score);
        }
        setRGB(cOFF);
        // updateInterface(p1Score, p2Score, i);
        sleepForMs(2000);
    }
    
    if(p1Score > p2Score){
        printf("Player 1 wins the game!\n");
    }else{
        printf("Player 2 wins the game!\n");
    }

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