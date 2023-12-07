#include "led_matrix.h"
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#define DEC 0b00001000
#define NONE 0x00

// Define digit patterns
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

static unsigned char *digits[] = {zero, one, two, three, four, five, six, seven, eight, nine};

//run linux command within C
void runCommand(char *command){
    int exitCode = system(command);
    if (exitCode != 0){
        perror("Unable to execute command:");
        printf(" command: %s\n", command);
        printf(" exitcode: %d\n", exitCode);
        exit(1);
    }
}

//Given functions for delay
void sleepForMs(long long delayInMs)
{
    const long long NS_PER_MS = 1000 * 1000;
    const long long NS_PER_SECOND = 1000000000;
    long long delayNs = delayInMs * NS_PER_MS;
    int seconds = delayNs / NS_PER_SECOND;
    int nanoseconds = delayNs % NS_PER_SECOND;
    struct timespec reqDelay = {seconds, nanoseconds};
    nanosleep(&reqDelay, (struct timespec *)NULL);
}

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
    runCommand("i2cset -y 1 0x70 0x21 0x00");
    runCommand("i2cset -y 1 0x70 0x81 0x00");
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

void displayDouble(double value)
{
    int i2cFileDesc = initI2CBus(I2CDRV_LINUX_BUS1, BUS_ADDR);
    unsigned char displayValue[8];
    unsigned char *onesBinary;
    unsigned char *tenthsBinary;

    //set to 9.9 if value higher than 9.9
    if(value > 9.9){
        onesBinary =getBinary(9);
        tenthsBinary = getBinary(9);
    }else if(value < 0.0){
        onesBinary = getBinary(0);
        tenthsBinary = getBinary(0);
    }else{
        //multiply by 10 to more easily extract digits
        int valueAsInt = value*10;
        int onesDigit = (valueAsInt/10)%10;
        int tenthsDigit = valueAsInt %10;
        onesBinary = getBinary(onesDigit);
        tenthsBinary = getBinary(tenthsDigit);
    }

    for(int i = 0; i < MATRIX_LENGTH; i++){
        //concat the tens digit and shifted ones digit together 
        unsigned char shifted = (onesBinary[i]<<4) | tenthsBinary[i];
        displayValue[i] = shifted;
    }
    //Decimal Display
    //runCommand("i2cset -y 1 0x70 0x00 0x55");
    displayValue[7] = DEC;
    writeI2CBytes(i2cFileDesc, REG_ADDR, displayValue, NUM_BYTES);
    
}

void displayDouble2(double value)
{
    int i2cFileDesc = initI2CBus(I2CDRV_LINUX_BUS2, BUS_ADDR);
    unsigned char displayValue[8];
    unsigned char *onesBinary;
    unsigned char *tenthsBinary;

    //set to 9.9 if value higher than 9.9
    if(value > 9.9){
        onesBinary =getBinary(9);
        tenthsBinary = getBinary(9);
    }else if(value < 0.0){
        onesBinary = getBinary(0);
        tenthsBinary = getBinary(0);
    }else{
        //multiply by 10 to more easily extract digits
        int valueAsInt = value*10;
        int onesDigit = (valueAsInt/10)%10;
        int tenthsDigit = valueAsInt %10;
        onesBinary = getBinary(onesDigit);
        tenthsBinary = getBinary(tenthsDigit);
    }

    for(int i = 0; i < MATRIX_LENGTH; i++){
        //concat the tens digit and shifted ones digit together 
        unsigned char shifted = (onesBinary[i]<<4) | tenthsBinary[i];
        displayValue[i] = shifted;
    }
    //Decimal Display
    //runCommand("i2cset -y 1 0x70 0x00 0x55");
    displayValue[7] = DEC;
    writeI2CBytes(i2cFileDesc, REG_ADDR, displayValue, NUM_BYTES);
    
}
