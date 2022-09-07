#include <stdint.h>
#include <stdlib.h>

#include "header.h"



typedef struct {
    uint8_t maxVal;
    uint8_t R;
    uint8_t G;
    uint8_t B;
    uint8_t A;
} PIXEL;


PIXEL * get_pixel_matrix(FILE * file);