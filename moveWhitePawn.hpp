#ifndef __MOVEWHITEPAWN_HPP__
#define __MOVEWHITEPAWN_HPP__

#include "move.hpp"
#include <cstdint>

class MoveWhitePawn: public Move {
    public:
        bool testMove(uint64_t position, uint64_t newMove, uint64_t playerState, uint64_t boardState) const;
};

#endif
