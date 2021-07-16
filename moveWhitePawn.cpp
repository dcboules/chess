#include "moveWhitePawn.hpp"

#include <cstdint>

bool MoveWhitePawn::testMove(uint64_t position, uint64_t newMove, uint64_t playerState, uint64_t boardState) const {
    if ((newMove & playerState) == 0) { //disallow move if it would land on a friendly piece
        if (newMove == (position << 8) && ((position << 8) & boardState) == 0) {
            return true;
        }
        else if ((newMove == (position << 16)) && (position < 65536) && ((position << 8) & boardState) == 0) { //if no collision in the next cell
            return true; //if in starting position the pawn can move two squares
        }
        else if (newMove == (position << 7) && ((position << 7) & boardState) != 0) { //diagonal captures
            return true;
        }
        else if (newMove == (position << 9) && ((position << 9) & boardState) != 0) { //diagonal captures
            return true;
        }
    }    
    
    return false;
}