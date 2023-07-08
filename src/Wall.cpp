#include "../include/Wall.hpp"

Wall::Wall(std::string Tex, Vector2 Pos, int W, int H) : GameObject{Tex, Pos, W, H}
{
    rb.collisionId = collisionMaskList::WALL;
    rb.CreateBoxCollider(Width, Height);
    rb.isActive = true;
}
