#include "moveFactory.hpp"

#include "moveBlackPawn.hpp"
#include "moveWhitePawn.hpp"
#include "moveRook.hpp"
#include "moveKnight.hpp"
#include "moveBishop.hpp"
#include "moveQueen.hpp"
#include "moveKing.hpp"

Move* MoveFactory::createMoveStrategy(int type, int team) { //0 = pawn, 1 = rook, 2 = knight, 3 = bishop, 4 = queen, 5 = king 
    switch(type) {
        case 0:
            if (team == 0) { //black
                return new MoveBlackPawn(); //works
            }
            else if (team == 1) { //white
                return new MoveWhitePawn(); //works
            }
            else {
                return nullptr;
            }
            break;
            
        case 1:
            return new MoveRook(); //works
            break;
            
        case 2:
            return new MoveKnight(); //works
            break;
            
        case 3:
            return new MoveBishop(); //works
            break;
            
        case 4:
            return new MoveQueen(); //works
            break;
            
        case 5:
            return new MoveKing(); //works
            break;
        
        default:
            return nullptr;
            break;
    }
}