#include "moveKnight.hpp"
#include <cstdint>

bool MoveKnight::testMove(uint64_t position, uint64_t newMove, uint64_t playerState, uint64_t boardState) const {
    int magicNumbers[8][2] = {{2,1},{1,2},{-1,2},{-2,1},{2,-1},{1,-2},{-1,-2},{-2,-1}};
    
    /*
    if ((newMove & playerState) == 0) { //disallow move if it would land on a friendly piece
        for (int i = 0; i < 4; i++) {
            if (newMove == position << magicNumbers[i]) {
                return true;
            }
            else if (newMove == position >> magicNumbers[i]) {
                return true;
            }
        }
    }
    */
    
    if ((newMove & playerState) == 0) { //disallow move if it would land on a friendly piece
        for (int i = 0; i < 8; i++) {
            if (newMove == cartesianToBitmask(getColumn(position) + magicNumbers[i][0], getRow(position) + magicNumbers[i][1])) {
                return true;
            }
        }
    }
    
    return false;
}
