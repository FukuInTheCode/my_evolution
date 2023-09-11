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
        evo->draw_agent(window, cell);
    }
    sfRenderWindow_display(window);
}

void my_evo_viz(my_evo_t *evo, sfVideoMode mode)
{
    sfRenderWindow *window = sfRenderWindow_create(mode, "my_evo",\
                                                sfDefaultStyle, NULL);
    uint32_t tick = 0;
    my_matrix_t *s_matrices;
    my_matrix_create_array(&s_matrices, "S", 2,\
                    evo->selected_size, 2, evo->pop_size, 1);
    uint32_t i_selected = 0;
    while (sfRenderWindow_isOpen(window)) {
        handle_event(window);
        handle_show(evo, window);
        i_selected = my_evo_algo(evo, &s_matrices, tick, i_selected);
        tick = (tick + 1) % (evo->max_tick_per_gen + 2);
    }
    sfRenderWindow_destroy(window);
    my_matrix_free_array(&s_matrices, 2);
}
