#ifndef __GAME_OBJECT_HPP__
#define __GAME_OBJECT_HPP__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "texture_manager.hpp"

class GameObject {
    protected:
        SDL_Texture* texture = NULL;
        SDL_Renderer* renderer = NULL;
        SDL_Rect srcRect, destRect;

        int x, y;
    public:
        GameObject(const char*, SDL_Renderer*, int, int);
        ~GameObject();

        void update();
        void render();
        void clean();

        void setX(int x) {this->x = x;}
        void setY(int y) {this->y = y;}
        SDL_Rect getRect() { return destRect; }

};

#endif  //__GAME_OBJECT_HPP__
