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


typedef struct PWM_t{
    int channel;
    int pin;
} PWM_t;

void checkChannels(){
    
    PWM_t channels[] = {
        {0, 0},
        {1, 0},
        {2, 0},
        {3, 0},
        {3, 1},
        {5, 0},
        {5, 1},
        {7, 0},
        {7, 1},
    };


    for (int i = 0; i < 9; i++){

        char buffer[128];

        PWM_CHANNEL(buffer, channels[i].channel, channels[i].pin);
        initPWM("P8.13", buffer, 1000000000000, 50);
        printf("%s\n", buffer);
        sleepForMs(1500);
    }

}




int main(){

    // initRGB();
    // setRGB(0,0,128);
    // for (int i = 0; i< 255; i+=10){

    //     setRGB(0,0,i);
    //     sleepForMs(100);
    // }
    // checkChannels();


    // initRGB();


    initLedMatrix();
    initLedMatrix2();
    initRGB();

   
    // signal(SIGALRM, sig_handler);
    // alarm(1);
    // /* Register the Alarm Handler */
    // // signal(SIGALRM, ALARMhandler);

    // // /* Run SDD1306 Initialization Sequence */



    // setRGB(0, 255, 0);
    // for(int i = 0; i <255; i++){

    //     clearDisplay();
    //     setCursor(0,0);

    //     setRGB(255, i, 255-i);

    //     printNumber(i, DEC);
        
    //     sleepForMs(1);
    //     Display();

    //     sleepForMs(1);
    // }


    // for(int i = 0; i <255; i++){

    //     clearDisplay();
    //     setCursor(0,0);

    //     setRGB(0, i, 255-i);

    //     printNumber(i, DEC);
        
    //     sleepForMs(1);
    //     Display();

    //     sleepForMs(1);
    // }



    // checkChannels();
    // setPWM("period", PERIOD_NS);
    // write_config(PWM_CHANNEL0, "enable", "1");

    
    // for(int i =0; i < 100; i++){


    //     setPWM("duty_cycle", PERCENT_DUTY_CYCLE_TO_NS(i));
    //     sleepForMs(100);

    // }

    

    

}
