#include "TestMethods.h"

bool moveListContains(Move m, const MoveList& moves)
{
    for (const Move currMoveToCheck : moves)
    {
        if (currMoveToCheck == m)
        {
            return true;
        }
    }
    return false;
}
