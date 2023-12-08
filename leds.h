#ifndef LEDS_H
#define LEDS_H

#include <stdbool.h>

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

void LED_init(void);

static int selectPin(char colour, bool isOn);

void LED_turnOn(char colour);

void LED_turnOff(char colour);


#endif /* LED_CONTROL_H */
