#include "../../includes/my.h"

void my_evo_free(my_evo_t *evo)
{
    for (uint32_t i = 0; i < evo.pop_size; ++i) {
        my_cell_t *cell = (my_cell_t *)((char *)evo.pop +\
                                        evo.agent_struct_size * i);
    }

    free(evo.pop);
}