#include "../includes/my.h"

#define RADIUS 16

#define C_COLOR sfRed


int main(int argc, char* argv[])
{
    srand(69);

    CELL_DECLA(cell);
    cell.brain.size = 3;
    uint32_t dims[] = {3, 3, 3};
    cell.brain.dims = dims;
    my_matrix_create(1, 3, 1, &cell.atb);
    my_nn_create(&cell.brain);
    my_nn_print(&cell.brain);
    MAT_PRINT(cell.atb);

#if 0

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
            .x = cell.atrbt.arr[0][0] + window_size.x / 2,
            .y = cell.atrbt.arr[0][1] + window_size.y / 2
        };
        sfVertex line[] = {
            {{pos.x  + RADIUS, pos.y  + RADIUS}, C_COLOR, {0, 0}},
            {{pos.x + 100. * cos(cell.atrbt.arr[0][2]) + RADIUS, pos.y + 100. * sin(cell.atrbt.arr[0][2]) + RADIUS}, C_COLOR, {0, 0}}
        };
        sfRenderWindow_drawPrimitives(window, line, 2, sfLines, NULL);
        sfCircleShape_setFillColor(pt, C_COLOR);
        sfCircleShape_setPosition(pt, pos);
        sfCircleShape_setRadius(pt, RADIUS);
        sfRenderWindow_drawCircleShape(window, pt, NULL);
        sfRenderWindow_display(window);
    }
    sfRenderWindow_destroy(window);
#endif

    return 0;
}