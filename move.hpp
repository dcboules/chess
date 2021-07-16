#ifndef __MOVE_HPP__
#define __MOVE_HPP__

#include <math.h>
#include <cstdint>

class Move {
    protected:
        int getColumn(uint64_t position) const { //zero-indexed
            return (static_cast<int>(log2(position)) % 8);
        }
        
        int getRow(uint64_t position) const {
            return static_cast<int>(log2(position) / 8);
        }
        
        uint64_t cartesianToBitmask(int column, int row) const {
            if ((column < 0) | (column > 7) | (row < 0) | (row > 7)) { //return 0 if out of bounds
                return 0;
            }
            
            return pow(2, ((row * 8) + column));
        }
    
        //cast a ray from start to end and return false if there is a collision
        bool raycast(uint64_t start, uint64_t end, int slope, uint64_t boardstate) const {
            int i = 1;
            if (end < start) { //>>
                while (start >> (slope * i) != end) {
                    if ((start >> (slope * i) & boardstate) != 0) { //if they collide
                        return false;
                    }
                    i++;
                }
            }
            else { //<<
                while (start << (slope * i) != end) {
                    if ((start << (slope * i) & boardstate) != 0) { //if they collide
                        return false;
                    }
                    i++;
                }
            }
            return true;
        }
    
    public:
        virtual bool testMove(uint64_t position, uint64_t newMove, uint64_t playerState, uint64_t boardState) const = 0;
};

#endif
