#include "../IPD.h"

// Cooperates until betrayed, and then defects for the rest of the match
__declspec(dllexport) int turn(int *result, int indexOfGame)
{
    if (indexOfGame != 0 && result[indexOfGame - 1] != 3)
    {
        return 0;
    }
    return 1;
}
