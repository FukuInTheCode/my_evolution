#include "../../includes/my.h"

void my_cell_from_array(void *cell_ptr, double *arr, void *params)
{
    my_cell_t *cell = (my_cell_t *)cell_ptr;
    my_nn_from_array(&(cell->brain), arr);
}
