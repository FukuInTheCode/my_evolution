#include "../includes/my.h"

double set(double x)
{
    return -1. * (x < 0) + (x > 0);
}

int main(int argc, char* argv[])
{
    srand(time(0));
    my_evo_t evo = {
        .pop_size = 100,
        .max_tick_per_gen = 100,
        .mutation_chance = 0.3,
        .mutation_range = 1.,
        .agent_struct_size = sizeof(my_cell_t),
        .gen_skip = 0,
        .selected_size = 30,
        .draw_agent = my_cell_draw,
        .update_agent = my_cell_update,
        .agent_is_select = my_cell_is_select,
        .get_agent_reward = my_cell_get_reward,
        .get_agent_array = my_cell_get_array,
        .reset_agent = my_cell_reset,
        .agent_from_array = my_cell_from_array,
        .create_agent = my_cell_create,
        .free_agent = my_cell_free
    };
    my_evo_create(&evo);
    sfVideoMode mode = {1500, 1500, 32};
    my_evo_viz(&evo, mode);
    my_evo_free(&evo);
    return 0;
}