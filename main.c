#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include "lib/I2C.h"
#include "common.h"
#include "lib/SSD1306_OLED.h"
#include "RGB.h"
#include "difficulty.h"



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
//         setPWM(buffer, PERIOD_NS, 50);
//         char enable[128];
//         write_config(buffer, "enable", "1");
//         read_config(enable,buffer, "enable");
//         printf("%s: %s\n", buffer, enable);
//         sleepForMs(1500);

//     }

// }


int main(){


    initRGB();

    for(int i = 0; i <100; i++){
        setRGB(100-i, i, 100);
        sleepForMs(100);
    }



    // checkChannels();
    // setPWM("period", PERIOD_NS);
    // write_config(PWM_CHANNEL0, "enable", "1");

    
    // for(int i =0; i < 100; i++){


    //     setPWM("duty_cycle", PERCENT_DUTY_CYCLE_TO_NS(i));
    //     sleepForMs(100);

    // }

    
    // /* Initialize I2C bus and connect to the I2C Device */
    // if(init_i2c_dev(I2C_DEV2_PATH, SSD1306_OLED_ADDR) == 0)
    // {
    //     printf("(Main)i2c-2: Bus Connected to SSD1306\r\n");
    // }
    // else
    // {
    //     printf("(Main)i2c-2: OOPS! Something Went Wrong\r\n");
    //     exit(1);
    // }

    // /* Register the Alarm Handler */
    // // signal(SIGALRM, ALARMhandler);

    // /* Run SDD1306 Initialization Sequence */
    // display_Init_seq();

    // /* Clear display */
    // clearDisplay();

    // unsigned char i = 0;
    // setTextSize(1);
    // setTextColor(WHITE);
    // setCursor(0,0);

    // setTextSize(4);
    // setTextColor(WHITE);
    // setCursor(0,0);
    // print_str("scroll");

    // sleepForMs(1);
    // Display();
    

    

}