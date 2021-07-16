#ifndef __PLAYER_TEST_HPP___
#define __PLAYER_TEST_HPP__

#include "../player.hpp"

TEST(TestPlayer, testBoardState) {
    Player p(1); //white
    EXPECT_EQ(0xffff, p.getBoardState()); 
}

TEST(TestPlayer, testAllValidMoves) {
    Player p(1);
    EXPECT_EQ(0xffff0000, p.getAllValidMoves(0xffff));
}

TEST(TestPlayer, testGetPiece) {
    Player p(1);
    EXPECT_EQ(1, p.getPieceAt(1));
}

TEST(TestPlayer, testKingCaptured) {
    Player p(1);
    EXPECT_EQ(false, p.kingIsCaptured());
}

#endif
