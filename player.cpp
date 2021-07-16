#include "player.hpp"

#include <cstdint>
#include <math.h>

Player::Player(int team) {
    this->team = team;
    uint64_t pos;
    
    for (int i = 0; i < 16; i++) { //create pieces
        if (team == 0) {
            pos = pow(2, (63 - i));
        }
        else {
            pos = pow(2, i);
        }
        
        if (i == 0 || i == 7) {
            pieces[i] = new Piece(1, team, pos); //rook
        }
        else if (i == 1 || i == 6) {
            pieces[i] = new Piece(2, team, pos); //knight
        }
        else if (i == 2 || i == 5) {
            pieces[i] = new Piece(3, team, pos); //bishop
        }
        else if ((i == 3 && team == 0) || (i == 4 && team == 1)) {
            pieces[i] = new Piece(4, team, pos); //queen
        }
        else if ((i == 3 && team == 1) || (i == 4 && team == 0)) {
            pieces[i] = new Piece(5, team, pos); //king
        }
        else {
            pieces[i] = new Piece(0, team, pos); //pawn
        }
    }
    
    updateBoardState();
}

Player::~Player() {
    for (int i = 0; i < 16; i++) {
        if (pieces[i] != nullptr) {
            delete pieces[i];
        }
    }
}

void Player::updateBoardState() {
    this->boardstate = 0;
    
    for (int i = 0; i < 16; i++) {
        this->boardstate |= pieces[i]->getPosition();
    }
}

uint64_t Player::getBoardState() const {
    return this->boardstate;
}

bool Player::makeMove(uint64_t piecePosition, uint64_t newPosition, uint64_t wholeBoardState) {
    bool valid = false;
    
    for (int i = 0; i < 16; i++) { //find if there is a piece at x position
        if (pieces[i]->getPosition() == piecePosition) {
            valid = pieces[i]->makeMove(newPosition, this->boardstate, wholeBoardState);
            this->updateBoardState();
        }
    }
    return valid;
} //returns true if the move was made and false otherwise

void Player::testCaptures(Player* enemy) { //set a piece to captured if it coincides with enemy position
    for (int i = 0; i < 16; i++) {
        if ((pieces[i]->getPosition() & enemy->getBoardState()) != 0) {
            pieces[i]->becomeCaptured();
        }
    }
}

uint64_t Player::getAllValidMoves(uint64_t wholeBoardState) const {
  uint64_t allmoves = 0;
  for (int i = 0; i< 16; i++) {
    allmoves |= pieces[i]->getAllValidMoves(this->boardstate, wholeBoardState);
  }
  
  return allmoves;
}

bool Player::testCheck(Player* enemy, uint64_t wholeBoardState) const {
    uint64_t kingPos;
  
    if (team == 0) { //set king index based on position
        kingPos = pieces[4]->getPosition();
    }
    else {
        kingPos = pieces[3]->getPosition();
    }
    
    if ((enemy->getAllValidMoves(wholeBoardState) & kingPos) != 0) {
        return true;
    }
    
    return false;
}

bool Player::kingIsCaptured() const {
    if (team == 0 && pieces[4]->getPosition() == 0) {
        return true;
    }
    else if (team == 1 && pieces[3]->getPosition() == 0) {
        return true;
    }
    
    return false;
}

int Player::getPieceAt(uint64_t piecePosition) const {
    for (int i = 0; i< 16; i++) {
        if (pieces[i]->getPosition() == piecePosition) {
            return pieces[i]->getType();
        }
    }
    
    return -1;
}