
#include "PWM.h"
#include "common.h"

#define BUZZER_PIN "P9.21"
#define BUZZER_PWM PWM_9_21

#define PERIOD_NS 1000000

#define B_NOTE 0.493883E6
#define C_NOTE 0.26163E6
#define D_NOTE 0.293665E6 //khz converted to period nanoseconds
#define A_NOTE 0.440E6
#define G_NOTE 0.391995E6 
#define G_NOTE 0.391995E6 

void initBuzzer(){
    
    initPWM(BUZZER_PIN, BUZZER_PWM, PERIOD_NS, 50);
    setPWM(BUZZER_PWM, PERIOD_NS, 0);
}


void setBuzzer(int duty_cycle){
    setPWM(BUZZER_PWM, PERIOD_NS, duty_cycle);
}

void playTune(){
    // 1khz -> 1E6


    //21 ms
    for (int i = 0; i <50; i++){
        setPWM(BUZZER_PWM, 0.1E6, 90);
        sleepForMs(6);
        setPWM(BUZZER_PWM, 15E6, 90);

      

    }

    setBuzzer(0);
}