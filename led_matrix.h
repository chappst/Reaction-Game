#ifndef LED_MATRIX_H
#define LED_MATRIX_H
//Referenced a guide from Brian Fraser

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
void clearMatrix();
void clearMatrix2();
void displayInteger(int value);
void displayInteger2(int value);
void displayface(const char *face);
void displayface2(const char *face);

#endif
