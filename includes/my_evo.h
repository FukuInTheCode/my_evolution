#ifndef MY_EVO_H
#define MY_EVO_H

#include "my_matrix.h"
#include "SFML/Graphics.h"

typedef void (*draw_func)(sfRenderWindow *, void *, void *);
typedef void (*draw_bg_func)(sfRenderWindow *, void *);
typedef uint32_t (*update_func)(void *, void *, uint32_t, void *);
typedef bool (*selection_func)(void *, void *, uint32_t, void *);
typedef double (*reward_func)(void *, void *, uint32_t, void *);
typedef uint32_t (*get_array_func)(void *, double **, void *);
typedef void (*reset_func)(void *, void *, uint32_t, void *);
typedef void (*from_array_func)(void *, double *, void *);
typedef void (*create_func)(void *, void *);
typedef void (*free_func)(void *, void *);
typedef void (*params_func)(void *, uint32_t, void *);

typedef struct {
    uint32_t pop_size;
    void *pop;
    uint32_t selected_size;
    uint32_t max_tick_per_gen;
    double mutation_chance;
    double mutation_range;
    size_t agent_struct_size;
    uint32_t gen_skip;
    void *params;
    draw_func draw_agent;
    draw_bg_func draw_bg;
    update_func update_agent;
    selection_func agent_is_select;
    reward_func get_agent_reward;
    get_array_func get_agent_array;
    reset_func reset_agent;
    from_array_func agent_from_array;
    create_func create_agent;
    free_func free_agent;
    params_func update_params;
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
uint32_t my_evo_algo(my_evo_t *evo, my_matrix_t **s_matrices,\
                            uint32_t tick, uint32_t i_selected);

#endif
