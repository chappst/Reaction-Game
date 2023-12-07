#include "led.h"


// init() must be called before any other functions
void LED_init(void){
    GPIO_configPin(GREEN_LED_PIN_NUM);
    GPIO_setForOutput(GREEN_LED_GPIO_NUM);
    LED_turnOn('g');

    GPIO_configPin(WHITE_LED_PIN_NUM);
    GPIO_setForOutput(WHITE_LED_GPIO_NUM);
    LED_turnOff('w');

    GPIO_configPin(RED_LED_PIN_NUM);
    GPIO_setForOutput(RED_LED_GPIO_NUM);
    LED_turnOff('r');

    return;
}


// Return the Pin name of the specified LED
static int selectPin(char colour, bool light_state){
    int pin;

    if (colour == 'g'){
        /*Turn GREEN_LED on*/
        pin = GREEN_LED_GPIO_NUM;
    }
    else if(colour == 'r'){
        /*Turn RED_LED on*/
        pin = RED_LED_GPIO_NUM;
    }
    else if(colour == 'w'){
        /*Turn WHITE_LED on*/
        pin = WHITE_LED_GPIO_NUM;
    }

    return pin;
}

// Turns on the LED
void LED_turnOn(char colour)
{
    GPIO_setValue(selectPin(colour, true), "1");
}

// Turns off the LED
void LED_turnOff(char colour){
    GPIO_setValue(selectPin(colour, false), "0");
}

// Turn on heartbeat flash
void LED_heartbeat(char colour)
{
    // on for 0.5 sec
    LED_turnOn(colour);
    Helper_sleepForMs(500);

    // off for 0.5 sec
    LED_turnOff(colour);
    Helper_sleepForMs(500);

    // on for 0.5 sec
    LED_turnOn(colour);
    Helper_sleepForMs(500);

    // off for 1.5 sec
    LED_turnOff(colour);
    Helper_sleepForMs(500);
}

/********** TEST **********/
// int main(){
//     Helper_sleepForMs(3000);
//     printf("TEST\n");

//     LED_init();
//     LED_turnOn('g');
//     Helper_sleepForMs(1000);
//     LED_turnOn('w');
//     Helper_sleepForMs(1000);
//     LED_turnOn('r');
//     Helper_sleepForMs(3000);
//     printf("TEST: this is the green, white, and red LED statuses should be true:%d, %d, %d\n", LED_isOn('g'), LED_isOn('w'), LED_isOn('r'));
//     LED_turnOff('g');
//     LED_turnOff('w');
//     LED_turnOff('r');
//     Helper_sleepForMs(3000);
//     printf("TEST: this is the green, white, and red LED statuses should be false:%d, %d, %d\n", LED_isOn('g'), LED_isOn('w'), LED_isOn('r'));
//     LED_heartbeat('g');
//     Helper_sleepForMs(1000);
//     LED_heartbeat('w');
//     Helper_sleepForMs(1000);
//     LED_heartbeat('r');
//     Helper_sleepForMs(5000);
//     LED_turnOff('g');
//     LED_turnOff('w');
//     LED_turnOff('r');
    
//     return 0;
// }