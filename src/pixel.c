#include "stdlib.h"
#include "string.h"

#include "../include/pixel.h"


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
            pixelMatrix[i/3].R = matrix[i];
            pixelMatrix[i/3].G = matrix[i+1];
            pixelMatrix[i/3].B = matrix[i+2];
        }
    }

    free(header);
    free(matrix);

    return pixelMatrix;
}

PIXEL * get_modified_matrix(PIXEL * oldMatrix, BMP_HEADER * header, size_t * mask[3])
{
    uint16_t bitPerPixel = header->BitCount;

    size_t rowLen = (size_t)((header->BitCount * header->Width + 31)/32)*4;
    size_t byteCount = rowLen*abs(header->Height);
    size_t pixelCount = byteCount * 8 / header->BitCount;
    
    size_t pixelInRow = pixelCount/header->Height;

    PIXEL * newMatrix = (PIXEL *)malloc(sizeof(PIXEL) * pixelCount);

    int32_t temp;
    for(int y = 1; y < header->Height - 1; y++)
    {
        for(int x = 1; x < header->Width - 1; x++)
        {
            temp =
            oldMatrix[(x-1)+(y-1)*header->Width].R * mask[0][0] + oldMatrix[(x)+(y-1)*header->Width].R * mask[0][1] + oldMatrix[(x+1)+(y-1)*header->Width].R * mask[0][2] +
            oldMatrix[(x-1)+(y)*header->Width].R * mask[1][0] + oldMatrix[(x)+(y)*header->Width].R * mask[1][1] + oldMatrix[(x+1)+(y)*header->Width].R * mask[1][2] +
            oldMatrix[(x-1)+(y+1)*header->Width].R * mask[2][0] + oldMatrix[(x)+(y+1)*header->Width].R * mask[2][1] + oldMatrix[(x+1)+(y+1)*header->Width].R * mask[2][2];

            if(temp > -1 && temp < 256) {newMatrix[x+y*header->Width].R = temp;}
            else if(temp < 0) {newMatrix[x+y*header->Width].R = 0;}
            else {newMatrix[x+y*header->Width].R = 255;}


            temp =
            oldMatrix[(x-1)+(y-1)*header->Width].G * mask[0][0] + oldMatrix[(x)+(y-1)*header->Width].G * mask[0][1] + oldMatrix[(x+1)+(y-1)*header->Width].G * mask[0][2] +
            oldMatrix[(x-1)+(y)*header->Width].G * mask[1][0] + oldMatrix[(x)+(y)*header->Width].G * mask[1][1] + oldMatrix[(x+1)+(y)*header->Width].G * mask[1][2] +
            oldMatrix[(x-1)+(y+1)*header->Width].G * mask[2][0] + oldMatrix[(x)+(y+1)*header->Width].G * mask[2][1] + oldMatrix[(x+1)+(y+1)*header->Width].G * mask[2][2];
        
            if(temp > -1 && temp < 256) {newMatrix[x+y*header->Width].G = temp;}
            else if(temp < 0) {newMatrix[x+y*header->Width].G = 0;}
            else {newMatrix[x+y*header->Width].G = 255;}

            temp = 
            oldMatrix[(x-1)+(y-1)*header->Width].B * mask[0][0] + oldMatrix[(x)+(y-1)*header->Width].B * mask[0][1] + oldMatrix[(x+1)+(y-1)*header->Width].B * mask[0][2] +
            oldMatrix[(x-1)+(y)*header->Width].B * mask[1][0] + oldMatrix[(x)+(y)*header->Width].B * mask[1][1] + oldMatrix[(x+1)+(y)*header->Width].B * mask[1][2] +
            oldMatrix[(x-1)+(y+1)*header->Width].B * mask[2][0] + oldMatrix[(x)+(y+1)*header->Width].B * mask[2][1] + oldMatrix[(x+1)+(y+1)*header->Width].B * mask[2][2];

            if(temp > -1 && temp < 256) {newMatrix[x+y*header->Width].B = temp;}
            else if(temp < 0) {newMatrix[x+y*header->Width].B = 0;}
            else {newMatrix[x+y*header->Width].B = 255;}

            newMatrix[x+y*header->Width].A = oldMatrix[x+y*header->Width].A;

            // newMatrix[x+y*header->Width].R = 255 - oldMatrix[x+y*header->Width].R;
            // newMatrix[x+y*header->Width].G = 255 - oldMatrix[x+y*header->Width].G;
            // newMatrix[x+y*header->Width].B = 255 - oldMatrix[x+y*header->Width].B;
            // newMatrix[x+y*header->Width].A = 255 - oldMatrix[x+y*header->Width].A;
        }
    }

    return newMatrix;
}

