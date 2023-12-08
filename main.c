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



// typedef struct PWM_t{
//     int channel;
//     int pin;
// } PWM_t;

// void checkChannels(){
    
//     PWM_t channels[] = {
//         {0, 0},
//         {1, 0},
//         {2, 0},
//         {3, 0},
//         {3, 1},
//         {5, 0},
//         {5, 1},
//         {7, 0},
//         {7, 1},
//     };


//     for (int i = 0; i < 9; i++){

//         char buffer[128];

//         PWM_CHANNEL(buffer, channels[i].channel, channels[i].pin);
//         // initPWM("P9.21", buffer, 1000000000000, 50);
//         printf("%s\n", buffer);
//         sleepForMs(1500);
//     }

// }

void init_everything(){
    LED_init();
    initLedMatrix();
    initLedMatrix2();
    initBuzzer();
    initInterface();
    initRGB();

}

void checkRGB(){



    sleepForMs(1000);
    printf("Lighting up red\n");
    setRGB((RGB){100,0,0});
    sleepForMs(1000);
     printf("Lighting up green\n");
    setRGB((RGB){0,100,0});
    sleepForMs(1000);
    printf("Lighting up blue\n");
    setRGB((RGB){0,0,100});
    sleepForMs(1000);
    printf("Turning off RGB\n");
    sleepForMs(1000);
}

void test_everything(){

    

    // printf("Displaying text!\n");
    // displayText(1);
    // sleepForMs(2000);
    // setBuzzer(50);
    // printf("Buzz!!!\n");
    // sleepForMs(1000);
    // printf("Buzz off!!!\n");
    // setBuzzer(0);
    // sleepForMs(2000);
    // printf("Checking RGB colors\n");
    // checkRGB();

    // printf("Now counting down on matrices\n");
  

    // JoystickChoice();

    play_easy();

    // clearMatrix();
    // clearMatrix2();

    // LED_turnOn('r');
    // sleepForMs(1000);
    // LED_turnOff('r');

    // LED_turnOn('y');
    // sleepForMs(1000);
    // LED_turnOff('y');

    // LED_turnOn('g');
    // sleepForMs(1000);
    // LED_turnOff('g');
    


}




int main(){

    init_everything();

    test_everything();

    
    

    

}
