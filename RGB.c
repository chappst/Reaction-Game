
#include "RGB.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "PWM.h"

#define RED_PWM PWM_9_22
#define GREEN_PWM PWM_9_14
#define BLUE_PWM PWM_9_16

#define RED_PIN "P9.22"
#define GREEN_PIN "P9.14"
#define BLUE_PIN "P9.16"


#define PERIOD_NS 1000000
// pwmchannel 2 -> 1A or 1B
// pwmchannel 0 -> 2A or 2B (22j)
// P9.22 config-pin channel3 pwm0
// P9.14 config-pin channel5 pwm0
// P9.16 config-pin channel5 pwm1

void initRGB(){
    
    initPWM(RED_PIN, RED_PWM, PERIOD_NS, 50);
    initPWM(GREEN_PIN, GREEN_PWM, PERIOD_NS, 50);
    initPWM(BLUE_PIN, BLUE_PWM, PERIOD_NS, 50);
}


void setRGB(RGB rgb){

    setPWM(RED_PWM, PERIOD_NS, rgb.red);
    setPWM(GREEN_PWM, PERIOD_NS, rgb.green);
    setPWM(BLUE_PWM, PERIOD_NS, rgb.blue);
}


