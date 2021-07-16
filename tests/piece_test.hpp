#ifndef __PIECE_TEST_HPP__
#define __PIECE_TEST_HPP__

#include "../piece.hpp"

TEST(TestPiece, testIsCaptured) {
    Piece p(0, 0, 1);
    p.becomeCaptured();

    EXPECT_EQ(true, p.isCaptured());
}

TEST(TestPiece, testType) {
    Piece p(1, 0, 1);

    EXPECT_EQ(1, p.getType());
}

#endif
