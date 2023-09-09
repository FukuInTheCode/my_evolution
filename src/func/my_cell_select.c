#include "../../includes/my.h"

bool my_cell_is_select(void *cell_ptr)
{
    my_cell_t *cell = (my_cell_t *)cell_ptr;
    if (cell->atb.arr[0][0] < 1000)
        return false;
    return true;
}
