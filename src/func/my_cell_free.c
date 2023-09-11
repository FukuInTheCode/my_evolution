#include "../../includes/my.h"

void my_cell_free(void *cell_ptr, void *params)
{
    my_cell_t *cell = (my_cell_t *)cell_ptr;

    my_nn_free(&(cell->brain));
    MAT_FREE((cell->atb));
}
