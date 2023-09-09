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
    sfVector2f ratio = {
        .x = (mode.width - 2 * RADIUS) / SIZE,
        .y = (mode.height - 2 * RADIUS) / SIZE
    };
    uint32_t tick = 0;
    uint32_t i_selected = 0;
    MAT_DECLA(selected);
    my_matrix_create(evo->pop_size / 2, 2, 1, &selected);
    MAT_DECLA(unselected);
    my_matrix_create(evo->pop_size, 1, 1, &unselected);
    uint32_t gen_i = 0;
    while (sfRenderWindow_isOpen(window)) {
        handle_event(window);
        handle_show(evo, window);
        if (evo->do_per_n_gen == 1)
            tick = my_evo_do_tick(evo, tick, &selected, &unselected);
    }
    sfRenderWindow_destroy(window);
    MAT_FREE(selected);
    MAT_FREE(unselected);
}
