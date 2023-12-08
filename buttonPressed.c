#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#define RED_BUTTON "/sys/class/gpio/gpio65"
#define GREEN_BUTTON "/sys/class/gpio/gpio27"

static bool redButtonClicked = false;
static bool greenButtonClicked = false;

static bool isDoneRunning = false;

static void sleepForMs(long long delayInMs)
{
    const long long NS_PER_MS = 1000 * 1000;
    const long long NS_PER_SECOND = 1000000000;
    long long delayNs = delayInMs * NS_PER_MS;
    int seconds = delayNs / NS_PER_SECOND;
    int nanoseconds = delayNs % NS_PER_SECOND;
    struct timespec reqDelay = {seconds, nanoseconds};
    nanosleep(&reqDelay, (struct timespec *) NULL);
}
   

static bool isClicked(char *fileName){
    if(readButtonValue(fileName) == '1'){
        return true;
    }
    else{
        return false;
    }
}

static void redButtonReader(){
    while(!isDoneRunning){
        if(isClicked(RED_BUTTON)){
            if(!redButtonClicked){
                redButtonClicked = true;
            }
        }
        else{
            redButtonClicked = false;
        }
        
        sleepForMs(10);
    }
    return NULL;
}

static void greenButtonReader(){
    while(!isDoneRunning){
        if(isClicked(GREEN_BUTTON)){
            if(!greenButtonClicked){
                greenButtonClicked = true;
            }
        }
        else{
            greenButtonClicked = false;
        }
        
        sleepForMs(10);
    }
    return NULL;
}



