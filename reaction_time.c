
#include "reaction_time.h"
#include <pthread.h>

typedef struct ButtonArgs{
    const char* button; // filepath to read for button
    pthread_t tid; // filepath to read for button
    double reaction_us; // reaction time of button press

}ButtonArgs;


#define TIMEOUT_S 3

#define PRESSED '1'
#define UNPRESSED '0'

#define NUM_BUTTONS 2
static ButtonArgs buttons[] = {
    {.button=PLAYER_RED_RED}, //player 1
    {.button=PLAYER_GREEN_GREEN} // player 2
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

        if (read_gpio(button->button) == PRESSED || timeout ){
            break;
        }

        sleepForMs(0.001);

        button->reaction_us += 1;
    }
}


Reaction start_button_timing(int randColor){

    switch(randColor){
        case RED:
            buttons[0].button = PLAYER_RED_RED;
            buttons[1].button = PLAYER_GREEN_RED;

            break;
        case GREEN:

            buttons[0].button = PLAYER_RED_GREEN;
            buttons[1].button = PLAYER_GREEN_GREEN;
            break;
        case YELLOW:
            buttons[0].button = PLAYER_RED_YELLOW;
            buttons[1].button = PLAYER_GREEN_YELLOW;
            break;

        default:
            printf("ERROR INVALID COLOR PASSED!!!!\n");
            break;
    }


    printf("%c %c\n", read_gpio(buttons[0].button),read_gpio(buttons[1].button));
    for (int i = 0; i < NUM_BUTTONS; i++){
        while(read_gpio(buttons[i].button) == PRESSED);
    }

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
        // cancel the alarm if the thread finishes
        alarm(0);
        printf("p%d: %.2f\n", i+1, buttons[i].reaction_us);
    }
    

    return (Reaction){
        .player1 = buttons[0].reaction_us,
        .player2 =buttons[1].reaction_us,
        .timeout = timeout,
    };
}