#ifndef __WPAWN_TEST_HPP__
#define __WPAWN_TEST_HPP__

#include "../piece.hpp"
#include <math.h>

TEST(WhitePawnTest, testPosition) {
    Piece p(0, 1, 0b1);
    EXPECT_EQ(0b1, p.getPosition());
}

TEST(WhitePawnTest, possibleMoves) {
    Piece p(0, 1, 0b1);
    EXPECT_EQ(static_cast<uint64_t>(pow(2, 8)) | static_cast<uint64_t>(pow(2, 16)), p.getAllValidMoves(0b1, 0b1));
}

#endif
