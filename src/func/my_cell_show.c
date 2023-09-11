#include "../../includes/my.h"

static void draw_rectangle(sfRenderWindow *window, sfVector2f ratio)
{
    sfRectangleShape *selection_zone = sfRectangleShape_create();
    sfRectangleShape_setOutlineColor(selection_zone, sfWhite);
    sfRectangleShape_setOutlineThickness(selection_zone, 3);
    sfRectangleShape_setFillColor(selection_zone, sfTransparent);
    sfVector2f zone_vec = {
        .x = SIZE / 3. * ratio.x + RADIUS,
        .y = SIZE * ratio.y + RADIUS
    };
    sfRectangleShape_setSize(selection_zone, zone_vec);
    zone_vec.x += SIZE / 3. * ratio.x;
    zone_vec.y = 0;
    sfRectangleShape_setPosition(selection_zone, zone_vec);
    sfRenderWindow_drawRectangleShape(window, selection_zone, NULL);
}

void my_cell_draw(sfRenderWindow *window, void *cell, void *params)
{
    sfVector2u window_size = sfRenderWindow_getSize(window);
    sfVector2f ratio = {
        (window_size.x - RADIUS * 2) / SIZE,
        (window_size.y - RADIUS * 2) / SIZE,
    };
    draw_rectangle(window, ratio);
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
