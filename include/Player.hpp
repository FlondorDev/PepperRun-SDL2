#ifndef _PLAYER_H_
#define _PLAYER_H_
#include <iostream>
#include <SDL.h>
#include "../Engine/include/GameObject.hpp"

class Player : public IController, public GameObject
{
    private:
        int jumps;
        bool jumped;
        SDL_RendererFlip flip;
    public:
        Player(std::string Tex, Vector2  = {0, 0}, int speed = 5, int W = 0, int H = 0);
        void Input(const Uint8 *keyboard_state_array) override;
        void onCollide(CollisionInfo info) override;
        void Update() override;
        void Draw(SDL_RendererFlip mode) override;
        void Jump();
};


#endif