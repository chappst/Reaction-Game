#ifndef COMMON_H
#define COMMON_H

void runCommand(char *command);

void sleepForMs(long long delayInMs);
int write_config(const char* path, const char* config, const char* data); 
int read_config(char* buffer, const char* path, const char* config); 

#endif