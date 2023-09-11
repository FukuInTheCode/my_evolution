#include "../../includes/my.h"

void my_cell_reset(void *cell_ptr, void *pop, uint32_t pop_size, void *params)
{
    my_cell_t *cell = (my_cell_t *)cell_ptr;
    my_matrix_randint(0, SIZE, 1, &(cell->atb));
}
