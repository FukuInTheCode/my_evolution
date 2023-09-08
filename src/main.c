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

    uint32_t pop_size = 100;

    my_cell_t pop[pop_size];

    uint32_t dims[] = {2, 3, 2};
    for (uint32_t i = 0; i < pop_size; ++i) {
        pop[i].brain.size = 3;
        pop[i].brain.name = "brain";
        pop[i].brain.dims = dims;
        my_nn_create(&pop[i].brain);
        pop[i].brain.acti_type = base_type;
        pop[i].brain.funcs.af = my_nn_sin;
        pop[i].brain.funcs.grad_af = my_nn_sin_grad;
        pop[i].atb.m = 0;
        pop[i].atb.n = 0;
        pop[i].atb.name = "atb";
        my_matrix_create(2, 1, 1, &pop[i].atb);
        my_matrix_set(&(pop[i].atb), 0, 0, my_randint(0, SIZE));
        my_matrix_set(&(pop[i].atb), 1, 0, my_randint(0, SIZE));
    }

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
        // if (sfKeyboard_isKeyPressed(sfKeyLeft))
        //     my_matrix_set(&(cell.atb), 0, 0, cell.atb.arr[0][0] - 1);
        // if (sfKeyboard_isKeyPressed(sfKeyRight))
        //     my_matrix_set(&(cell.atb), 0, 0, cell.atb.arr[0][0] + 1);
        // if (sfKeyboard_isKeyPressed(sfKeyUp))
        //     my_matrix_set(&(cell.atb), 1, 0, cell.atb.arr[1][0] - 1);
        // if (sfKeyboard_isKeyPressed(sfKeyDown))
        //     my_matrix_set(&(cell.atb), 1, 0, cell.atb.arr[1][0] + 1);

        if (tick <= max_tick) {
            for (uint32_t i = 0; i < pop_size; ++i) {
                MAT_DECLA(datb);
                my_nn_predict(&(pop[i].brain), &(pop[i].atb), &datb);
                datb.arr[0][0] = set(datb.arr[0][0]);
                datb.arr[1][0] = set(datb.arr[1][0]);
                MAT_DECLA(new_atb);
                my_matrix_add(&new_atb, 2, &(pop[i].atb), &datb);
                bool can_move = true;
                if (new_atb.arr[0][0] < 0)
                    can_move = false;
                if (new_atb.arr[1][0] < 0)
                    can_move = false;
                if (new_atb.arr[0][0] > SIZE)
                    can_move = false;
                if (new_atb.arr[1][0] > SIZE)
                    can_move = false;
                for (uint32_t j = 0; j < pop_size; ++j) {
                    if (my_matrix_equals(&(pop[j].atb), &new_atb))
                        can_move = false;
                }
                if (can_move)
                    my_matrix_copy(&new_atb, &(pop[i].atb));
                my_matrix_free(2, &datb, &new_atb);
            }
            ++tick;
        }

        printf("Hello\n");


        sfRenderWindow_clear(window, sfBlack);
        for (uint32_t i = 0; i < pop_size; ++i) {
            sfVector2f pos = {
                .x = pop[i].atb.arr[0][0] * ratio.x,
                .y = pop[i].atb.arr[1][0] * ratio.y
            };
            sfCircleShape *pt =sfCircleShape_create();
            sfCircleShape_setFillColor(pt, C_COLOR);
            sfCircleShape_setPosition(pt, pos);
            sfCircleShape_setRadius(pt, RADIUS);
            sfRenderWindow_drawCircleShape(window, pt, NULL);
        }
        sfRenderWindow_display(window);
    }
    sfRenderWindow_destroy(window);

    return 0;
}