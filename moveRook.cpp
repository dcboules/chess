#include "moveRook.hpp"
#include <math.h> 
#include <cstdint>

bool MoveRook::testMove(uint64_t position, uint64_t newMove, uint64_t playerState, uint64_t boardState) const {
    
    if ((newMove & playerState) == 0) { 
        for (int i = 1; i < 8 - getRow(position); i++) { //+y
            if (newMove == position << (8 * i) && raycast(position, newMove, 8, boardState)) {
                return true;
            }
        }
        
        for (int i = 1; i <= getRow(position); i++) { //-y
            if (newMove == position >> (8 * i) && raycast(position, newMove, 8, boardState)) {
                return true;
            }
        }
        
        for (int i = 1; i < 8 - getColumn(position); i++) { //+x
            if (newMove == position << (1 * i) && raycast(position, newMove, 1, boardState)) {
                return true;
            }
        }
        
        for (int i = 1; i <= getColumn(position); i++) { //-y
            if (newMove == position >> (1 * i) && raycast(position, newMove, 1, boardState)) {
                return true;
            }
        }
    }
    
    return false;
}