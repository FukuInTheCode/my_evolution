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
#include "SFML/Graphics.h"

typedef struct {
    my_nn_t brain;
    my_matrix_t atb;
} my_cell_t;

#define CELL_DECLA(nvar) my_cell_t nvar = { \
        .brain = {.size = 0, .name = "brain"}, \
        .atb = {.m = 0, .n = 0, .name = "atb"} };
