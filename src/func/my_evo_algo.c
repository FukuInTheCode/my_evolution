#include "../../includes/my.h"

static uint32_t do_gen(my_evo_t *evo, my_matrix_t **s_matrices,\
                                uint32_t tick, uint32_t i_selected)
{
    if (tick < evo->max_tick_per_gen) {
        for (uint32_t i = 0; i < evo->pop_size; ++i) {
            void *cell = (void *)((char *)evo->pop + i *\
                                    evo->agent_struct_size);
            evo->pop_size = evo->update_agent(cell, evo->pop, evo->pop_size);
        }
    } else if (tick == evo->max_tick_per_gen) {
        i_selected = my_evo_do_selection(evo, &((*s_matrices)[0]),\
                                                    &((*s_matrices)[1]));
    } else {
        my_evo_duplica(evo, &((*s_matrices)[0]), &((*s_matrices)[1]),\
                                                            i_selected);
        i_selected = 0;
        my_matrix_setall(&((*s_matrices)[1]), 0);
        my_matrix_setall(&((*s_matrices)[0]), 0);
        printf("One more!\n");
    }
    return i_selected;
}

uint32_t my_evo_algo(my_evo_t *evo, my_matrix_t **s_matrices,\
                            uint32_t tick, uint32_t i_selected)
{
    if (tick == 0) {
        for (uint32_t i = 0; i < evo->gen_skip * evo->max_tick_per_gen; ++i)
            uint32_t i_sel_tmp = do_gen(evo, s_matrices, i % evo->max_tick_per_gen, i_sel_tmp);
    }
    return do_gen(evo, s_matrices, tick, i_selected);
}
