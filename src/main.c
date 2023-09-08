#include "../includes/my.h"

#define RADIUS 5

#define C_COLOR sfRed

#define SIZE 512.

double set(double x)
{
    return -1. * (x < 0) + (x > 0);
}
int main(int argc, char* argv[])
{
    uint32_t max_tick = 100;
    uint32_t tick = 0;
    srand(time(0));

    double mutation_chance = 0.3;

    uint32_t pop_size = 100;

    uint32_t selected_id[pop_size / 2];
    double selected_reward[pop_size / 2];
    uint32_t max_reward_id;

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
        pop[i].color = C_COLOR;
    }

    sfVideoMode mode = {1500, 1500, 32};
    sfRenderWindow *window = sfRenderWindow_create(mode, "my_evo", sfDefaultStyle, NULL);

    sfVector2u window_size = sfRenderWindow_getSize(window);
    sfVector2f ratio = {
        .x = (window_size.x - 2 * RADIUS) / SIZE,
        .y = (window_size.y - 2 * RADIUS) / SIZE
    };
    sfEvent event;
    uint32_t gen_i = 0;
    bool do_selection = false;
    bool do_reset = false;
    bool do_gen = true;
    while (sfRenderWindow_isOpen(window)) {
        while (sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }
        if (do_gen) {
            if (tick < max_tick) {
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
                if (tick == max_tick) {
                    do_selction = true;
                    do_gen = false;
                }
            }
        } else if (do_selection) {
            double max_reward = -1.;
            uint32_t unselected_id[pop_size / 2];
            uint32_t unselect_i = 0;
            double total_reward = 0;
            for (uint32_t i = 0; i < pop_size; ++i) {
                pop[i].reward = 1. / (sqrt(pow(pop[i].atb.arr[0][0] - SIZE / 2., 2) + pow(pop[i].atb.arr[1][0] - SIZE / 2., 2)) + 1);
                total_reward += pop[i].reward;
                if (max_reward < pop[i].reward) {
                    max_reward = pop[i].reward;
                    max_reward_id = i;
                }
                if (i < pop_size / 2) {
                    selected_id[i] = i;
                    selected_reward[i] = pop[i].reward;
                    continue;
                }
                double min_selected_reward = my_min(selected_reward, pop_size / 2);
                if (min_selected_reward >= pop[i].reward) {
                    unselected_id[unselect_i++] = i;
                    continue;
                }
                uint32_t j;
                for (j = 0; j < pop_size / 2; ++j) {
                    if (min_selected_reward == selected_reward[j])
                        break;
                }
                unselected_id[unselect_i++] = selected_id[j];
                selected_id[j] = i;
                selected_reward[j] = pop[i].reward;
            }


            uint32_t n_params = my_nn_get_n_params(&(pop[0].brain));
            unselect_i = 0;
            for (uint32_t i = 0; i < pop_size / 2;  i += 2) {
                uint32_t crosspoint = my_randint(0, n_params);
                double *parent1 = malloc(sizeof(double) * n_params);
                my_nn_to_array(&(pop[i].brain), &parent1);
                double *parent2 = malloc(sizeof(double) * n_params);
                my_nn_to_array(&(pop[i + 1].brain), &parent2);
                double *child1 = malloc(sizeof(double) * n_params);
                double *child2 = malloc(sizeof(double) * n_params);
                for (uint32_t j = 0; j < crosspoint; ++j) {
                    child1[j] = parent1[j];
                    child2[j] = parent2[j];
                }
                for (uint32_t j = crosspoint; j < n_params; ++j) {
                    child1[j] = parent2[j];
                    child2[j] = parent1[j];
                }

                if (my_randfloat(0, 1) < mutation_chance) {
                    child1[my_randint(0, n_params - 1)] += my_randfloat(-1, 1);
                    child2[my_randint(0, n_params - 1)] += my_randfloat(-1, 1);
                }

                my_nn_from_array(&(pop[unselected_id[unselect_i++]].brain), child1);
                my_nn_from_array(&(pop[unselected_id[unselect_i++]].brain), child2);
                free(parent1);
                free(parent2);
                free(child1);
                free(child2);
            }

            printf("gen %u's avr reward: %lf\n", gen_i++, total_reward / pop_size);
            for (uint32_t i = 0; i < pop_size / 2; ++i)
                pop[selected_id[i]].color = sfGreen;
            for (uint32_t i = 0; i < pop_size / 2; ++i)
                pop[unselected_id[i]].color = sfCyan;
            pop[max_reward_id].color = sfBlue;
            do_reset = true;
        } else if (do_reset) {
            usleep(1000000);
            for (uint32_t i = 0; i < pop_size; ++i){
                my_matrix_randint(0, SIZE, 1, &(pop[i].atb));
                pop[i].color = sfRed;
            }
            pop[max_reward_id].color = sfBlue;
            do_gen = true;
            do_selection = false;
            do_reset = false;
            tick = 0;
        }

        sfRenderWindow_clear(window, sfBlack);
        for (uint32_t i = 0; i < pop_size; ++i) {
            // if (tick == max_tick + 1) {
            //     bool is_selected = false;
            //     for (uint32_t j = 0; j < pop_size / 2; ++j) {
            //         if (selected_id[j] == i) {
            //             is_selected = true;
            //             break;
            //         }
            //     }
            //     if (!is_selected)
            //         continue;
            // }
            sfVector2f pos = {
                .x = pop[i].atb.arr[0][0] * ratio.x,
                .y = pop[i].atb.arr[1][0] * ratio.y
            };
            sfCircleShape *pt =sfCircleShape_create();
            sfCircleShape_setFillColor(pt, pop[i].color);
            sfCircleShape_setPosition(pt, pos);
            sfCircleShape_setRadius(pt, RADIUS);
            sfRenderWindow_drawCircleShape(window, pt, NULL);
        }
        sfRenderWindow_display(window);
    }
    sfRenderWindow_destroy(window);

    return 0;
}