#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/pixel.h"


int main(int argc, char *argv[])
{
    FILE * file = fopen(argv[1], "rb+");
    int strLen = strlen(argv[1]);
    char * newFileName;
    newFileName = (char *)malloc(sizeof(char)*(strLen+3));
    strcpy(newFileName, argv[1]);
    int index = strLen-4;
    newFileName[index] = 'm';
    newFileName[index+1] = 'o';
    newFileName[index+2] = 'd';
    newFileName[index+3] = '.';
    strcat(newFileName, "bmp");

    PIXEL * pixelMatrix = get_pixel_matrix(file);
    BMP_HEADER * header = get_header(file);
    if(file == NULL)
    {
        puts("oof");
        return 1;
    }

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


    FILE * newFile = fopen(newFileName, "wb");
    set_new_file(newFile, header, newPixelMatrix);

    fclose(file);
    free(pixelMatrix);
    free(newPixelMatrix);
    return 0;
}