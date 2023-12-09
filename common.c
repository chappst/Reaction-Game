//Referenced a guide from Brian Fraser
#include "common.h"
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

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

int write_config(const char* path, const char* config, const char* data) {

	char fpath[1024];
	sprintf(fpath, "%s/%s", path, config);

	FILE* fp = fopen(fpath, "w");
	 
	if (fp == NULL) {
		printf("ERROR OPENING trying to write %s. errno: %d\n", path, errno);
		exit(1);
	}

	int n = fputs(data, fp);

	if (n <= 0) {
		printf("ERROR WRITING DATA\n");
		exit(1);
	}

	return fclose(fp);
}

int read_config(char* buffer, const char* path, const char* config) {
	
	char fpath[1024];
	sprintf(fpath, "%s/%s", path, config);

	FILE* fp = fopen(fpath, "r");
	 
	if (fp == NULL) {
		printf("ERROR OPENING trying to read %s.\n", path);
		exit(1);
	}

	fgets(buffer, 512, fp);

	return fclose(fp);
}

char read_gpio(const char* gpio) {
	char value[16];
	read_config(value, gpio, "value");
	return value[0]; // gpio is always one character
}