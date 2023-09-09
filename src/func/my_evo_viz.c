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

static uint32_t do_gen(my_evo_t *evo, my_matrix_t **s_matrices,\
                                uint32_t tick, uint32_t i_selected)
{
    if (tick < evo->max_tick_per_gen) {
        my_cell_update(evo->pop, evo->pop_size);
    } else if (tick == evo->max_tick_per_gen) {
        i_selected = my_evo_do_selection(evo, &(s_matrices[0]), &(s_matrices[1]));
    } else {
        my_evo_duplica(evo, &(s_matrices[0]), &(s_matrices[1]), i_selected);
        i_selected = 0;
        my_matrix_setall(&(s_matrices[1]), 0);
        my_matrix_setall(&(s_matrices[0]), 0);
    }
}


void my_evo_viz(my_evo_t *evo, sfVideoMode mode)
{
    sfRenderWindow *window = sfRenderWindow_create(mode, "my_evo",\
                                                sfDefaultStyle, NULL);
    uint32_t tick = 0;
    my_matrix_t *s_matrices;
    my_matrix_create_array(&s_matrices, "S", 2,\
                    evo->pop_size / 2, 2, evo->pop_size, 1);
    uint32_t gen_i = 0;
    uint32_t i_selected = 0;
    while (sfRenderWindow_isOpen(window)) {
        handle_event(window);
        handle_show(evo, window);
        i_selected = do_gen(evo, &s_matrices, tick, i_selected);
        tick = (tick + 1) % (evo->max_tick_per_gen + 2);
    }
    sfRenderWindow_destroy(window);
    my_matrix_free_array(&s_matrices, 2);
}
