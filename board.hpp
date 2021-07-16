#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include <cstdint>

#include "player.hpp"

class Board {
    private:
        Player* white;
        Player* black;
        
        uint64_t boardstate;
    
    protected:
        uint64_t cartesianToBitmask(int column, int row) const;
    
    public:
        Board();
        ~Board();
        
        void updateBoardState();
        uint64_t getBoardState() const;
        void drawDebugBoard() const;
        bool GUIinputMove(int team, int startX, int startY, int endX, int endY);
        bool inputMove(int team);
        bool gameOver() const;
        void runTerminalGame();
};

#endif