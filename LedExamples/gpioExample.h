#ifndef _GPIO_H
#define _GPIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "helper.h"

// Config pin for GPIO
void GPIO_configPin(char* pinNum);

// Configure pin for output
void GPIO_setForOutput(int gpioNum);

// Configure pin for input
void GPIO_setForInput(int gpioNum);

// Set pin value
void GPIO_setValue(int gpioNum, char* value);

// Get pin value
int GPIO_getValue(int gpioNum);

#endif