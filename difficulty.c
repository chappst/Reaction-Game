#include "difficulty.h"
#include "common.h"
#include "interface.h"
#include "reaction_time.h"
#include "joystickSel.h"
#include "RGB.h"

static void start_game(){
    //Call buzzer for start of game 
    //Could Light up RGB LED too
    sleepForMs(3000);

}

static void end_game(difficulty){
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

static void play_easy(){

    start_game();

    // LED_light(LED);
    start_button_timing();
    end_game(EASY);

}

// void waitForButton(){
//     While(!buttonIsPressed() || //time runs out){
//         //Do nothing
//     }

// }

static void play_medium(){
    start_game();

    //Medium difficulty algorithm
    int randCol = rand() % 4; //Randomly choose colour
    setRGB(colour[randCol][0], colour[randCol][1], colour[randCol][2]);

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