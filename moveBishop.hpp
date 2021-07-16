#ifndef __MOVEBISHOP_HPP__
#define __MOVEBISHOP_HPP__

#include <cstdint>

#include "move.hpp"

class MoveBishop: public Move {
    public:
        bool testMove(uint64_t position, uint64_t newMove, uint64_t playerState, uint64_t boardState) const;
};

#endif
