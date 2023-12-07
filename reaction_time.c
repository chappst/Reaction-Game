
#include "reaction_time.h"
#include "common.h"
#include <pthread.h>
#include <stdbool.h>
#include <signal.h>
#include <stdlib.h>

typedef struct ButtonArgs{
    const char* button; // filepath to read for button
    double reaction; // reaction time of button press

}ButtonArgs;

#define BUTTON1_PATH ""
#define BUTTON2_PATH ""


// flag to check if either thread finished
// (no critical section because no race condition possible; we just need to finish at some point...)
static bool finished = false;

void* thread_check_button(void* args){


    ButtonArgs button = *(ButtonArgs*) args;

    // possible infinite loop if no one presses the button...
    while(read_gpio("72") != 1){
        button.reaction++;
        sleepForMs(1);
    }

    // whichever button finishes first should signal main thread
    finished = true;
    
}


Reaction start_button_timing(){

    ButtonArgs p1 = {
        .button = BUTTON1_PATH,
    };

    ButtonArgs p2 = {
        .button = BUTTON2_PATH,
    };

    finished = false;

    pthread_t tid2;
    pthread_t tid1;

    pthread_create(&tid1, NULL, thread_check_button, (void*) &p1);
    pthread_create(&tid2, NULL, thread_check_button, (void*) &p2);
    
    while(!finished);
    
    pthread_kill(tid1, SIGKILL);
    pthread_kill(tid2, SIGKILL);

    return (Reaction){
        .player1 = p1.reaction,
        .player2 = p2.reaction,
    };
}