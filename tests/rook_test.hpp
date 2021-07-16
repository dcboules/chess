#ifndef __ROOK_TEST_HPP__
#define __ROOK_TEST_HPP__

#include "../piece.hpp"
#include <math.h>

TEST(RookTest, testPosition){
   Piece p(1, 0, 0x8000000);
   EXPECT_EQ(0X8000000, p.getPosition());
}
TEST(RookTest, possibleMoves) {
    Piece p(1, 0,static_cast<uint64_t>(pow(2,27)));
    EXPECT_EQ(578721386714368008, p.getAllValidMoves(static_cast<int>(pow(2,27)), static_cast<int>(pow(2,27))));
}
#endif
