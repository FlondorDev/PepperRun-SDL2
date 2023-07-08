#ifndef _WALL_H_
#define _WALL_H_
#include <iostream>
#include <SDL.h>
#include "../Engine/include/GameObject.hpp"

class Wall : public GameObject
{
    private:
    public:
        Wall(std::string Tex, Vector2 pos, int W = 0, int H = 0);
};

#endif