#ifndef MY_EVO_H
#define MY_EVO_H

#include "my_neuralnetwork.h"
#include "SFML/Graphics.h"

typedef void (*draw_func)(sfRenderWindow *, void *);

typedef struct {
    size_t pop_size;
    void *pop;
    uint32_t max_tick_per_gen;
    double mutation_chance;
    double mutation_range;
    size_t agent_struct_size;
    uint32_t do_per_n_gen;
    draw_func agent_draw;
} my_evo_t;

void my_evo_viz(my_evo_t *evo, sfVideoMode mode);
uint32_t my_evo_do_tick(my_evo_t *evo, uint32_t tick,\
                my_matrix_t *selected, my_matrix_t *unselected);
uint32_t my_evo_do_selection(my_evo_t *evo, my_matrix_t *selected,\
                                            my_matrix_t *unselected);
void my_evo_duplica(my_evo_t *evo, my_matrix_t *selected, \
                                        my_matrix_t *unselected, uint32_t i_selected);
void my_evo_create(my_evo_t *evo);

#endif