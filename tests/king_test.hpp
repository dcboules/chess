#ifndef __KING_TEST_HPP__
#define __KING_TEST_HPP__

#include "../piece.hpp"

TEST(KingTest, testPosition){
   Piece p(5, 0, 0x8000000);
   EXPECT_EQ((0x8000000), p.getPosition());
}
TEST(KingTest, possibleMoves){
	Piece p(5, 0, static_cast<uint64_t>(pow(2,27)));
	EXPECT_EQ(120596463616,  p.getAllValidMoves(0x8000000, 0x8000000));
}
#endif
