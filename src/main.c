#include "../includes/my.h"

#define RADIUS 5

#define C_COLOR sfRed

#define SIZE 128.

double set(double x)
{
    return -1. * (x < 0) + (x > 0);
}
uint32_t max_tick = SIZE * sqrt(2);
uint32_t tick = 0;
int main(int argc, char* argv[])
{
    srand(69);

    CELL_DECLA(cell);
    cell.brain.size = 3;
    uint32_t dims[] = {3, 3, 3};
    cell.brain.dims = dims;
    my_nn_create(&cell.brain);
    cell.brain.acti_type = base_type;
    cell.brain.funcs.af = my_nn_sin;
    cell.brain.funcs.grad_af = my_nn_sin_grad;
    my_matrix_create(3, 1, 1, &cell.atb);
    my_matrix_set(&(cell.atb), 0, 0, 64);
    my_matrix_set(&(cell.atb), 1, 0, 64);
    my_nn_print(&cell.brain);
    MAT_PRINT(cell.atb);

    sfVideoMode mode = {1500, 1500, 32};
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
        if (sfKeyboard_isKeyPressed(sfKeyLeft))
            my_matrix_set(&(cell.atb), 0, 0, cell.atb.arr[0][0] - 1);
        if (sfKeyboard_isKeyPressed(sfKeyRight))
            my_matrix_set(&(cell.atb), 0, 0, cell.atb.arr[0][0] + 1);
        if (sfKeyboard_isKeyPressed(sfKeyUp))
            my_matrix_set(&(cell.atb), 1, 0, cell.atb.arr[1][0] - 1);
        if (sfKeyboard_isKeyPressed(sfKeyDown))
            my_matrix_set(&(cell.atb), 1, 0, cell.atb.arr[1][0] + 1);

        if (tick <= max_tick) {
            MAT_DECLA(datb);
            my_nn_predict(&(cell.brain), &(cell.atb), &datb);
            datb.arr[0][0] = set(datb.arr[0][0]);
            datb.arr[1][0] = set(datb.arr[1][0]);
            MAT_DECLA(new_atb);
            my_matrix_add(&new_atb, 2, &(cell.atb), &(datb));
            my_matrix_copy(&new_atb, &(cell.atb));
            my_matrix_free(2, &datb, &new_atb);
            ++tick;
        }

        if ((int)cell.atb.arr[0][0] < 0)
            my_matrix_set(&(cell.atb), 0, 0, 0);
        if ((int)cell.atb.arr[1][0] < 0)
            my_matrix_set(&(cell.atb), 1, 0, 0);
        if ((int)cell.atb.arr[0][0] > SIZE)
            my_matrix_set(&(cell.atb), 0, 0, SIZE);
        if ((int)cell.atb.arr[1][0] > SIZE)
            my_matrix_set(&(cell.atb), 1, 0, SIZE);

        sfRenderWindow_clear(window, sfBlack);
        sfCircleShape *pt =sfCircleShape_create();
        sfVector2f pos = {
            .x = cell.atb.arr[0][0] * ratio.x,
            .y = cell.atb.arr[1][0] * ratio.y
        };
        // printf("%lf, %lf\n", pos.x, pos.y);
        sfCircleShape_setFillColor(pt, C_COLOR);
        sfCircleShape_setPosition(pt, pos);
        sfCircleShape_setRadius(pt, RADIUS);
        sfRenderWindow_drawCircleShape(window, pt, NULL);
        sfRenderWindow_display(window);
    }
    sfRenderWindow_destroy(window);

    return 0;
}