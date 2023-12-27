#include <stdlib.h>
#include <time.h>
#include "../IPD.h"

// Randomly cooperates and defects
__declspec(dllexport) int turn(int *result, int indexOfGame)
{
    return rand() % 2;
}