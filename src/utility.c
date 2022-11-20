#include <string.h>
#include <stdlib.h>

char * createNewFileName(char *argv[])
{
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

    return newFileName;
}