FILE * set_new_matrix(FILE * file, PIXEL * newMatrix)
{

    BMP_HEADER * header = get_header(file);

    if(header == NULL) return NULL;

    fseek(file, header->DataOffset, SEEK_SET);

    size_t rowLen = (size_t)((header->BitCount * header->Width + 31)/32)*4;
    size_t byteCount = rowLen*abs(header->Height);

    uint8_t * matrix = (uint8_t *)malloc(sizeof(uint8_t)*byteCount);
    
    if(header->BitCount == 32)
    {
        for(int i = 0; i < byteCount; i += 4)
        {
            matrix[i]   = newMatrix[i/4].R;
            matrix[i+1] = newMatrix[i/4].G; 
            matrix[i+2] = newMatrix[i/4].B;
            matrix[i+3] = newMatrix[i/4].A; 
        }
    }
    else if (header->BitCount == 24)
    {
        for(int i = 0; i < byteCount; i += 3)
        {
            matrix[i] = newMatrix[i/3].R;  
            matrix[i+1] = newMatrix[i/3].G; 
            matrix[i+2] = newMatrix[i/3].B; 
        }
    }

    fseek(file, header->DataOffset, SEEK_SET);
    
    fwrite(matrix, sizeof(uint8_t), byteCount, file);

    return file;
}

FILE * set_new_file(FILE * file, BMP_HEADER * header, PIXEL * newMatrix)
{
    fwrite(&header->Signature, sizeof(header->Signature), 1, file);
    fwrite(&header->FileSize, sizeof(header->FileSize), 1, file);
    fwrite(&header->reserved, sizeof(header->reserved), 1, file);
    fwrite(&header->DataOffset, sizeof(header->DataOffset), 1, file);

    fwrite(&header->Size, sizeof(header->Size), 1, file);
    fwrite(&header->Width, sizeof(header->Width), 1, file);
    fwrite(&header->Height, sizeof(header->Height), 1, file);
    fwrite(&header->Planes, sizeof(header->Planes), 1, file);
    fwrite(&header->BitCount, sizeof(header->BitCount), 1, file);
    fwrite(&header->Compression, sizeof(header->Compression), 1, file);
    fwrite(&header->ImageSize, sizeof(header->ImageSize), 1, file);
    fwrite(&header->XpixelsPerM, sizeof(header->XpixelsPerM), 1, file);
    fwrite(&header->YpixelsPerM, sizeof(header->YpixelsPerM), 1, file);
    fwrite(&header->ColorsUsed, sizeof(header->ColorsUsed), 1, file);
    fwrite(&header->ColorsImportant, sizeof(header->ColorsImportant), 1, file);

    size_t rowLen = (size_t)((header->BitCount * header->Width + 31)/32)*4;
    size_t byteCount = rowLen*abs(header->Height);
    fseek(file, header->DataOffset, SEEK_SET);
    if(header->BitCount == 24)
    {
        for(int i = 0; i < byteCount; i += 3)
        {
            fwrite(&newMatrix[i/3].R, sizeof(uint8_t), 1, file);
            fwrite(&newMatrix[i/3].G, sizeof(uint8_t), 1, file);
            fwrite(&newMatrix[i/3].B, sizeof(uint8_t), 1, file);
        }
    }
    if(header->BitCount == 32)
    {
        for(int i = 0; i < byteCount; i += 4)
        {
            fwrite(&newMatrix[i/4].R, sizeof(uint8_t), 1, file);
            fwrite(&newMatrix[i/4].G, sizeof(uint8_t), 1, file);
            fwrite(&newMatrix[i/4].B, sizeof(uint8_t), 1, file);
            fwrite(&newMatrix[i/4].A, sizeof(uint8_t), 1, file);
        }
    }
    return file;
}