#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "piece.hpp"
#include <cstdint>

class Player {
    private:
        uint64_t boardstate;
        Piece* pieces[16] = {nullptr}; 
        int team;
        
    public:
        Player(int team);
        ~Player();
        
        void updateBoardState();
        uint64_t getBoardState() const;
        bool makeMove(uint64_t piecePosition, uint64_t newPosition, uint64_t boardState);
        void testCaptures(Player* enemy);
        uint64_t getAllValidMoves(uint64_t wholeBoardState) const;
        bool testCheck(Player* enemy, uint64_t wholeBoardState) const;
        bool kingIsCaptured() const;
        int getPieceAt(uint64_t piecePosition) const;
};

#endif
