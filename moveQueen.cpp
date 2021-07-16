#include "moveQueen.hpp"
#include <math.h> 
#include <cstdint>
#include <stdlib.h>

#include <iostream>

bool MoveQueen::testMove(uint64_t position, uint64_t newMove, uint64_t playerState, uint64_t boardState) const {
    int x1 = getColumn(position);
    int y1 = getRow(position);
    
    int x2 = getColumn(newMove);
    int y2 = getRow(newMove);
    /*
    for (int i = 1; i < 8; i++) { 
        for (int j = 0; j < 4; i++) {
            if ((newMove == (position << (magicNumbers[j] * i))) && raycast(position, newMove, magicNumbers[j], boardState)) {
                return true;
            }
            else if ((newMove == (position >> (magicNumbers[j] * i))) && raycast(position, newMove, magicNumbers[j], boardState)) {
                return true;
            }
        }
    }
    */
    
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
        
        if ((abs(x2 - x1) == abs(y1 - y2)) && (abs(y1 - y2) > 0)) {
            if (((x1 < x2) && (y1 < y2)) || ((x1 > x2) && (y1 > y2))) {
                if (raycast(position, newMove, 9, boardState)) {
                    return true;
                }
            }
            else {
                if (raycast(position, newMove, 7, boardState)) {
                    return true;
                }
            }
        }
    }
    
    
    return false;
}