#include "../../includes/my.h"

double my_cell_get_reward(void *cell_ptr, void *pop, uint32_t pop_size)
{
    my_cell_t *cell = (my_cell_t *)cell_ptr;
    return 1. / (SIZE - cell->atb.arr[0][0] + 1.);
}

double my_cell_get_reward_2(void *cell_ptr, void *pop, uint32_t pop_size)
{
    my_cell_t *cell = (my_cell_t *)cell_ptr;
    double dist = pow(0 - cell->atb.arr[0][0] + 1., 2) +\
                        pow(0 - cell->atb.arr[1][0] + 1., 2);
    return 1. / sqrt(dist);
}
