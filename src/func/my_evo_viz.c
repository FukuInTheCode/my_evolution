#include "../../includes/my.h"

void my_evo_viz(my_evo_t *evo, sfVideoMode mode)
{
    sfRenderWindow *window = sfRenderWindow_create(mode, "my_evo", sfDefaultStyle, NULL);

    sfVector2u window_size = sfRenderWindow_getSize(window);
    sfVector2f ratio = {
        .x = (window_size.x - 2 * RADIUS) / SIZE,
        .y = (window_size.y - 2 * RADIUS) / SIZE
    };
    sfEvent event;
    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }

        // show
        sfRenderWindow_clear(window, sfBlack);
        for (uint32_t i = 0; i < evo->pop_size; ++i) {
            void *cell = (void *)((char *)(evo->pop) + i * evo->agent_struct_size);
            my_cell_show(window, cell, ratio);
        }
        sfRenderWindow_display(window);

        // gen algo

        if (tick < evo->max_tick_per_gen) {
            my_cell_update(evo->pop, evo->pop_size);
            ++tick;
        } else if (tick == evo->max_tick_per_gen) {
            // selection
            for (uint32_t i = 0; i < evo->pop_size; ++i) {
                void *cell = (void *)((char *)(evo->pop) + i * evo->agent_struct_size);
                double cell_reward = my_cell_get_reward(cell);
                bool is_selected = my_cell_is_select(cell);
                if (is_selected && i_selected < evo->pop_size / 2) {
                    my_matrix_set(&selected, i_selected, 0, i);
                    my_matrix_set(&selected, i_selected, 1, cell_reward);
                    i_selected++;
                    continue;
                }
                if (is_selected && i_selected >= evo->pop_size / 2) {
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
            for (uint32_t i = 0; i < evo->pop_size - i_selected; ++i) {
                my_cell_t *cell_child = (my_cell_t *)((char *)(evo->pop) + (int)(unselected.arr[i][0]) * evo->agent_struct_size);
                my_cell_t *cell_parent = (my_cell_t *)((char *)(evo->pop) + (int)(selected.arr[i % i_selected][0]) * evo->agent_struct_size);
                double *arr = malloc(my_nn_get_n_params(&(cell_parent->brain)) * sizeof(double));
                my_nn_to_array(&(cell_parent->brain), &arr);
                for (uint32_t j = 0; j < my_nn_get_n_params(&(cell_parent->brain)); ++j) {
                    if (my_randfloat(0, 1) <= evo->mutation_chance)
                        arr[j] += my_randfloat(-1 * evo->mutation_range, evo->mutation_range);
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
}
