#include "../../includes/my.h"

void my_evo_create(my_evo_t *evo)
{
    evo.pop = calloc(evo.pop_size, evo.agent_struct_size);
    check_alloc(evo->pop);

    uint32_t dims[] = {2, 3, 2};
    for (size_t i = 0; i < evo.pop_size; ++i) {
        my_cell_t *cell = (my_cell_t *)((char *)(evo.pop) + evo.agent_struct_size * i);
        cell->brain.dims = dims;
        cell->brain.size = 3;
        cell->brain.name = "cell";
        cell->brain.acti_type = base_type;
        cell->brain.funcs.af = my_nn_sin;
        cell->brain.funcs.grad_af = my_nn_sin_grad;
        my_nn_create(&(cell->brain));
        my_matrix_create(2, 1, 1, &(cell->atb));
        my_matrix_randint(0, SIZE, 1, &(cell->atb));
        cell->atb.name = "atb";
        cell->color = sfRed;
    }
}
