#ifndef __QUEEN_TEST_HPP__
#define __QUEEN_TEST_HPP__

#include "../piece.hpp"
#include <math.h>

TEST(QueenTest, testPosition){
   Piece p(4, 1, 0x8000000);
   EXPECT_EQ(0x8000000, p.getPosition());
}
TEST(QueenTest, possibleMoves) {
    Piece p(4, 1,0x8000000);
    EXPECT_EQ(static_cast<uint64_t>(9820426766351346249), p.getAllValidMoves(0x8000000,0x8000000));
}
#endif
