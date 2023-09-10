#include "../includes/my.h"

double set(double x)
{
    return -1. * (x < 0) + (x > 0);
}

int main(int argc, char* argv[])
{

    srand(69);

    // my_evo_t

    my_evo_t evo = {
        .pop_size = 100,
        .max_tick_per_gen = SIZE / 3. * 2.,
        .mutation_chance = 0.3,
        .mutation_range = 1.,
        .agent_struct_size = sizeof(my_cell_t),
        .do_per_n_gen = 1
    };
    // used var

    // population creattion (main)

    sfVideoMode mode = {1500, 1500, 32};
    my_evo_viz(&evo, mode);



    for (uint32_t i = 0; i < evo.pop_size; ++i) {
        my_cell_t *cell = (my_cell_t *)((char *)evo.pop + evo.agent_struct_size * i);

        my_nn_free(&(cell->brain));
        MAT_FREE((cell->atb));
    }

    free(evo.pop);

    return 0;
}