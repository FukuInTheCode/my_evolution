#include "../../includes/my.h"

void my_evo_duplica(my_evo_t *evo, my_matrix_t *selected, \
                                        my_matrix_t *unselected, uint32_t i_selected)
{
    for (uint32_t i = 0; i < evo->pop_size - i_selected; ++i) {
        void *cell_parent = (void *)((char *)(evo->pop) +\
                    (int)(selected->arr[i % i_selected][0] *\
                                            evo->agent_struct_size));
        double *arr;
        uint32_t arr_size = evo->get_agent_array(cell_parent, &arr);
        for (uint32_t j = 0; j < arr_size; ++j) {
            if (my_randfloat(0, 1) <= evo->mutation_chance)
                arr[j] += my_randfloat(-1 * evo->mutation_range, evo->mutation_range);
        }
        void *cell_child = (void *)((char *)(evo->pop) +\
                        (int)(unselected->arr[i][0]) * evo->agent_struct_size);
        evo->agent_from_array(cell_child, arr);
        free(arr);
        evo->reset_agent(cell_parent, true, evo->pop, evo_pop_size);
        evo->reset_agent(cell_child, false, evo->pop, evo_pop_size);
    }
}
