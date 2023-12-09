#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

// external library: https://github.com/deeplyembeddedWP/SSD1306-OLED-display-driver-for-BeagleBone
#include "lib/I2C.h"
#include "lib/SSD1306_OLED.h"

typedef struct Text{
    const char* title;
    const char* description;
}Text;

const static Text TextPages[] = {
    {"Reaction Game!", "Next (1/4)"},
    {"Easy(2/4):", "One led goes on/off"},
    {"Medium(3/4):", "Med"},
    {"Hard(4/4):", "Harder"}, // add more pages here...
};


void initInterface();
void displayText(int page_num);

void sleepForMs(long long delayInMs);

int main(){

    /*
        You may add more complex conditions such as
        reading a joystick to determine whether to increment or decrement
        the page number. Here, we simply increment through all the pages.
    */
    for (int i = 0; i < sizeof(TextPages)/sizeof(Text); i++){

        displayText(i);

        sleepForMs(1000);
    }

    return 0;
}

void initInterface(){
    
    /* Initialize I2C bus and connect to the I2C Device */

    if(init_i2c_dev(I2C_DEV2_PATH, SSD1306_OLED_ADDR) == 0)
    {
        printf("(Main)i2c-2: Bus Connected to SSD1306\r\n");
    }
    else {
        printf("(Main)i2c-2: OOPS! Something Went Wrong\r\n");
        exit(1);
    }

    display_Init_seq();
    
    /* Clear display */
    clearDisplay();

    setTextSize(2);
    setTextColor(WHITE);

}

void displayText(int page_num){

    Text page = TextPages[page_num];
    
    clearDisplay();

    setCursor(0,0);

    print_strln(page.title);
    print_str(page.description);
        
    sleepForMs(1);
    Display();

}

void sleepForMs(long long delayInMs) {
    const long long NS_PER_MS = 1000 * 1000;
    const long long NS_PER_SECOND = 1000000000;
    long long delayNs = delayInMs * NS_PER_MS;
    int seconds = delayNs / NS_PER_SECOND;
    int nanoseconds = delayNs % NS_PER_SECOND;
    struct timespec reqDelay = {seconds, nanoseconds};
    nanosleep(&reqDelay, (struct timespec *)NULL);
}