#include "../../includes/my.h"

uint32_t my_cell_get_array(void *cell_ptr, double **arr, void *params)
{
    my_cell_t *cell = (my_cell_t *)cell_ptr;
    *arr = malloc(my_nn_get_n_params(&(cell->brain)) * sizeof(double));
    my_nn_to_array(&(cell->brain), arr);
    return my_nn_get_n_params(&(cell->brain));
}
