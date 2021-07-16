#include "../header/gui_board.hpp"
//#include "../../backend/header/player.hpp"

#include <cstdint>
#include <iostream>
#include <math.h>

GUI_Board::GUI_Board() {
    this->white = new Player(1);
    this->black = new Player(0);

    this->updateBoardState();
}
GUI_Board::~GUI_Board() {
    delete white;
    delete black;

    for (int i = 0; i < 64; i++) {
        if (white_pieces[i] != nullptr) {
            white_pieces[i]->clean();
            delete white_pieces[i];
        } 
        if (black_pieces[i] != nullptr) {
            black_pieces[i]->clean();
            delete black_pieces[i];
        }
    }
    if (pieceMoving) delete pieceMoving;

    clean();
    //if (chessBoard) delete chessBoard;
    //if (window) delete window;
    //if (renderer) delete renderer;
}
uint64_t GUI_Board::cartesianToBitmask(int column, int row) const {
    if ((column < 0) | (column > 7) | (row < 0) | (row > 7)) { //return 0 if out of bounds
        return 0;
    }
            
    return pow(2, ((row * 8) + column));
}
void GUI_Board::updateBoardState() {
    this->boardstate = white->getBoardState() | black->getBoardState();
}
uint64_t GUI_Board::getBoardState() const {
    return this->boardstate;
}
void GUI_Board::runGame() {
    init(SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,800);


    while (!gameOver() && isRunning) {
        
        handleEvents();
        update();
        render();
        
        updateBoardState();
    }
    
}

//From Chess Game
void GUI_Board::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    int mX, mY;
    SDL_GetMouseState(&mX, &mY);
    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_MOUSEBUTTONDOWN:
            if (pieceMoved) {
                mX /= PIECE_W;
                mY = mY/PIECE_H;
                mouseX /= PIECE_W;
                mouseY = mouseY/PIECE_H;

                if (makeMove(team, mouseX, 7-mouseY, mX, 7-mY)) {
                    int index = 8*(mY) + mX;
                    pieceMoving->setX(mX*PIECE_W);
                    pieceMoving->setY((mY)*PIECE_H);
                    switch(team) {
                        case 0:
                            white->testCaptures(black);
                            //if capture update board w/ capture
                            
                            if (white_pieces[index]) {
                                delete white_pieces[index];
                                white_pieces[index] = nullptr;
                            }
                            
                            black_pieces[index] = pieceMoving;
                            pieceMoving = nullptr;
                            team = 1;
                            std::cout << "white's move" << std::endl;
                            break;
                        case 1:
                            black->testCaptures(white);
                            
                            if (black_pieces[index]) {
                                delete black_pieces[index];
                                black_pieces[index] = nullptr;
                            }
                            white_pieces[index] = pieceMoving;

                            pieceMoving = nullptr;
                            team = 0;
                            std::cout << "black's move" << std::endl;
                            break;
                    }
                }
                else {
                    int index = 8*(mouseY) + mouseX;
                    pieceMoving->setX(mouseX*PIECE_W);
                    pieceMoving->setY(mouseY*PIECE_H);
                    if (team == 1) white_pieces[index] = pieceMoving;
                    else black_pieces[index] = pieceMoving;

                    pieceMoving = nullptr;

                }
                pieceMoved = false;
            }
            else {
                SDL_GetMouseState(&mouseX, &mouseY);
                for (int i = 0; i < 64; i++) {
                    if (collision(mouseX,mouseY,white_pieces[i])) {
                        pieceMoved = true;
                        pieceMoving = white_pieces[i];
                        white_pieces[i] = nullptr;
                    }
                    else if (collision(mouseX,mouseY,black_pieces[i])) {
                        pieceMoved = true;
                        pieceMoving = black_pieces[i];
                        black_pieces[i] = nullptr;
                    }
                }
            }
            break;
            
        case SDL_MOUSEMOTION:
            if (pieceMoved) {
                int newMX, newMY;
                SDL_GetMouseState(&newMX, &newMY);
                int currX = pieceMoving->getRect().x + (newMX - mX);
                int currY = pieceMoving->getRect().y + (newMY - mY);
                pieceMoving->setX(newMX-50);
                pieceMoving->setY(newMY-50);
                pieceMoving->update();
            }
            break;
        default:
            break;
    }
}

