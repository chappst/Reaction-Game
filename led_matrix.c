#include "led_matrix.h"
#include <unistd.h>
#include <time.h>
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include "common.h"
#include <stdint.h>

#define DEC 0b00001000
#define NONE 0x00

// Define digit patterns
static unsigned char off[] = {0b000, 0b000, 0b000, 0b000, 0b000, 0b000, 0b000};
static unsigned char zero[] = {0b111, 0b101, 0b101, 0b101, 0b101, 0b101, 0b111};
static unsigned char one[] = {0b110, 0b010, 0b010, 0b010, 0b010, 0b010, 0b111};
static unsigned char two[] = {0b111, 0b001, 0b001, 0b111, 0b100, 0b100, 0b111};
static unsigned char three[] = {0b111, 0b001, 0b001, 0b111, 0b001, 0b001, 0b111};
static unsigned char four[] = {0b101, 0b101, 0b101, 0b111, 0b001, 0b001, 0b001};
static unsigned char five[] = {0b111, 0b100, 0b100, 0b111, 0b001, 0b001, 0b111};
static unsigned char six[] = {0b111, 0b100, 0b100, 0b111, 0b101, 0b101, 0b111};
static unsigned char seven[] = {0b111, 0b001, 0b001, 0b001, 0b001, 0b001, 0b001};
static unsigned char eight[] = {0b111, 0b101, 0b101, 0b111, 0b101, 0b101, 0b111};
static unsigned char nine[] = {0b111, 0b101, 0b101, 0b111, 0b001, 0b001, 0b001};
//Facial Expression
// static uint8_t smile[8]=   {0x3C,0x42,0xA5,0x81,0xA5,0x99,0x42,0x3C};
// static uint8_t neutral[8]= {0x3C,0x42,0xA5,0x81,0xBD,0x81,0x42,0x3C};
// static uint8_t sad[8]=   {0x3C,0x42,0xA5,0x81,0x99,0xA5,0x42,0x3C};
static unsigned char smile[] = {0x3C,0x42,0xA5,0x81,0xA5,0x99,0x42,0x3C};
static unsigned char sad[] = {0x3C,0x42,0xA5,0x81,0x99,0xA5,0x42,0x3C};

static unsigned char *digits[] = {zero, one, two, three, four, five, six, seven, eight, nine};


void initLedMatrix(){
    runCommand("config-pin P9_18 i2c");
    sleepForMs(500);
    runCommand("config-pin P9_17 i2c");
    sleepForMs(500);
    runCommand("i2cset -y 1 0x70 0x21 0x00");
    runCommand("i2cset -y 1 0x70 0x81 0x00");
}

void initLedMatrix2(){
    runCommand("config-pin P9_20 i2c");
    sleepForMs(500);
    runCommand("config-pin P9_19 i2c");
    sleepForMs(500);
    runCommand("i2cset -y 2 0x70 0x21 0x00");
    runCommand("i2cset -y 2 0x70 0x81 0x00");
}

static void writeI2CBytes(int i2cFileDesc, unsigned char regAddr, unsigned char* data, int numBytes)
{
    unsigned char buff[numBytes+1];
    buff[0] = regAddr;

    int i = numBytes-1; 
    int j = 0;
    while(i>=0){
        if(i%2 == 0){
            buff[i+1] = data[j];
            j++;
        }
        i--;
    }
    int res = write(i2cFileDesc, buff, numBytes + 1);

    if (res != numBytes + 1) {
        perror("Unable to write i2c register");
        exit(-1);
    }
}

static int initI2CBus(char* bus, int address)
{
	int i2cFileDesc = open(bus, O_RDWR);
	if (i2cFileDesc < 0) {
		printf("I2C DRV: Unable to open bus for read/write (%s)\n", bus);
		perror("Error is:");
		exit(-1);
	}

	int result = ioctl(i2cFileDesc, I2C_SLAVE, address);
	if (result < 0) {
		perror("Unable to set I2C device to slave address.");
		exit(-1);
	}
	return i2cFileDesc;
}

unsigned char *getBinary(int digit)
{
    return digits[digit];
}

void clearMatrix(){
    runCommand("i2cset -y 1 0x70 0x02 0x00"); 
    runCommand("i2cset -y 1 0x70 0x04 0x00"); 
    runCommand("i2cset -y 1 0x70 0x06 0x00"); 
    runCommand("i2cset -y 1 0x70 0x08 0x00"); 
    runCommand("i2cset -y 1 0x70 0x0a 0x00"); 
    runCommand("i2cset -y 1 0x70 0x0c 0x00"); 
    runCommand("i2cset -y 1 0x70 0x0e 0x00"); 
}
void clearMatrix2(){

    runCommand("i2cset -y 2 0x70 0x02 0x00"); 
    runCommand("i2cset -y 2 0x70 0x04 0x00"); 
    runCommand("i2cset -y 2 0x70 0x06 0x00"); 
    runCommand("i2cset -y 2 0x70 0x08 0x00"); 
    runCommand("i2cset -y 2 0x70 0x0a 0x00"); 
    runCommand("i2cset -y 2 0x70 0x0c 0x00"); 
    runCommand("i2cset -y 2 0x70 0x0e 0x00"); 
}

