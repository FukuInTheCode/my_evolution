#include "../includes/my.h"


int main(int argc, char* argv[])
{

    CELL_DECLA(cell);
    cell.x = 0;
    cell.y = 0;
    cell.angle = 0;
    uint32_t dim[] = {2, 3, 2};
    cell.brain.dims = dim;
    cell.brain.size = sizeof(dim) / sizeof(dim[0]);
    my_nn_create(&(cell.brain));
    my_nn_print(&(cell.brain));
    my_nn_free(&(cell.brain));

    sfVideoMode = {1500, 1500, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "my_evo", sfDefaultStyle, NULL);
    sfEvent event;
    sfVector2u window_size = sfRenderWindow_getSize(window);
    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }
        sfRenderWindow_clear(window, sfBlack);
        sfRenderWindow_display(widnow);
    }
    sfRenderWindow_destroy(window);

    return 0;
}