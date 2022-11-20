#include <stdio.h>

#include "../include/pixel.h"
#include "../include/utility.h"


int main(int argc, char *argv[])
{
    FILE * file = fopen(argv[1], "rb");
    
    char * newFileName = createNewFileName(argv);

    if(file == NULL)
    {
        puts("oof");
        return 1;
    }

    PIXEL * pixelMatrix = get_pixel_matrix(file);
    BMP_HEADER * header = get_header(file);

    if(header == NULL)
        return 1;

    size_t * mask[3];
    mask[0] = (size_t *)malloc(sizeof(size_t)*3);
    mask[1] = (size_t *)malloc(sizeof(size_t)*3);
    mask[2] = (size_t *)malloc(sizeof(size_t)*3);

    mask[0][0] = 0;
    mask[0][1] = -1;
    mask[0][2] = 0; 

    mask[1][0] = -1;
    mask[1][1] = 4;
    mask[1][2] = -1; 

    mask[2][0] = 0;
    mask[2][1] = -1;
    mask[2][2] = 0; 

    PIXEL * newPixelMatrix = get_modified_matrix(pixelMatrix, header, mask);

    fclose(file);

    file = fopen(newFileName, "wb");
    if(file == NULL)
    {
        puts("oof");
        return 1;
    }
    set_new_file(file, header, newPixelMatrix);

    fclose(file);

    for(int i = 0; i < 3; i++)
    {
        free(mask[i]);
    }

    free(pixelMatrix);
    free(newPixelMatrix);
    free(newFileName);
    return 0;
}