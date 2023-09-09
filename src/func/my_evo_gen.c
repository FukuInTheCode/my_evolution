#include "../../includes/my.h"

uint32_t my_evo_do_tick(my_evo_t *evo, uint32_t tick,\
                my_matrix_t *selected, my_matrix_t *unselected)
{
    uint32_t i_selected;
    if (tick < evo->max_tick_per_gen) {
        my_cell_update(evo->pop, evo->pop_size);
        ++tick;
    } else if (tick == evo->max_tick_per_gen) {
        // selection
        i_selected = my_evo_do_selection(evo, selected, unselected);
        ++tick;
    } else {
        // duplica
        for (uint32_t i = 0; i < evo->pop_size - i_selected; ++i) {
            my_cell_t *cell_child = (my_cell_t *)((char *)(evo->pop) + (int)(unselected.arr[i][0]) * evo->agent_struct_size);
            my_cell_t *cell_parent = (my_cell_t *)((char *)(evo->pop) + (int)(selected.arr[i % i_selected][0]) * evo->agent_struct_size);
            double *arr = malloc(my_nn_get_n_params(&(cell_parent->brain)) * sizeof(double));
            my_nn_to_array(&(cell_parent->brain), &arr);
            for (uint32_t j = 0; j < my_nn_get_n_params(&(cell_parent->brain)); ++j) {
                if (my_randfloat(0, 1) <= evo->mutation_chance)
                    arr[j] += my_randfloat(-1 * evo->mutation_range, evo->mutation_range);
            }
            my_nn_from_array(&(cell_child->brain), arr);
            free(arr);
            // reset
            my_matrix_randint(0, SIZE, 2, &(cell_child->atb), &(cell_parent->atb));
            cell_parent->color = sfBlue;
            cell_child->color = sfRed;
        }
        // reset
        i_selected = 0;
        my_matrix_setall(unselected, 0);
        my_matrix_setall(selected, 0);
        usleep(1000);
        tick = 0;
        gen_i++;
    }
}
