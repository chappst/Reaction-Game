#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>

// #define EASY 1U
// #define MEDIUM 2U
// #define HARD 3U

// #define RED 1U
// #define GREEN 2U
// #define BLUE 3U

#define PLAYER_RED_RED "/sys/class/gpio/gpio65"
#define PLAYER_RED_YELLOW "/sys/class/gpio/gpio26"
#define PLAYER_RED_GREEN "/sys/class/gpio/gpio44"

#define PLAYER_GREEN_RED "/sys/class/gpio/gpio46"
#define PLAYER_GREEN_YELLOW "/sys/class/gpio/gpio47"
#define PLAYER_GREEN_GREEN "/sys/class/gpio/gpio27"

enum{
    EASY =1,
    MEDIUM,
    HARD,
};

enum{
    RED,
    GREEN,
    YELLOW, 
};

void runCommand(char *command);

void sleepForMs(long long delayInMs);
int write_config(const char* path, const char* config, const char* data); 
int read_config(char* buffer, const char* path, const char* config); 

char read_gpio(const char* gpio);

#endif