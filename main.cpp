#include "GUI/header/gui_board.hpp"

GUI_Board* game;

int main(int argc, const char* args[]) {

    game = new GUI_Board();
    game->runGame();

    delete game;

    return 0;
}
