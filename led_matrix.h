#ifndef LED_MATRIX_H
#define LED_MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <stdbool.h>
#include <time.h>

#define I2CDRV_LINUX_BUS1 "/dev/i2c-1"
#define I2CDRV_LINUX_BUS2 "/dev/i2c-2"
#define REG_ADDR 0x00
#define NUM_BYTES 16
#define BUS_ADDR 0x70
#define MATRIX_LENGTH 8

void initLedMatrix();
void initLedMatrix2();
void displayInteger(int value);
void displayInteger2(int value);
void displayDouble(double value);
void displayDouble2(double value);
void runCommand(char *command);
void sleepForMs(long long delayInMs);

//extern int i2cFileDesc;

#endif // LED_MATRIX_H