void displayInteger(int value)
{
    int i2cFileDesc = initI2CBus(I2CDRV_LINUX_BUS1, BUS_ADDR);
    unsigned char displayValue[8];

    unsigned char *tensBinary;
    unsigned char *onesBinary;
    
    if(value > 99){
        tensBinary = getBinary(9);
        onesBinary = getBinary(9);
    }else if(value < 0){
        tensBinary = getBinary(0);
        onesBinary = getBinary(0);
    }else if(value > 9){ 
        int tensDigit = (value/10)%10;
        int onesDigit = value %10;
        tensBinary = getBinary(tensDigit);
        onesBinary = getBinary(onesDigit);
    }else{//case single digit
        int onesDigit = value %10;
        tensBinary = getBinary(0);
        onesBinary = getBinary(onesDigit);
    }

    for(int i = 0; i < MATRIX_LENGTH; i++){
         //concat the tens digit and shifted ones digit together 
        unsigned char shifted = (tensBinary[i]<<4) | onesBinary[i];
        displayValue[i] = shifted;
    }
    writeI2CBytes(i2cFileDesc, REG_ADDR, displayValue, NUM_BYTES);
    
}

void displayInteger2(int value)
{
    int i2cFileDesc = initI2CBus(I2CDRV_LINUX_BUS2, BUS_ADDR);
    unsigned char displayValue[8];

    unsigned char *tensBinary;
    unsigned char *onesBinary;
    
    if(value > 99){
        tensBinary = getBinary(9);
        onesBinary = getBinary(9);
    }else if(value < 0){
        tensBinary = getBinary(0);
        onesBinary = getBinary(0);
    }else if(value > 9){ 
        int tensDigit = (value/10)%10;
        int onesDigit = value %10;
        tensBinary = getBinary(tensDigit);
        onesBinary = getBinary(onesDigit);
    }else{//case single digit
        int onesDigit = value %10;
        tensBinary = getBinary(0);
        onesBinary = getBinary(onesDigit);
    }

    for(int i = 0; i < MATRIX_LENGTH; i++){
         //concat the tens digit and shifted ones digit together 
        unsigned char shifted = (tensBinary[i]<<4) | onesBinary[i];
        displayValue[i] = shifted;
    }
    writeI2CBytes(i2cFileDesc, REG_ADDR, displayValue, NUM_BYTES);
    
}


void displayface(const char *face) {
    int i2cFileDesc;
    unsigned char displayValue[8];

    if (strcmp(face, "smile") == 0) {
        for(int i = 0; i < MATRIX_LENGTH; i++){
            displayValue[i] = smile[i] >> 1 | (smile[i] << 7);
        }
        i2cFileDesc = initI2CBus(I2CDRV_LINUX_BUS1, BUS_ADDR);
        writeI2CBytes(i2cFileDesc, REG_ADDR, displayValue, NUM_BYTES);
    } else if (strcmp(face, "sad") == 0) {
        for(int i = 0; i < MATRIX_LENGTH; i++){
            displayValue[i] = sad[i] >> 1 | (smile[i] << 7);
        }
        i2cFileDesc = initI2CBus(I2CDRV_LINUX_BUS1, BUS_ADDR);
        writeI2CBytes(i2cFileDesc, REG_ADDR, displayValue, NUM_BYTES);
    }
}


void displayface2(const char *face) {
    int i2cFileDesc;
    unsigned char displayValue[8];

    if (strcmp(face, "smile") == 0) {
        for(int i = 0; i < MATRIX_LENGTH; i++){
            displayValue[i] = smile[i] >> 1 | (smile[i] << 7);
        }
        i2cFileDesc = initI2CBus(I2CDRV_LINUX_BUS2, BUS_ADDR);
        writeI2CBytes(i2cFileDesc, REG_ADDR, displayValue, NUM_BYTES);
    } else if (strcmp(face, "sad") == 0) {
        for(int i = 0; i < MATRIX_LENGTH; i++){
            displayValue[i] = sad[i] >> 1 | (smile[i] << 7);
        }
        i2cFileDesc = initI2CBus(I2CDRV_LINUX_BUS2, BUS_ADDR);
        writeI2CBytes(i2cFileDesc, REG_ADDR, displayValue, NUM_BYTES);
    }
}

