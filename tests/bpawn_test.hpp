#ifndef __BPAWN_TEST_HPP__
#define __BPAWN_TEST_HPP__

#include "../piece.hpp"
#include <math.h>
TEST(BlackPawnTest, testPosition) {
    Piece p(0, 0, 0x1000000000000);
    EXPECT_EQ(0x1000000000000, p.getPosition());
}

TEST(BlackPawnTest, possibleMoves) {
    Piece p(0, 0, static_cast<uint64_t>(pow(2,63)));
    EXPECT_EQ(static_cast<uint64_t>(pow(2, 55)) | static_cast<uint64_t>(pow(2, 47)), p.getAllValidMoves(static_cast<uint64_t>(pow(2,63)), static_cast<uint64_t>(pow(2,63))));
}
#endif
