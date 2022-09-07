#include "stdlib.h"
#include "pixel.h"



PIXEL * get_pixel_matrix(FILE * file)
{
    BMP_HEADER * header = get_header(file);
    uint8_t * matrix = get_bytes_matrix(header, file);
    uint16_t bitPerPixel = header->BitCount;

    size_t rowLen = (size_t)((header->BitCount * header->Width + 31)/32)*4;
    size_t byteCount = rowLen*abs(header->Height);
    size_t pixelCount = byteCount * 8 / header->BitCount;

    PIXEL * pixelMatrix = (PIXEL *)malloc(sizeof(PIXEL) * pixelCount);


    if(bitPerPixel == 32)
    {
        for(int i = 0; i < byteCount; i += 4)
        {
            pixelMatrix[i/4].maxVal = 0b11111111;
            pixelMatrix[i/4].R = matrix[i];
            pixelMatrix[i/4].G = matrix[i+1]; 
            pixelMatrix[i/4].B = matrix[i+2];
            pixelMatrix[i/4].A = matrix[i+3]; 
        }
    }
    else if (bitPerPixel == 24)
    {
        for(int i = 0; i < byteCount; i += 3)
        {
            pixelMatrix[i/3].maxVal = 0b00111111;
            pixelMatrix[i/3].R = (matrix[i] & 0b11111100) >> 2;
            pixelMatrix[i/3].G = (matrix[i] & 0b00000011) << 4 + 
                                 (matrix[i+1] & 0b11110000) >> 4;
            pixelMatrix[i/3].B = (matrix[i+1] & 0b00001111) << 2 +
                                 (matrix[i+2] & 0b11000000) >> 4;
            pixelMatrix[i/3].A = (matrix[i+2] & 0b00111111); 
        }
    }
    else if (bitPerPixel == 16)
    {
        for(int i = 0; i < byteCount; i += 2)
        {
            pixelMatrix[i/2].maxVal = 0b00001111;
            pixelMatrix[i/2].R = (matrix[i] & 0b11110000) >> 4;
            pixelMatrix[i/2].G = (matrix[i] & 0b00001111);
            pixelMatrix[i/2].B = (matrix[i+1] & 0b11110000) >> 4;
            pixelMatrix[i/2].A = (matrix[i+1] & 0b00001111);
        }
    }
    else if (bitPerPixel == 8)
    {
        for(int i = 0; i < byteCount; i++)
        {
            pixelMatrix[i].maxVal = 0b000000011;
            pixelMatrix[i].R = (matrix[i] & 0b11000000) >> 6;
            pixelMatrix[i].G = (matrix[i] & 0b00110000) >> 4;
            pixelMatrix[i].B = (matrix[i] & 0b00001100) >> 2;
            pixelMatrix[i].A = (matrix[i] & 0b00000011);
        }
    }
    // else if (bitPerPixel == 4)
    // {
    //     for(int i = 0; i < byteCount; i++)
    //     {
    //         pixelMatrix[i].maxVal = 0b00000001;
    //         pixelMatrix[i].R = (matrix[i] & 0b10000000) >> 7;
    //         pixelMatrix[i].G = (matrix[i] & 0b01000000) >> 6;
    //         pixelMatrix[i].B = (matrix[i] & 0b00100000) >> 5;
    //         pixelMatrix[i].A = (matrix[i] & 0b00010000) >> 4;
    //         pixelMatrix[i+1].maxVal = 0b00000001;
    //         pixelMatrix[i+1].R = (matrix[i] & 0b00001000) >> 3;
    //         pixelMatrix[i+1].G = (matrix[i] & 0b00000100) >> 2;
    //         pixelMatrix[i+1].B = (matrix[i] & 0b00000010) >> 1;
    //         pixelMatrix[i+1].A = (matrix[i] & 0b00000001);
    //     }
    // }
    // else if (bitPerPixel == 1)
    // {

    // }
    // else if (bitPerPixel == 64)
    // {

    // }

    free(header);
    free(matrix);

    return pixelMatrix;
}