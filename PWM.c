#include "PWM.h"
#include "common.h"

void initPWM(const char* pinout, const char* channel, int period, int duty_cycle){

    char buffer[128];
    sprintf(buffer, "config-pin %s pwm", pinout);
    runCommand(buffer);


    setPWM(channel, period, duty_cycle);

    write_config(channel, "enable", "1");
}

void setPWM(const char* channel, int period, int duty_cycle){

    char duty_str[128];
    char period_str[128];

    NUM_TO_STR(period_str, period);
    NUM_TO_STR(duty_str, PERCENT_DUTY_CYCLE_TO_NS(duty_cycle, period));

    write_config(channel, "duty_cycle", duty_str);
    write_config(channel, "period", period_str);
}
