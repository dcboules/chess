#include "gtest/gtest.h"

#include "wpawn_test.hpp"
#include "bpawn_test.hpp"
#include "knight_test.hpp"
#include "rook_test.hpp"
#include "queen_test.hpp"
#include "king_test.hpp"
#include "bishop_test.hpp"
#include "piece_test.hpp"
#include "player_test.hpp"
#include "board_test.hpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
