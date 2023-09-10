#include "../../includes/my.h"

void my_cell_reset(void *cell_ptr, bool is_selected)
{
    my_cell_t *cell = (my_cell_t *)cell_ptr;
    my_matrix_randint(0, SIZE, 1, &(cell->atb));
    if (is_selected)
        cell->color = sfBlue;
    else
        cell->color = sfRed;
}