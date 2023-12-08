#include "gpio.h"
#include "common.h"
#include "leds.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// GPIO pin numbers for LEDs and the USER button on BeagleBone Green
#define LEDRED_TRIGGER_FILE "/sys/class/gpio/gpio49" //P9_23
#define LEDGREEN_TRIGGER_FILE "/sys/class/gpio/gpio50" //P9_14
#define LEDRED_GPIO_PIN 49
#define LEDRED_PIN_NUM "P9_23"
#define LEDGREEN_GPIO_PIN 70
#define LEDGREEN_PIN_NUM "P8_45"
#define LEDYELLOW_GPIO_PIN 61
#define LEDYELLOW_PIN_NUM "P8_26"
#define BUTTONRED_GPIO_PIN 65
#define BUTTONGREEN_GPIO_PIN 27


// Config pin for GPIO
void GPIO_configPin(char* PIN){
    char command[100];
    snprintf(command, sizeof(command), "config-pin %s gpio", PIN);
    runCommand(command);
    return;
}

// Configure pin for output
void GPIO_setForOutput(int GPIO){
    char file[100]; 
    snprintf(file, sizeof(file), "/sys/class/gpio/gpio%d", GPIO);
    write_config(file, "direction", "out");
    return;
}

// Configure pin for input
void GPIO_setForInput(int GPIO){
    char file[100]; 
    snprintf(file, sizeof(file), "/sys/class/gpio/gpio%d", GPIO);
    write_config(file, "direction", "in");
    return;
}

// Set pin value
void GPIO_setValue(int GPIO, char* value){
    char file[100]; 
    snprintf(file, sizeof(file), "/sys/class/gpio/gpio%d", GPIO);
    write_config(file, "value", value);
    return;
}
