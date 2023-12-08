#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <pthread.h>
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

static char readButtonValue(char *fileName){
    char* file = malloc(sizeof(char)*(strlen(fileName)+7));  

    snprintf(file, strlen(fileName)+7, "%s/value", fileName);

    errno = 0;
    FILE *pFile = fopen(file , "r"); 
    
    if (pFile == NULL) {
        printf("ERROR: Unable to open file (%s) for read\n", file);
        perror("ERROR");
        exit(-1); 
    }
    
    const int MAX_LENGTH = 1024; 
    char buff[MAX_LENGTH]; 
    fgets(buff, MAX_LENGTH, pFile);
    
    fclose(pFile);
    free(file);
    file = NULL;
    
    return buff[0];
}

static bool isClicked(char *fileName){
    if(readButtonValue(fileName) == '1'){
        return true;
    }
    else{
        return false;
    }
}

static void *redButtonReader(void *_){
    while(!isDoneRunning){
        if(isClicked(RED_BUTTON)){
            if(!redButtonClicked){
                // Perform action for red button press
                // Example: LEDDisplay_toggleRedMode();
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

static void *greenButtonReader(void *_){
    while(!isDoneRunning){
        if(isClicked(GREEN_BUTTON)){
            if(!greenButtonClicked){
                // Perform action for green button press
                // Example: LEDDisplay_toggleGreenMode();
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


