
#include "PWM.h"

#define BUZZER_PIN "P9.22"
#define BUZZER_PWM PWM_9_21

#define PERIOD_NS 1000000
void initBuzzer(){
    
    initPWM(BUZZER_PIN, BUZZER_PWM, PERIOD_NS, 50);
}


void setBuzzer(int freq){
    setPWM(BUZZER_PWM, PERIOD_NS, 99);
}


