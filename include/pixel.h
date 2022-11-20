#include <stdint.h>
#include <stdlib.h>

#include "header.h"



typedef struct {
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t A; 
} PIXEL;


PIXEL * get_pixel_matrix(FILE * file);
PIXEL * get_modified_matrix(PIXEL * oldMatrix, BMP_HEADER * header, size_t * mask[3]);
FILE * set_new_matrix(FILE * file, PIXEL * newMatrix);
FILE * set_new_file(FILE * file, BMP_HEADER * header, PIXEL * newMatrix);