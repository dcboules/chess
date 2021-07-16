#ifndef __TEX_MAN_HPP__
#define __TEX_MAN_HPP__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class TextureManager {
    public:
        static SDL_Texture* load_Texture(const char* fileName, SDL_Renderer *ren);
};

#endif