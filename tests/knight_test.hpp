#ifndef __KNIGHT_TEST_HPP__
#define __KNIGHT_TEST_HPP__

#include "../piece.hpp"
#include <math.h>

TEST(KnightTest, testPosition){
   Piece p(2, 0, 0x8000000);
   EXPECT_EQ(0X8000000, p.getPosition());
}

TEST(KnightTest, possibleMoves){
	Piece p(2, 0, 0x8000000);
	EXPECT_EQ(22136263676928, p.getAllValidMoves(0x8000000,0x8000000));

}
#endif
