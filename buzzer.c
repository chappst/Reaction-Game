
#include "PWM.h"

#define BUZZER_PIN "P9.21"
#define BUZZER_PWM PWM_9_21

#define PERIOD_NS 1000000
void initBuzzer(){
    
    initPWM(BUZZER_PIN, BUZZER_PWM, PERIOD_NS, 50);
    setPWM(BUZZER_PWM, PERIOD_NS, 0);
}


void setBuzzer(int duty_cycle){
    setPWM(BUZZER_PWM, PERIOD_NS, duty_cycle);
}

void setFrequency(int freq_khz){

    // setPWM(BUZZER_PWM, , duty_cycle);
}

