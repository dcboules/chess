#include "piece.hpp"
#include "moveFactory.hpp"

#include <cstdint>
#include <iostream>

Piece::Piece(int type, int team, uint64_t startPos) {
    this->type = type;
    this->team = team;
    this->position = startPos;
    
    MoveFactory factory;
    this->moveStrategy = factory.createMoveStrategy(type, team);
    
    this->captured = false;
}

Piece::~Piece() {
    delete moveStrategy;
}

bool Piece::testMove(uint64_t newPosition, uint64_t playerState, uint64_t boardState) const {
    if (moveStrategy->testMove(position, newPosition, playerState, boardState)) {
        return true;
    }
    return false;
}

bool Piece::makeMove(uint64_t newPosition, uint64_t playerState, uint64_t boardState) {
    if (testMove(newPosition, playerState, boardState)) {
        this->position = newPosition;
        return true;
    }
    return false;
}

uint64_t Piece::getAllValidMoves(uint64_t playerState, uint64_t boardState) const {
    uint64_t allMoves = 0;
    const uint64_t literalOne = 1;
    
    for (uint64_t i = 0; i < 64; i++) {
        if (testMove((literalOne << i), playerState, boardState)) {
            allMoves |= (literalOne << i);
        }
    }
    
    return allMoves;
}

uint64_t Piece::getPosition() const {
    return this->position;
}

bool Piece::isCaptured() const {
    return this->captured;
}

void Piece::becomeCaptured() {
    this->position = 0; //effectively remove from board
    this->captured = true;
}

int Piece::getType() const {
    return this->type;
}