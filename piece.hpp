#ifndef __PIECE_HPP__
#define __PIECE_HPP__

#include "move.hpp"
#include <cstdint>

class Board;

class Piece {
    private:
        Move* moveStrategy; 
        int type; //0 = pawn, 1 = rook, 2 = knight, 3 = bishop, 4 = queen, 5 = king
        int team; //0 = black, 1 = white
        uint64_t position; //position states are stored as a 64 bit number with one bit for each square
        bool captured;
    
    public:
    	Piece(int type, int team, uint64_t startPos);
        ~Piece();
        bool testMove(uint64_t newPosition, uint64_t playerState, uint64_t boardState) const;
        bool makeMove(uint64_t newPosition, uint64_t playerState, uint64_t boardState);
        uint64_t getAllValidMoves(uint64_t playerState, uint64_t boardState) const;
        //bool testCheck() const; //test if piece is in check (move this to player)
        
        uint64_t getPosition() const;
        bool isCaptured() const;
        void becomeCaptured();
        
        int getType() const;
};

#endif
