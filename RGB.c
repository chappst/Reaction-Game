
#include "RGB.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define PWM_CHANNEL(buffer, chip, pin) sprintf(buffer, "/sys/class/pwm/pwmchip%d/pwm%d", chip, pin)

#define PWM_9_22 "/sys/class/pwm/pwmchip3/pwm0"
#define PWM_9_14 "/sys/class/pwm/pwmchip5/pwm0"
#define PWM_9_16 "/sys/class/pwm/pwmchip5/pwm1"
#define PERIOD_NS 1000000
#define PERCENT_DUTY_CYCLE_TO_NS(x, period) (int)((x/100.0)*period)
#define NUM_TO_STR(buffer, x) sprintf(buffer, "%d", x)
// pwmchannel 2 -> 1A or 1B
// pwmchannel 0 -> 2A or 2B (22j)
// P9.22 config-pin channel3 pwm0
// P9.14 config-pin channel5 pwm0
// P9.16 config-pin channel5 pwm1

static void setPWM(const char* channel, int period, int duty_cycle);

void initRGB(){
    runCommand("config-pin P9.16 pwm");
    runCommand("config-pin P9.22 pwm");

    runCommand("config-pin P9.14 pwm");

    setPWM(PWM_9_14, PERIOD_NS, 50);
    setPWM(PWM_9_16, PERIOD_NS, 50);
    setPWM(PWM_9_22, PERIOD_NS, 50);

    write_config(PWM_9_14, "enable", "1");
    write_config(PWM_9_16, "enable", "1");
    write_config(PWM_9_22, "enable", "1");
}


void setRGB(int r, int g, int b){

    setPWM(PWM_9_14, PERIOD_NS, r);
    setPWM(PWM_9_16, PERIOD_NS, g);
    setPWM(PWM_9_22, PERIOD_NS, b);
}

static void setPWM(const char* channel, int period, int duty_cycle){

    char duty_str[128];
    char period_str[128];

    NUM_TO_STR(period_str, period);
    NUM_TO_STR(duty_str, PERCENT_DUTY_CYCLE_TO_NS(duty_cycle, period));

    write_config(channel, "duty_cycle", duty_str);
    write_config(channel, "period", period_str);
}
