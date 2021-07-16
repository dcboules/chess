#ifndef __MOVEKING_HPP__
#define __MOVEKING_HPP__

#include "move.hpp"
#include <cstdint>

class MoveKing: public Move {
    public:
        bool testMove(uint64_t position, uint64_t newMove, uint64_t playerState, uint64_t boardState) const;
};

#endif