//Referenced a guide from Brian Fraser
#include "leds.h"
#include "gpio.h"
#include "common.h"
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED_LED_GPIO 49
#define RED_LED_PIN "P9_23"
#define GREEN_LED_GPIO 70
#define GREEN_LED_PIN "P8_45"
#define BLUE_LED_GPIO 61
#define BLUE_LED_PIN "P8_26"
#define DEFAULT_FILE_SIZE 50;

//Initiating pins
void init_leds(){
    configure_pin_num(RED_LED_PIN);
    configure_pin_num(BLUE_LED_PIN);
    configure_pin_num(GREEN_LED_PIN);

    set_pin_out(RED_LED_GPIO);
    set_pin_out(BLUE_LED_GPIO);
    set_pin_out(GREEN_LED_GPIO);

    turn_off_led(RED);
    turn_off_led(BLUE);
    turn_off_led(GREEN);
}

//Returns the pin number depending on the colour that is called
static int choose_led_colour(int colour){
    int pin;
    switch(colour){
        case GREEN:
            pin = GREEN_LED_GPIO;
            break;
        case BLUE:
            pin = BLUE_LED_GPIO;
            break;
        case RED:
            pin = RED_LED_GPIO;
            break;
        default:
            break;
    }
    return pin;
}

// Led on
void turn_on_led(int colour){
    int ledColour = choose_led_colour(colour);
    gpio_pin_value(ledColour, "0"); //Active low pin
}

//Led off
void turn_off_led(int colour){
    int ledColour = choose_led_colour(colour);
    gpio_pin_value(ledColour, "1"); //Active low pin
}
