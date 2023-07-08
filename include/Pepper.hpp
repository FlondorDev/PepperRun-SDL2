#ifndef _PEPPER_H_
#define _PEPPER_H_
#include <iostream>
#include <SDL.h>
#include "../Engine/include/GameObject.hpp"

class Pepper : public GameObject
{
    private:
    public:
        Pepper(std::string Tex, Vector2 pos);
        bool toDelete;
        void onCollide(CollisionInfo info) override;
        void Update() override;
        void Draw(SDL_RendererFlip mode) override;
};

#endif