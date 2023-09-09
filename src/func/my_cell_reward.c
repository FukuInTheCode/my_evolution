#include "../../includes/my.h"

double my_cell_get_reward(void *cell_ptr)
{
    my_cell_t *cell = (my_cell_t *)cell_ptr;
    return 1. / (1500. - cell->atb.arr[0][0] + 1.);
}
