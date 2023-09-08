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


    return 0;
}