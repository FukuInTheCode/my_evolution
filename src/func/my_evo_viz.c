#include "../../includes/my.h"

static void handle_event(sfRenderWindow *window)
{
    sfEvent event;
    while (sfRenderWindow_pollEvent(window, &event)) {
        if (event.type == sfEvtClosed)
            sfRenderWindow_close(window);
    }
}

static void handle_show(my_evo_t *evo, sfRenderWindow *window)
{
    sfVector2u window_size = sfRenderWindow_getSize(window);
    sfVector2f ratio = {
        .x = (window_size.x - 2 * RADIUS) / SIZE,
        .y = (window_size.y - 2 * RADIUS) / SIZE
    };
    sfRenderWindow_clear(window, sfBlack);
    for (uint32_t i = 0; i < evo->pop_size; ++i) {
        void *cell = (void *)((char *)(evo->pop) + i * evo->agent_struct_size);
        my_cell_show(window, cell, ratio);
    }
    sfRenderWindow_display(window);
}

void my_evo_viz(my_evo_t *evo, sfVideoMode mode)
{
    sfRenderWindow *window = sfRenderWindow_create(mode, "my_evo",\
                                                sfDefaultStyle, NULL);
    uint32_t tick = 0;
    MAT_DECLA(selected);
    my_matrix_create(evo->pop_size / 2, 2, 1, &selected);
    MAT_DECLA(unselected);
    my_matrix_create(evo->pop_size, 1, 1, &unselected);
    uint32_t gen_i = 0;
    while (sfRenderWindow_isOpen(window)) {
        handle_event(window);
        handle_show(evo, window);
        if (tick < evo->max_tick_per_gen) {
            my_cell_update(evo->pop, evo->pop_size);
            ++tick;
        } else if (tick == evo->max_tick_per_gen) {
            i_selected = my_evo_do_selection(evo, selected, unselected);
            ++tick;
        } else {
            // duplica
            MAT_PRINT((*selected));
            MAT_PRINT((*unselected));
            for (uint32_t i = 0; i < evo->pop_size - i_selected; ++i) {
                // printf("%zu, %i, %zu\n", evo->pop, (int)unselected->arr[i][0], evo->agent_struct_size);
                my_cell_t *cell_child = (my_cell_t *)((char *)(evo->pop) + (int)(unselected->arr[i][0]) * evo->agent_struct_size);
                my_cell_t *cell_parent = (my_cell_t *)((char *)(evo->pop) + (int)(selected->arr[i % i_selected][0]) * evo->agent_struct_size);
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
            my_matrix_setall(unselected, 0);
            my_matrix_setall(selected, 0);
            usleep(1000);
        }
    }
    sfRenderWindow_destroy(window);
    MAT_FREE(selected);
    MAT_FREE(unselected);
}
