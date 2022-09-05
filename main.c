#include <stdio.h>

#include "header.h"


int main(int argc, char *argv[])
{
    FILE * file = fopen(argv[1], "rb+");

    if(file == NULL)
    {
        puts("oof");
        return 1;
    }

    BMP_HEADER * header = get_header(file);

    if(header == NULL) 
    {
        puts("something went wrong");
    }
    else
    {
        printf("size: %x\nwidth: %x\nheight: %x\nbits: %x\n", 
                header->Size,
                header->Width,
                header->Height,
                header->BitCount);
        get_pixel_matrix(header, file);
    }

    fclose(file);

    return 0;
}