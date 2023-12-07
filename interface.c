
#include "interface.h"
#include "RGB.h"
#include "common.h"
#include <stdlib.h>

#include "lib/I2C.h"
#include "lib/SSD1306_OLED.h"

typedef struct Text{
    const char* title;
    const char* description;
}Text;

const static Text TextPages[] = {
    {"Easy(1/4):", "One led goes on/off"},
    {"Medium(2/4):", "One led goes on/off"},
    {"Hard(3/4):", "One led goes on/off"},
    {"Easy(4/4):", "One led goes on/off"},
};

void initInterface(){
    
    /* Initialize I2C bus and connect to the I2C Device */

    if(init_i2c_dev(I2C_DEV2_PATH, SSD1306_OLED_ADDR) == 0)
    {
        printf("(Main)i2c-2: Bus Connected to SSD1306\r\n");
    }
    else
    {
        printf("(Main)i2c-2: OOPS! Something Went Wrong\r\n");
        exit(1);
    }

    display_Init_seq();
    
    /* Clear display */
    clearDisplay();

    setTextSize(2);
    setTextColor(WHITE);

}

static void displayText(int page_num){

    Text page = TextPages[page_num];
    
    clearDisplay();

    setCursor(0,0);

    print_strln(page.title);
    print_str(page.description);
        
    sleepForMs(1);
    Display();

}

void updateInterface(int p1Score, int p2Score, int iteration){

    // get percentage of points won by each player 
    double p1Percent = ((double)p1Score/iteration)*100.0;
    double p2Percent = ((double)p2Score/iteration)*100.0;

    setRGB(p1Percent, p2Percent, 0);
}
