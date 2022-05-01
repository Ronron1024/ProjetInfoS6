#include <stdlib.h>

int randInt(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

int getPlateauId()
{
    static int id = 0;
    return id++;
}