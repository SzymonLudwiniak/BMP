#ifndef HEADER
#define HEADER

#include <stdint.h>
#include <stdio.h>


typedef struct {
    //HEADER - 14 bytes
    uint16_t Signature; // "BM" - bitmap 0x42 0x4D
    uint32_t FileSize;  // can be skipped
    uint32_t reserved;
    uint32_t DataOffset; // where pixel matrix starts
    
    //DIB HEADER
    uint32_t Size;  // dib header size
    uint32_t Width; // visible width
    int32_t Height; // image height
    uint16_t Planes; // wiki says must be 1
    uint16_t BitCount; // bits per pixel
    uint32_t Compression; // wish none
    uint32_t ImageSize; // yas
    int32_t XpixelsPerM; // pixel per metre?
    int32_t YpixelsPerM; // pixel per metre?
    uint32_t ColorsUsed; // number of colors | 0 = 2^n
    uint32_t ColorsImportant; // mostly doesn't matter
} BMP_HEADER;


BMP_HEADER * get_header(FILE * file);
uint8_t * get_bytes_matrix(BMP_HEADER * header, FILE * file);


#endif
