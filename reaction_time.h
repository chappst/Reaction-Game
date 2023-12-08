#ifndef REACTION_H
#define REACTION_H
#pragma once

#include "common.h"
#include <pthread.h>
#include <stdbool.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Reaction{
    double player1;
    double player2;
    bool timeout;
}Reaction;




Reaction start_button_timing(int randColor);
#endif 