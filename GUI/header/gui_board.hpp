#ifndef __GUI_BOARD_HPP__
#define __GUI_BOARD_HPP__

#include <cstdint>
#include <SDL2/SDL.h>
#include <iostream>

#include "../../player.hpp"
#include "game_object.hpp"

class GUI_Board {
    private:
        Player* white;
        Player* black;
        
        uint64_t boardstate;
        int team;

        //From Chess Game
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* chessBoard;
        SDL_Rect windowRect;
        GameObject* white_pieces[64] = {nullptr};
        GameObject* black_pieces[64] = {nullptr};
        bool isRunning;
        int mouseX, mouseY;
        bool pieceMoved = false;
        GameObject* pieceMoving = nullptr;
        int PIECE_W, PIECE_H;
    
    protected:
        uint64_t cartesianToBitmask(int column, int row) const;
    
    public:
        GUI_Board();
        ~GUI_Board();
        
        void updateBoardState();
        uint64_t getBoardState() const;
        bool makeMove(int team);
        
        void runGame();

        //New Functions
        bool gameOver();
        bool makeMove(int team, int sX, int sY, int eX, int eY);

        //From Chess Game
        void init(int x, int y, int w, int h);

        void handleEvents();
        void update();
        void render();
        void clean();

        bool running() { return isRunning; }



        void drawDebugBoard() const;
    private:
        bool collision(int, int, GameObject*);


};

#endif