#ifndef __MOVEFACTORY_HPP__
#define __MOVEFACTORY_HPP__

#include "move.hpp"

class MoveFactory {
    public:
        Move* createMoveStrategy(int type, int team); 
    /*
    Type: 0 = pawn, 1 = rook, 2 = knight, 3 = bishop, 4 = queen, 5 = king 
    Team: 0 = black, 1 = white
    */
};

#endif