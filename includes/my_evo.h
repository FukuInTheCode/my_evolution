#ifndef MY_EVO_H
#define MY_EVO_H

#include "my_neuralnetwork.h"
#include "SFML/Graphics.h"

typedef bool (*selection_func)(void *);
typedef double (*reward_func)(void *);
typedef void (*do_update)(void *, uint32_t);
typedef void (*show_func)(sfRenderWindow *, void *, sfVector2f);

typedef struct {
    size_t pop_size;
    void *pop;
    uint32_t max_tick_per_gen;
    double mutation_chance;
    double mutation_range;
    size_t agent_struct_size;
    selection_func is_selected;
    do_update update;
    reward_func get_reward;
    show_func show;
} my_evo_t;

void my_evo_viz(my_evo_t *evo, sfVideoMode mode);

#endif