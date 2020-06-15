#include "competition.h"

bool Competition::operator==(const Competition &rhs) const
{
    if (date == rhs.date && prizePool == rhs.prizePool && jackpot == rhs.jackpot)
        return true;
    return false;
}
