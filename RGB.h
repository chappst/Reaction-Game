#ifndef RGB_H
#define RGB_H

#include "common.h"

typedef struct RGB{
    int red;
    int green;
    int blue;

}RGB;

#define cOFF (RGB){0,0,0}
#define cRED (RGB){100,0,0}
#define cGREEN (RGB){0,100,0}
#define cBLUE (RGB){0,0,100}

void initRGB();
void setRGB(RGB rgb);

#endif
