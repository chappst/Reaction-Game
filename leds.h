#ifndef LEDS_H
#define LEDS_H

#include <stdbool.h>

void init_leds();

static int choose_led_colour(int colour);

void turn_on_led(int colour);

void turn_off_led(int colour);


#endif 
