#include "../../includes/my.h"

uint32_t my_evo_do_selection(my_evo_t *evo, my_matrix_t *selected,\
                                            my_matrix_t *unselected)
{
    uint32_t i_selected = 0;
    for (uint32_t i = 0; i < evo->pop_size; ++i) {
        void *cell = (void *)((char *)(evo->pop) + i * evo->agent_struct_size);
        double cell_reward = evo->get_agent_reward(cell, evo->pop, evo->pop_size, evo->params);
        bool is_selected = evo->agent_is_select(cell, evo->pop, evo->pop_size, evo->params);
        if (is_selected && i_selected < evo->selected_size) {
            my_matrix_set(selected, i_selected, 0, i);
            my_matrix_set(selected, i_selected, 1, cell_reward);
            i_selected++;
            continue;
        }
        if (is_selected && i_selected >= evo->selected_size) {
            double min_selected_reward = my_matrix_mincol(selected, 1);
            if (cell_reward > min_selected_reward) {
                uint32_t min_i = my_matrix_find_row_index(selected, 1, min_selected_reward);
                my_matrix_set(unselected, i - i_selected, 0, selected->arr[min_i][0]);
                my_matrix_set(selected, min_i, 0, i);
                my_matrix_set(selected, min_i, 1, cell_reward);
                continue;
            }
        }
        my_matrix_set(unselected, i - i_selected, 0, i);
    }
    return i_selected;
}
