#ifndef _GPIO_H
#define _GPIO_H

void configure_pin_num(char* pin);

void set_pin_in(int pin);

void set_pin_out(int pin);

void gpio_pin_value(int pin, char* value);

#endif