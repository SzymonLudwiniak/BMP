#include <stdio.h>
#include <stdlib.h>

#include "pixel.h"


int main(int argc, char *argv[])
{
    FILE * file = fopen(argv[1], "rb+");

    PIXEL * pixelMatrix = get_pixel_matrix(file);
    if(file == NULL)
    {
        puts("oof");
        return 1;
    }

    fclose(file);
    free(pixelMatrix);
    return 0;
}