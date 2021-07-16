#include "board.hpp"
#include "player.hpp"

#include <cstdint>
#include <iostream>
#include <math.h>

Board::Board() {
    this->white = new Player(1);
    this->black = new Player(0);

    this->updateBoardState();
}

Board::~Board() {
    delete this->white;
    delete this->black;
}

uint64_t Board::cartesianToBitmask(int column, int row) const {
    if ((column < 0) | (column > 7) | (row < 0) | (row > 7)) { //return 0 if out of bounds
        return 0;
    }
            
    return pow(2, ((row * 8) + column));
}

void Board::updateBoardState() {
    this->boardstate = white->getBoardState() | black->getBoardState();
}

uint64_t Board::getBoardState() const {
    return this->boardstate;
}

void Board::drawDebugBoard() const {
    char output;
    
    std::cout << "-------- " << std::endl;
    for (int i = 63; i >= 0; i--) {
        //output = '#';
        
        if (((i / 8) + (i % 8)) % 2 == 1) {
            output = 176;
        }
        else {
            output = 178;
        }
        
        switch(white->getPieceAt(pow(2,i))) {
            case 0:
                output = 'p';
                break;
            case 1:
                output = 'r';
                break;
            case 2:
                output = 'n';
                break;
            case 3:
                output = 'b';
                break;
            case 4:
                output = 'q';
                break;
            case 5:
                output = 'k';
                break;
        }
        
        switch(black->getPieceAt(pow(2,i))) {
            case 0:
                output = 'P';
                break;
            case 1:
                output = 'R';
                break;
            case 2:
                output = 'N';
                break;
            case 3:
                output = 'B';
                break;
            case 4:
                output = 'Q';
                break;
            case 5:
                output = 'K';
                break;
        }
        
        std::cout << output;
        
        if (i % 8 == 0) {
            std::cout << "|" << (i / 8) << std::endl;
        }
    }
    std::cout << "-------- " << std::endl;
    std::cout << "76543210 " << std::endl;
}

bool Board::GUIinputMove(int team, int startX, int startY, int endX, int endY) {
    uint64_t scoord = cartesianToBitmask(startX, startY);
    uint64_t ecoord = cartesianToBitmask(endX, endY);
    
    if (team == 0) {
        return black->makeMove(scoord, ecoord, this->boardstate);
    }
    else {
        return white->makeMove(scoord, ecoord, this->boardstate);
    }
}

bool Board::inputMove(int team) {
    char srow;
    char scol;
    
    char erow;
    char ecol;
    
    uint64_t scoord;
    uint64_t ecoord;
    
    std::cout << "Input starting position: ";
    std::cin >> scol >> srow;
    
    std::cout << "Input destination: ";
    std::cin >> ecol >> erow;
    std::cout << std::endl;
    
    scoord = cartesianToBitmask(static_cast<int>(scol) - 48, static_cast<int>(srow) - 48);
    ecoord = cartesianToBitmask(static_cast<int>(ecol) - 48, static_cast<int>(erow) - 48);
    
    if (team == 0) {
        return black->makeMove(scoord, ecoord, this->boardstate);
    }
    else {
        return white->makeMove(scoord, ecoord, this->boardstate);
    }
}

bool Board::gameOver() const {
    if (white->getAllValidMoves(boardstate) == 0) { 
        return true;
    }
    
    if (black->getAllValidMoves(boardstate) == 0) {
        return true;
    }
    
    if (white->kingIsCaptured() || black->kingIsCaptured()) {
        return true;
    }
        
    return false;
}

void Board::runTerminalGame() {
    int team = 0;

    while (!gameOver()) {
        drawDebugBoard();
        
        if (inputMove(team)) {
            switch(team) {
                case 0:
                    white->testCaptures(black);
                    team = 1;
                    std::cout << "white's move" << std::endl;
                    break;
                case 1:
                    black->testCaptures(white);
                    team = 0;
                    std::cout << "black's move" << std::endl;
                    break;
            }
        }
        else {
            std::cout << "invalid move" << std::endl;
        }
        
        updateBoardState();
    }
}
