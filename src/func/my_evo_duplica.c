#include "../../includes/my.h"

void my_evo_duplica(my_evo_t *evo, my_matrix_t *selected, \
                                        my_matrix_t *unselected, uint32_t i_selected)
{
    for (uint32_t i = 0; i < evo->pop_size - i_selected; ++i) {
        void *cell_parent = (void *)((char *)(evo->pop) +\
                    (int)(selected->arr[i % i_selected][0] *\
                                            evo->agent_struct_size));
        double *arr;
        my_cell_get_array(cell_parent, &arr);
        my_cell_t *cell_child = (my_cell_t *)((char *)(evo->pop) + (int)(unselected->arr[i][0]) * evo->agent_struct_size);
        for (uint32_t j = 0; j < my_nn_get_n_params(&(cell_parent->brain)); ++j) {
            if (my_randfloat(0, 1) <= evo->mutation_chance)
                arr[j] += my_randfloat(-1 * evo->mutation_range, evo->mutation_range);
        }
        // ...
        my_nn_from_array(&(cell_child->brain), arr);
        free(arr);
        // reset
        my_matrix_randint(0, SIZE, 2, &(cell_child->atb), &(cell_parent->atb));
        cell_parent->color = sfBlue;
        cell_child->color = sfRed;
    }
}
