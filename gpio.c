//Referenced a guide from Brian Fraser
#include "gpio.h"
#include "common.h"
#include "leds.h"

#define RED_LED_GPIO 49
#define RED_LED_PIN "P9_23"
#define GREEN_LED_GPIO 70
#define GREEN_LED_PIN "P8_45"
#define BLUE_LED_GPIO 61
#define BLUE_LED_PIN "P8_26"
#define DEFAULT_FILE_SIZE 100

//Configures the pin for led
void configure_pin_num(char* pin){
    char file_path[DEFAULT_FILE_SIZE];
    snprintf(file_path, sizeof(file_path), "config-pin %s gpio", pin);
    runCommand(file_path); 
}

//Set pin to read because active low
void set_pin_in(int pin){
    char file_path[DEFAULT_FILE_SIZE]; 
    snprintf(file_path, sizeof(file_path), "/sys/class/gpio/gpio%d", pin);
    write_config(file_path, "direction", "in");
}

//Set pin to write because of active low
void set_pin_out(int pin){
    char file_path[DEFAULT_FILE_SIZE]; 
    snprintf(file_path, sizeof(file_path), "/sys/class/gpio/gpio%d", pin);
    write_config(file_path, "direction", "out");
}


//Write to the value of the specified gpio pin
void gpio_pin_value(int pin, char* value){
    char file_path[DEFAULT_FILE_SIZE]; 
    snprintf(file_path, sizeof(file_path), "/sys/class/gpio/gpio%d", pin);
    write_config(file_path, "value", value);
}
