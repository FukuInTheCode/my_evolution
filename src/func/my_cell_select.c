#include "../../includes/my.h"

bool my_cell_is_select(void *cell_ptr, void *pop, uint32_t pop_size, void *params)
{
    my_cell_t *cell = (my_cell_t *)cell_ptr;
    if (cell->atb.arr[0][0] < SIZE / 3 * 2)
        return false;
    return true;
}
