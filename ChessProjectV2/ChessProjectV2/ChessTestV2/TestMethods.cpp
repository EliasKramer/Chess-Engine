#include "TestMethods.h"

bool moveListContains(Move m, const UniqueMoveList& moves)
{
    for (const std::unique_ptr<Move>& currMoveToCheck : moves)
    {
        if (*currMoveToCheck == m)
        {
            return true;
        }
    }
    return false;
}
