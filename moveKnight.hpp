#ifndef __MOVEKNIGHT_HPP__
#define __MOVEKNIGHT_HPP__

#include "move.hpp"
#include <cstdint>

class MoveKnight: public Move {
    public:
        bool testMove(uint64_t position, uint64_t newMove, uint64_t playerState, uint64_t boardState) const;
};

#endif