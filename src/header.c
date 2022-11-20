#include <stdlib.h>
#include <math.h>

#include "../include/header.h"


BMP_HEADER * get_header(FILE * file)
{

    fseek(file, 0, SEEK_SET);

    BMP_HEADER * bmp_header = (BMP_HEADER *)malloc(sizeof(BMP_HEADER));

    fread(&(bmp_header->Signature), sizeof(uint16_t), 1, file);

    if(bmp_header->Signature != 0x4d42)
        return NULL;

    fread(&(bmp_header->FileSize), sizeof(uint32_t), 1, file);
    fread(&(bmp_header->reserved), sizeof(uint32_t), 1, file);
    fread(&(bmp_header->DataOffset), sizeof(uint32_t), 1, file);

    fread(&(bmp_header->Size), sizeof(uint32_t), 1, file);
    fread(&(bmp_header->Width), sizeof(uint32_t), 1, file);
    fread(&(bmp_header->Height), sizeof(int32_t), 1, file);
    fread(&(bmp_header->Planes), sizeof(uint16_t), 1, file);
    fread(&(bmp_header->BitCount), sizeof(uint16_t), 1, file);
    fread(&(bmp_header->Compression), sizeof(uint32_t), 1, file);
    fread(&(bmp_header->ImageSize), sizeof(uint32_t), 1, file);
    fread(&(bmp_header->XpixelsPerM), sizeof(int32_t), 1, file);
    fread(&(bmp_header->YpixelsPerM), sizeof(int32_t), 1, file);
    fread(&(bmp_header->ColorsUsed), sizeof(uint32_t), 1, file);
    fread(&(bmp_header->ColorsImportant), sizeof(uint32_t), 1, file);

    printf("bits per pixel:%d\noffset:%d\n", bmp_header->BitCount, bmp_header->DataOffset);

    return bmp_header;
}

uint8_t * get_bytes_matrix(BMP_HEADER * header, FILE * file)
{
    fseek(file, header->DataOffset, SEEK_SET);

    size_t row_len = (size_t)((header->BitCount * header->Width + 31)/32)*4;
    size_t byte_amount = row_len*abs(header->Height);
    
    uint8_t * matrix = (uint8_t *)malloc(sizeof(uint8_t)*byte_amount);

    fread(matrix, sizeof(uint8_t), byte_amount, file);

    return matrix;
}