#pragma once

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define PWM_CHANNEL(buffer, chip, pin) sprintf(buffer, "/sys/class/pwm/pwmchip%d/pwm%d", chip, pin)
#define PWM_9_22 "/sys/class/pwm/pwmchip3/pwm0"
#define PWM_9_21 "/sys/class/pwm/pwmchip3/pwm1"
#define PWM_9_14 "/sys/class/pwm/pwmchip5/pwm0"
#define PWM_9_16 "/sys/class/pwm/pwmchip5/pwm1"
#define PERCENT_DUTY_CYCLE_TO_NS(x, period) (int)((x/100.0)*period)
#define NUM_TO_STR(buffer, x) sprintf(buffer, "%d", x)

void initPWM(const char* pinout, const char* channel, int period, int duty_cycle);
void setPWM(const char* channel, int period, int duty_cycle);