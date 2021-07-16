#ifndef __MOVEBLACKPAWN_HPP__
#define __MOVEBLACKPAWN_HPP__

#include "move.hpp"
#include <cstdint>

class MoveBlackPawn: public Move {
    public:
        bool testMove(uint64_t position, uint64_t newMove, uint64_t playerState, uint64_t boardState) const;
};

#endif