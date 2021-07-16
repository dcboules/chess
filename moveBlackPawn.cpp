#include "moveBlackPawn.hpp"
#include <math.h> 
#include <cstdint>

bool MoveBlackPawn::testMove(uint64_t position, uint64_t newMove, uint64_t playerState, uint64_t boardState) const {
    if ((newMove & playerState) == 0 && ((position >> 8) & boardState) == 0) {
        if (newMove == position >> 8) {
            return true;
        }
        else if ((newMove == (position >> 16)) && (position >= pow(2,48)) && ((position >> 8) & boardState) == 0) {
            return true; //if in starting position the pawn can move two squares
        }
        else if (newMove == (position >> 7) && ((position >> 7) & boardState) != 0) { //diagonal captures
            return true;
        }
        else if (newMove == (position >> 9) && ((position >> 9) & boardState) != 0) { //diagonal captures
            return true;
        }
    }
    return false;
}