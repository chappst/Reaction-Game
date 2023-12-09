#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "lib/I2C.h"
#include "common.h"
#include "lib/SSD1306_OLED.h"
#include "RGB.h"
#include "PWM.h"
#include "difficulty.h"
#include "led_matrix.h"
#include "update_scores.h"
#include "interface.h"
#include "buzzer.h"
#include "difficulty.h"
#include "reaction_time.h"
#include "leds.h"
#include "joystickSel.h"

void init_everything(){
    init_leds();
    initLedMatrix();
    initLedMatrix2();
    initBuzzer();
    initInterface();
    initRGB();
    clearMatrix();
    clearMatrix2();
}

int main(){  
    
    //Initializing everything
    init_everything();

    while(1){

        playTune();
        clearMatrix();
        clearMatrix2();

        int difficulty = JoystickChoice();

        int winner = choose_difficulty(difficulty);
        
        end_game(difficulty, winner);
    }
    


    
    

    

}
