
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
    {"Reaction Game(1/4):", "Go to next page"},
    {"Easy(2/4):", "One led goes on/off"},
    {"Medium(3/4):", "Med"},
    {"Hard(4/4):", "Harder"},
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

void displayText(int page_num){

    Text page = TextPages[page_num];
    
    clearDisplay();

    setCursor(0,0);

    print_strln(page.title);
    print_str(page.description);
        
    sleepForMs(1);
    Display();

}

static void printText(const char* first_line, const char* second_line){

    clearDisplay();

    setCursor(0,0);

    print_strln(first_line);
    print_str(second_line);
        
    sleepForMs(1);
    Display();
}

void updateInterface(int p1Score, int p2Score, int iteration, int num_rounds){

    int winner = 0;
    if(p1Score > p2Score){

            winner = 1;

            printf("Player 1 wins the game!\n");

    }else{
        winner = 2;

        printf("Player 2 wins the game!\n");
    }

    char first_line[128];
    char second_line[128];
    
    sprintf(first_line, "Player %d wins! ", winner);
    sprintf(second_line, "(%d/%d)", iteration, num_rounds);


    printText(first_line, second_line);

    // // get percentage of points won by each player 
    // double p1Percent = ((double)p1Score/iteration)*100.0;
    // double p2Percent = ((double)p2Score/iteration)*100.0;

    // setRGB((RGB){ p1Percent, p2Percent, 0 });
}
