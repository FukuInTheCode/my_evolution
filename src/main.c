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
        .do_per_n_gen = 1,
        .draw_agent = my_cell_draw,
        .update_agents = my_cell_update,
        .agent_is_select = my_cell_is_select,
        .get_agent_reward = my_cell_get_reward
    };
    // used var

    // population creattion (main)

    my_evo_create(&evo);

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