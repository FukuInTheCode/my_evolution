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
        .pop_size = 16,
        .max_tick_per_gen = SIZE / 3. * 2.,
        .mutation_chance = 0.3,
        .mutation_range = 1.,
        .agent_struct_size = sizeof(my_cell_t)
    };
    evo.pop = malloc(evo.agent_struct_size * evo.pop_size);

    // used var
    uint32_t tick = 0;
    uint32_t i_selected = 0;
    MAT_DECLA(selected);
    my_matrix_create(evo.pop_size / 2, 2, 1, &selected);
    MAT_DECLA(unselected);
    my_matrix_create(evo.pop_size, 1, 1, &unselected);
    uint32_t gen_i = 0;
    // population creattion (main)

    uint32_t dims[] = {2, 3, 2};
    for (uint32_t i = 0; i < evo.pop_size; ++i) {
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

    // window creation

    sfVideoMode mode = {1500, 1500, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "my_evo", sfDefaultStyle, NULL);

    sfVector2u window_size = sfRenderWindow_getSize(window);
    sfVector2f ratio = {
        .x = (window_size.x - 2 * RADIUS) / SIZE,
        .y = (window_size.y - 2 * RADIUS) / SIZE
    };
    sfEvent event;

    // window loop
    while (sfRenderWindow_isOpen(window)) {
        // event loop
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }

        // show
        sfRenderWindow_clear(window, sfBlack);
        for (uint32_t i = 0; i < evo.pop_size; ++i) {
            void *cell = (void *)((char *)(evo.pop) + i * evo.agent_struct_size);
            my_cell_show(window, cell, ratio);
        }
        sfRenderWindow_display(window);

        // gen algo

        if (tick < evo.max_tick_per_gen) {
            my_cell_update(evo.pop, evo.pop_size);
            ++tick;
        } else if (tick == evo.max_tick_per_gen) {
            // selection
            for (uint32_t i = 0; i < evo.pop_size; ++i) {
                void *cell = (void *)((char *)(evo.pop) + i * evo.agent_struct_size);
                double cell_reward = my_cell_get_reward(cell);
                bool is_selected = my_cell_is_select(cell);
                if (is_selected && i_selected < evo.pop_size / 2) {
                    my_matrix_set(&selected, i_selected, 0, i);
                    my_matrix_set(&selected, i_selected, 1, cell_reward);
                    i_selected++;
                    continue;
                }
                if (is_selected && i_selected >= evo.pop_size / 2) {
                    double min_selected_reward = my_matrix_mincol(&selected, 1);
                    if (cell_reward > min_selected_reward) {
                        uint32_t min_i = my_matrix_find_row_index(&selected, 1, min_selected_reward);
                        my_matrix_set(&unselected, i - i_selected, 0, selected.arr[min_i][0]);
                        my_matrix_set(&selected, min_i, 0, i);
                        my_matrix_set(&selected, min_i, 1, cell_reward);
                        continue;
                    }
                }
                my_matrix_set(&unselected, i - i_selected, 0, i);
            }
            ++tick;
        } else {
            // duplica
            for (uint32_t i = 0; i < evo.pop_size - i_selected; ++i) {
                my_cell_t *cell_child = (my_cell_t *)((char *)(evo.pop) + (int)(unselected.arr[i][0]) * evo.agent_struct_size);
                my_cell_t *cell_parent = (my_cell_t *)((char *)(evo.pop) + (int)(selected.arr[i % i_selected][0]) * evo.agent_struct_size);
                double *arr = malloc(my_nn_get_n_params(&(cell_parent->brain)) * sizeof(double));
                my_nn_to_array(&(cell_parent->brain), &arr);
                for (uint32_t j = 0; j < my_nn_get_n_params(&(cell_parent->brain)); ++j) {
                    if (my_randfloat(0, 1) <= evo.mutation_chance)
                        arr[j] += my_randfloat(-1 * evo.mutation_range, evo.mutation_range);
                }
                my_nn_from_array(&(cell_child->brain), arr);
                free(arr);
                // reset
                my_matrix_randint(0, SIZE, 2, &(cell_child->atb), &(cell_parent->atb));
                cell_parent->color = sfBlue;
                cell_child->color = sfRed;
            }
            // reset
            i_selected = 0;
            my_matrix_setall(&unselected, 0);
            my_matrix_setall(&selected, 0);
            usleep(1000);
            tick = 0;
            gen_i++;
        }

    }
    sfRenderWindow_destroy(window);


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