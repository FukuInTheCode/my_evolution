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
    sfColor color;
} my_cell_t;

#define CELL_DECLA(nvar) my_cell_t nvar = { \
        .brain = {.size = 0, .name = "brain"}, \
        .atb = {.m = 0, .n = 0, .name = "atb"} };

#define RADIUS 5

#define C_COLOR sfRed

#define SIZE 512.

void my_cell_show(sfRenderWindow *window, void *cell, sfVector2f ratio);
void my_cell_update(void *pop, uint32_t pop_size);
bool my_cell_is_select(void *cell_ptr);
double my_cell_get_reward(void *cell_ptr);
void my_cell_get_array(void *cell_ptr, double **arr);
