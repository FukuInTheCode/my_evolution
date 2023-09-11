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

void my_cell_draw(sfRenderWindow *window, void *cell, void *params);
uint32_t my_cell_update(void *cell_ptr, void *pop, uint32_t pop_sizev, void *);
bool my_cell_is_select(void *cell_ptr, void *pop, uint32_t pop_size, void *params);
double my_cell_get_reward(void *cell_ptr, void *pop, uint32_t pop_size, void *params);
uint32_t my_cell_get_array(void *cell_ptr, double **arr, void *params);
void my_cell_reset(void *cell_ptr, void *pop, uint32_t pop_size, void *params);
void my_cell_from_array(void *cell_ptr, double *arr, void *params);
void my_cell_create(void *cell_ptr, void *params);
void my_cell_free(void *cell_ptr, void *params);
