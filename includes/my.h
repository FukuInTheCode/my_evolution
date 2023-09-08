#pragma once
#define MYH

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "my_evo.h"

#define CELL_DECLA(nvar) my_cell_t nvar = {.brain = {.size = 0, .name = "brain"}}

typedef struct {
    double x;
    double y;
    my_nn_t brain;
} my_cell_t;

