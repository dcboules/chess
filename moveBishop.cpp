#include "moveBishop.hpp"

#include <cstdint>
#include <stdlib.h>

bool MoveBishop::testMove(uint64_t position, uint64_t newMove, uint64_t playerState, uint64_t boardState) const {
    
    int x1 = getColumn(position);
    int y1 = getRow(position);
    
    int x2 = getColumn(newMove);
    int y2 = getRow(newMove);
    
    if ((newMove & playerState) == 0) {  
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
