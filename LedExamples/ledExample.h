#ifndef _LED_H_
#define _LED_H_

#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "helper.h"
#include "gpio.h"

#define GREEN_LED_PIN_NUM "P8_45"
#define GREEN_LED_GPIO_NUM 70
#define WHITE_LED_PIN_NUM "P8_46"
#define WHITE_LED_GPIO_NUM 71
#define RED_LED_PIN_NUM "P8_44"
#define RED_LED_GPIO_NUM 73

// init() must be called before any other functions
void LED_init(void);

// Turns on the LED
void LED_turnOn(char colour);

// Turns off the LED
void LED_turnOff(char colour);

// Turn on heartbeat flash
void LED_heartbeat(char colour);

#endif