CMAKE_MINIMUM_REQUIRED(VERSION 3.7)

ADD_SUBDIRECTORY(googletest)

SET(CMAKE_CXX_STANDARD 11)

project(MonkeyChess)

ADD_EXECUTABLE(test
    tests/unit_test.cpp
    
    board.cpp
    moveBishop.cpp
    moveBlackPawn.cpp
    moveFactory.cpp
    moveKing.cpp
    moveKnight.cpp
    moveQueen.cpp
    moveRook.cpp
    moveWhitePawn.cpp
    piece.cpp
    player.cpp
)

#[[ADD_EXECUTABLE(main
    
    board.cpp
    cmd_main.cpp
    moveBishop.cpp
    moveBlackPawn.cpp
    moveFactory.cpp
    moveKing.cpp
    moveKnight.cpp
    moveQueen.cpp
    moveRook.cpp
    moveWhitePawn.cpp
    piece.cpp
    player.cpp
)
]]

ADD_COMPILE_OPTIONS(-std=c++0x)
TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)
