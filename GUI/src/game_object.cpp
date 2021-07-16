#include "../header/game_object.hpp"

GameObject::~GameObject() {
    
}

GameObject::GameObject(const char* imgFile, SDL_Renderer* r, int w, int h) {

    this->renderer = r;
    this->texture = TextureManager::load_Texture(imgFile, r);

    //this->srcRect = NULL;

    this->x = 0;
    this->y = 0;

    this->destRect.x = this->x;
    this->destRect.y = this->y;
    this->destRect.w = w;
    this->destRect.h = h;
}

void GameObject::render() {
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
}

void GameObject::update() {
    this->destRect.x = this->x;
    this->destRect.y = this->y;
}

void GameObject::clean() {
    SDL_DestroyTexture(texture);
}
