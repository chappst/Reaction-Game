#include "leds.h"
#include "gpio.h"
#include "common.h"

#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>


// GPIO pin numbers for LEDs and the USER button on BeagleBone Green
#define LEDRED_TRIGGER_FILE "/sys/class/gpio/gpio49" //P9_23
#define LEDGREEN_TRIGGER_FILE "/sys/class/gpio/gpio50" //P9_14
#define LEDRED_GPIO_PIN 49
#define LEDRED_PIN_NUM "P9_23"
#define LEDGREEN_GPIO_PIN 70
#define LEDGREEN_PIN_NUM "P8_45"
#define BUTTONRED_GPIO_PIN 65
#define BUTTONGREEN_GPIO_PIN 27

// init() must be called before any other functions
void LED_init(void){
    GPIO_configPin(LEDGREEN_PIN_NUM);
    GPIO_setForOutput(LEDGREEN_GPIO_PIN);
    LED_turnOff('g');

    GPIO_configPin(LEDRED_PIN_NUM);
    GPIO_setForOutput(LEDRED_GPIO_PIN);
    LED_turnOff('r');
    
    return;
}


// Return the Pin name of the specified LED
static int selectPin(char colour, bool light_state){
    int pin;

    if (colour == 'g'){
        /*Turn GREEN_LED on*/
        pin = LEDGREEN_GPIO_PIN;
    }
    else if(colour == 'r'){
        /*Turn RED_LED on*/
        pin = LEDRED_GPIO_PIN;
    }

    return pin;
}

// Turns on the LED
void LED_turnOn(char colour)
{
    GPIO_setValue(selectPin(colour, true), "0");
}

// Turns off the LED
void LED_turnOff(char colour){
    GPIO_setValue(selectPin(colour, false), "1");
}