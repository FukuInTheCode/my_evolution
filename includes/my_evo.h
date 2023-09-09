#ifndef MY_EVO_H
#define MY_EVO_H

#include "my_neuralnetwork.h"

typedef bool (*selection_func)(void *);
typedef double (*reward_func)(void *);
typedef void (*do_tick)(void *);

typedef struct {
    uint32_t pop_size;
    void *pop;
    uint32_t max_tick_per_gen;
    double mutation_chance;
    size_t agent_struct_size;
    selection_func is_selected;
    do_tick do_tick;
    reward_func get_reward;
} my_evo_t;

#endif