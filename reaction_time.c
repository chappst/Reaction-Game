
#include "reaction_time.h"
#include "common.h"
#include <pthread.h>
#include <stdbool.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct ButtonArgs{
    const char* button; // filepath to read for button
    pthread_t tid; // filepath to read for button
    double reaction_us; // reaction time of button press

}ButtonArgs;

#define BUTTON1_PATH "/sys/class/gpio/gpio66"
#define BUTTON2_PATH "/sys/class/gpio/gpio67"
#define TIMEOUT_S 5

#define NUM_BUTTONS 2
static ButtonArgs buttons[] = {
    {.button=BUTTON1_PATH},
    {.button=BUTTON2_PATH}
};

static bool timeout = false;

static void sig_handler(int signo)
{
    timeout = true;
}

void* thread_check_button(void* args){


    ButtonArgs* button = (ButtonArgs*) args;

    // possible infinite loop if no one presses the button...
    // either one of the thre
    while(1){

        if (read_gpio(button->button) == '1' || timeout ){
            break;
        }

        sleepForMs(0.001);

        button->reaction_us += 1;
    }
}


Reaction start_button_timing(){


    for (int i = 0; i < NUM_BUTTONS; i++){
        buttons[i].reaction_us = 0;
        pthread_create(&buttons[i].tid, NULL, thread_check_button, (void*) &buttons[i]);
    }

    /* start timer if reaction is too*/
    timeout = false;
    signal(SIGALRM, sig_handler);
    alarm(TIMEOUT_S);
    
    for (int i = 0; i < NUM_BUTTONS; i++){
        pthread_join(buttons[i].tid, NULL);
        printf("%.2f\n", buttons[i].reaction_us);
    }
    

    return (Reaction){
        .player1 = buttons[0].reaction_us,
        .player2 =buttons[1].reaction_us,
    };
}