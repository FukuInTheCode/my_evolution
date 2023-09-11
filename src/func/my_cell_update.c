#include "../../includes/my.h"

static double set(double x)
{
    return -1. * (x < 0) + (x > 0);
}

static void use_brain(my_cell_t *cell, my_matrix_t *new_atb)
{
    MAT_DECLA(datb);
    my_nn_predict(&(cell->brain), &(cell->atb), &datb);
    my_matrix_applyfunc_2(&datb, set);
    my_matrix_add(new_atb, 2, &(cell->atb), &datb);
    MAT_FREE(datb);
}

static void check_new_atb(my_matrix_t *old_atb, uint32_t pop_size,\
                                        void *pop, my_matrix_t *new_atb)
{
    if (new_atb->arr[0][0] < 0)
        new_atb->arr[0][0] = 0;
    if (new_atb->arr[1][0] < 0)
        new_atb->arr[1][0] = 0;
    if (new_atb->arr[0][0] > SIZE)
        new_atb->arr[0][0] = SIZE;
    if (new_atb->arr[1][0] > SIZE)
        new_atb->arr[1][0] = SIZE;
    for (uint32_t i = 0; i < pop_size; ++i) {
        my_cell_t *cell_ptr = (my_cell_t *)((char *)pop + i * sizeof(my_cell_t));
        if (!my_matrix_equals(&(cell_ptr->atb), new_atb))
            continue;
        new_atb->arr[1][0] = old_atb->arr[1][0];
        new_atb->arr[0][0] = old_atb->arr[0][0];
    }
}


uint32_t my_cell_update(void *cell_ptr, void *pop, uint32_t pop_size, void *)
{
    my_cell_t *cell = (my_cell_t *)cell_ptr;
    MAT_DECLA(new_atb);
    use_brain(cell, &new_atb);
    check_new_atb(&(cell->atb), pop_size, pop, &new_atb);
    my_matrix_copy(&new_atb, &(cell->atb));
    MAT_FREE(new_atb);
    return pop_size;
}