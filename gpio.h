#ifndef _GPIO_H
#define _GPIO_H


// Config pin for GPIO
void GPIO_configPin(char* PIN);

// Configure pin for output
void GPIO_setForOutput(int GPIO);

// Configure pin for input
void GPIO_setForInput(int GPIO);

// Set pin value
void GPIO_setValue(int GPIO, char* value);

#endif