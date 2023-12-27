#include "../IPD.h"

// Always cooperates
__declspec(dllexport) int turn(int *result, int indexOfGame)
{
    return 1;
}