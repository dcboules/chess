#include "../header/texture_manager.hpp"
#include <SDL2/SDL_image.h>
#include <iostream>

SDL_Texture* TextureManager::load_Texture(const char* imgFile, SDL_Renderer* rend) {
    SDL_Surface* tempSurface = IMG_Load(imgFile);
    if (!tempSurface) std::cout << "File couldnt load" << std::endl; 
    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, tempSurface);
    SDL_FreeSurface(tempSurface);

    return tex;
}