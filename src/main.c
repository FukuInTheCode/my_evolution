#include "../includes/my.h"

double set(double x)
{
    return -1. * (x < 0) + (x > 0);
}

int main(int argc, char* argv[])
{

    srand(69);
    // uint32_t max_reward_id;
    // uint32_t gen_i = 0;

    // my_evo_t

    my_evo_t evo = {
        .pop_size = 100,
        .max_tick_per_gen = SIZE / 3. * 2.,
        .mutation_chance = 0.3,
        .mutation_range = 1.,
        .agent_struct_size = sizeof(my_cell_t)
    };
    evo.pop = calloc(evo.pop_size, evo.agent_struct_size);
    if (evo.pop == NULL) {
        fprintf(stderr, "Alloc failed!");
        exit(1);
    }
    // used var

    // population creattion (main)

    uint32_t dims[] = {2, 3, 2};
    for (size_t i = 0; i < evo.pop_size; ++i) {
        my_cell_t *cell = (my_cell_t *)((char *)(evo.pop) + evo.agent_struct_size * i);
        cell->brain.dims = dims;
        cell->brain.size = 3;
        cell->brain.name = "cell";
        cell->brain.acti_type = base_type;
        cell->brain.funcs.af = my_nn_sin;
        cell->brain.funcs.grad_af = my_nn_sin_grad;
        my_nn_create(&(cell->brain));
        my_matrix_create(2, 1, 1, &(cell->atb));
        my_matrix_randint(0, SIZE, 1, &(cell->atb));
        cell->atb.name = "atb";
        cell->color = sfRed;
    }

    sfVideoMode mode = {1500, 1500, 32};
    my_evo_viz(&evo, mode);



    for (uint32_t i = 0; i < evo.pop_size; ++i) {
        my_cell_t *cell = (my_cell_t *)((char *)evo.pop + evo.agent_struct_size * i);

        my_nn_free(&(cell->brain));
        MAT_FREE((cell->atb));
    }

    free(evo.pop);

    MAT_FREE(selected);
    MAT_FREE(unselected);

    return 0;
}