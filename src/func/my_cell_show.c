#include "../../includes/my.h"

void my_cell_show(sfRenderWindow *window, void *cell, sfVector2f ratio)
{
    sfRectangleShape *selection_zone = sfRectangleShape_create();
    sfRectangleShape_setFillColor(selection_zone, sfWhite);
    sfVector2f zone_vec = {
        .x = SIZE / 3 * ratio.x,
        .y = SIZE * ratio.y
    };
    sfRectangleShape_setSize(selction_zone, zone_vec);
    zone_vec.x += SIZE / 3 * ratio.x;
    zone_vec.y = 0;
    sfRectangleShape_setPosition(selection_zone, zone_vec);
    sfRenderWindow_drawRectangleShape(window, selection_zone, NULL);
    my_cell_t *cell_ptr = (my_cell_t *)cell;
    sfVector2f pos = {
        .x = cell_ptr->atb.arr[0][0] * ratio.x,
        .y = cell_ptr->atb.arr[1][0] * ratio.y
    };
    sfCircleShape *pt =sfCircleShape_create();
    sfCircleShape_setFillColor(pt, cell_ptr->color);
    sfCircleShape_setPosition(pt, pos);
    sfCircleShape_setRadius(pt, RADIUS);
    sfRenderWindow_drawCircleShape(window, pt, NULL);
    sfCircleShape_destroy(pt);
}
