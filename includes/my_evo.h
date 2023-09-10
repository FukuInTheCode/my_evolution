#ifndef MY_EVO_H
#define MY_EVO_H

#include "my_neuralnetwork.h"
#include "SFML/Graphics.h"

typedef void (*draw_func)(sfRenderWindow *, void *);
typedef void (*update_func)(void *, uint32_t);
typedef bool (*selection_func)(void *);
typedef double (*reward_func)(void *);
typedef uint32_t (*get_array_func)(void *, double **);
typedef void (*reset_func)(void *, bool);
typedef void (*from_array_func)(void *, double *);
typedef void (*create_func)(void *);
typedef void (*free_func)(void *);

typedef struct {
    size_t pop_size;
    void *pop;
    uint32_t max_tick_per_gen;
    double mutation_chance;
    double mutation_range;
    size_t agent_struct_size;
    uint32_t do_per_n_gen;
    draw_func draw_agent;
    update_func update_agents;
    selection_func agent_is_select;
    reward_func get_agent_reward;
    get_array_func get_agent_array;
    reset_func reset_agent;
    from_array_func agent_from_array;
    create_func create_agent;
    free_func free_agent;
} my_evo_t;

void my_evo_viz(my_evo_t *evo, sfVideoMode mode);
uint32_t my_evo_do_tick(my_evo_t *evo, uint32_t tick,\
                my_matrix_t *selected, my_matrix_t *unselected);
uint32_t my_evo_do_selection(my_evo_t *evo, my_matrix_t *selected,\
                                            my_matrix_t *unselected);
void my_evo_duplica(my_evo_t *evo, my_matrix_t *selected, \
                                        my_matrix_t *unselected, uint32_t i_selected);
void my_evo_create(my_evo_t *evo);
void my_evo_free(my_evo_t *evo);

#endif