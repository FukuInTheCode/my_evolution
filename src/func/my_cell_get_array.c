#include "../../includes/my.h"

void my_cell_get_array(void *cell_ptr, double **arr)
{
    my_cell_t *cell = (my_cell_t *)cell_ptr;
    *arr = malloc(my_nn_get_n_params(&(cell->brain)) * sizeof(double));
    my_nn_to_array(&(cell->brain), arr);

}
