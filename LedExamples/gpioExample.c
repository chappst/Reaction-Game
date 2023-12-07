#include "gpio.h"

// Config pin for GPIO
void GPIO_configPin(char* pinNum){
    char command[35];
    snprintf(command, 35, "config-pin %s gpio", pinNum);
    Helper_runCommand(command);
    return;
}

// Configure pin for output
void GPIO_setForOutput(int gpioNum){
    char file[35]; 
    snprintf(file, 35, "/sys/class/gpio/gpio%d/direction", gpioNum);
    Helper_writeToFile(file, "out");
    return;
}

// Configure pin for input
void GPIO_setForInput(int gpioNum){
    char file[35]; 
    snprintf(file, 35, "/sys/class/gpio/gpio%d/direction", gpioNum);
    Helper_writeToFile(file, "in");
    return;
}

// Set pin value
void GPIO_setValue(int gpioNum, char* value){
    char file[35]; 
    snprintf(file, 35, "/sys/class/gpio/gpio%d/value", gpioNum);
    Helper_writeToFile(file, value);
    return;
}

// Get pin value
int GPIO_getValue(int gpioNum){
    char file[35]; 
    snprintf(file, 35, "/sys/class/gpio/gpio%d/value", gpioNum);
    return Helper_readFromFile(file);
}