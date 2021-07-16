#ifndef __BOARD_TEST_HPP__
#define __BOARD_TEST_HPP__

#include "../board.hpp"

TEST(TestBoard, testGetBoardState) {
    Board b;
    uint64_t testNum = 0xffff;
    testNum |= testNum << 48; 
    EXPECT_EQ(testNum, b.getBoardState());
}

#endif