void GUI_Board::init(int x, int y, int w, int h) {
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Initializing..." << std::endl;
        window = SDL_CreateWindow("Monkey Chess", x,y,w,h,0);
        if (window) std::cout << "Window in..." << std::endl;
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            std::cout << "Renderer in..." << std::endl;
            SDL_SetRenderDrawColor(renderer, 255,255,255,255);

        }
        isRunning = true;
        team = 1;
        
        chessBoard = TextureManager::load_Texture("GUI/img/chessboard2.png", renderer);
        windowRect.x = 0;
        windowRect.y = 0;
        windowRect.w = w;
        windowRect.h = h;
        
        int pos = 0;
        PIECE_W = w/8;
        PIECE_H = h/8;

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                int currPiece = white->getPieceAt(cartesianToBitmask(j,7-i));
                if (currPiece != -1) {
                    const char* currPieceImg = "GUI/img/pawn2.png";
                    switch (currPiece) {
                        case 0: 
                            currPieceImg = "GUI/img/white_pawn.png";
                            break;
                        case 1: 
                            currPieceImg = "GUI/img/white_rook.png";
                            break;
                        case 2:
                            currPieceImg = "GUI/img/white_knight.png";
                            break;
                        case 3:
                            currPieceImg = "GUI/img/white_bishop.png";
                            break;
                        case 4:
                            currPieceImg = "GUI/img/white_queen.png";
                            break;
                        case 5:
                            currPieceImg = "GUI/img/white_king.png";
                            break;
                        default:
                            break;
                    }
                    white_pieces[8*(i) + j] = new GameObject(currPieceImg, renderer, PIECE_W, PIECE_H);
                    if (white_pieces[8*(i) + j]) {
                        white_pieces[8*(i) + j]->setX(PIECE_W*j);
                        white_pieces[8*(i) + j]->setY(PIECE_H*i);
                        white_pieces[8*(i) + j]->update();
                    }
                }
                else white_pieces[8*(i) + j] = nullptr;

                currPiece = black->getPieceAt(cartesianToBitmask(j,7-i));
                if (currPiece != -1) {
                    const char* currPieceImg = "GUI/img/pawn2.png";
                    switch (currPiece) {
                        case 0: 
                            currPieceImg = "GUI/img/black_pawn.png";
                            break;
                        case 1: 
                            currPieceImg = "GUI/img/black_rook.png";
                            break;
                        case 2:
                            currPieceImg = "GUI/img/black_knight.png";
                            break;
                        case 3:
                            currPieceImg = "GUI/img/black_bishop.png";
                            break;
                        case 4:
                            currPieceImg = "GUI/img/black_queen.png";
                            break;
                        case 5:
                            currPieceImg = "GUI/img/black_king.png";
                            break;
                        default:
                            break;
                    }
                    black_pieces[8*(i) + j] = new GameObject(currPieceImg, renderer, PIECE_W, PIECE_H);
                    if (black_pieces[8*(i) + j]) {
                        black_pieces[8*(i) + j]->setX(PIECE_W*j);
                        black_pieces[8*(i) + j]->setY(PIECE_H*i);
                        black_pieces[8*(i) + j]->update();
                        
                    }
                    else black_pieces[8*(i) + j] = nullptr;
                }
                else black_pieces[8*(i) + j] = nullptr;
            }
        }
    }
    else {
        std::cout << "Bad things happened" << std::endl;
        isRunning = false;
    }
}
void GUI_Board::update() {
    for(GameObject* o : white_pieces) {
        if (o) o->update();
    }
    for(GameObject* o : black_pieces) {
        if (o) o->update();
    }
    if (pieceMoving) pieceMoving->update();
}
void GUI_Board::render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, chessBoard, NULL, &windowRect);

    for(GameObject* o : white_pieces) {
        if (o) o->render();
    }
    for(GameObject* o : black_pieces) {
        if (o) o->render();
    }
    if (pieceMoving) pieceMoving->render();

    SDL_RenderPresent(renderer);
}
void GUI_Board::clean() {
    SDL_DestroyTexture(chessBoard);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
//Helpers
bool GUI_Board::collision(int x, int y, GameObject* o) {
    if (!o) return false;
    SDL_Rect temp = o->getRect();
    if (x > temp.x && x < temp.x + temp.w) {
        if (y > temp.y && y < temp.y + temp.h) {
            return true;
        }
    }
    return false;
}

//Additional Functions
bool GUI_Board::gameOver() {
    //Checks if checkmate
    if (white->kingIsCaptured() || black->kingIsCaptured()) return true;
    //Checks if no more moves
    if (white->getAllValidMoves(boardstate) == 0) return true;
    if (black->getAllValidMoves(boardstate) == 0) return true;
    return false;
}
bool GUI_Board::makeMove(int teamTmp, int sX, int sY, int eX, int eY) {
    uint64_t scoord;
    uint64_t ecoord;

    scoord = cartesianToBitmask(sX,sY);
    ecoord = cartesianToBitmask(eX,eY);
    
    if (team == 0) {
        return black->makeMove(scoord, ecoord, this->boardstate);
    }
    else {
        return white->makeMove(scoord, ecoord, this->boardstate);
    }
}
void GUI_Board::drawDebugBoard() const {
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
