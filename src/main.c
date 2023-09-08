#include "../includes/my.h"

#define RADIUS 16

#define C_COLOR sfRed


int main(int argc, char* argv[])
{
    srand(69);

    CELL_DECLA(cell);
    cell.x = 0;
    cell.y = 0;
    cell.angle = 0;
    uint32_t dim[] = {3, 3, 3};
    cell.brain.dims = dim;
    cell.brain.size = sizeof(dim) / sizeof(dim[0]);
    my_nn_create(&(cell.brain));
    my_nn_print(&(cell.brain));
    my_nn_free(&(cell.brain));

    sfVideoMode mode = {1500, 1500, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "my_evo", sfDefaultStyle, NULL);
    sfEvent event;
    sfVector2u window_size = sfRenderWindow_getSize(window);
    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }
        sfRenderWindow_clear(window, sfBlack);
        sfCircleShape *pt =sfCircleShape_create();
        sfVector2f pos = {
            .x = cell.x + window_size.x / 2,
            .y = cell.y + window_size.y / 2
        };
        sfVertex line[] = {
            {{pos.x  + RADIUS, pos.y  + RADIUS}, C_COLOR, {0, 0}},
            {{pos.x + 100. * cos(cell.angle) + RADIUS, pos.y + 100. * sin(cell.angle) + RADIUS}, C_COLOR, {0, 0}}
        };
        sfRenderWindow_drawPrimitives(window, line, 2, sfLines, NULL);
        sfCircleShape_setFillColor(pt, C_COLOR);
        sfCircleShape_setPosition(pt, pos);
        sfCircleShape_setRadius(pt, RADIUS);
        sfRenderWindow_drawCircleShape(window, pt, NULL);
        sfRenderWindow_display(window);
    }
    sfRenderWindow_destroy(window);

    return 0;
}