#define MATRIX_CHECK_ALLOC
#include "../../includes/my.h"

void my_evo_create(my_evo_t *evo)
{
    evo->pop = calloc(evo->pop_size, evo->agent_struct_size);
    check_alloc(evo->pop);

    for (size_t i = 0; i < evo->pop_size; ++i) {
        void *cell = (void *)((char *)(evo->pop) + evo->agent_struct_size * i);
        evo->create_agent(cell, evo->params);
    }
}
