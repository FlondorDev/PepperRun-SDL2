#include "../include/Pepper.hpp"

Pepper::Pepper(std::string Tex, Vector2 pos) : GameObject{Tex, pos, 0, 0, false}
{
    rb.collisionId = collisionMaskList::PEPPER;
    rb.addCollisionMask(collisionMaskList::PLAYER);
    rb.CreateBoxCollider(Width, Height);
    rb.isActive = true;
}

void Pepper::Draw(SDL_RendererFlip mode)
{
    GameObject::Draw(mode);
}

void Pepper::Update()
{
    if (toDelete)
    {
        Pepper::~Pepper();
    }
}

void Pepper::onCollide(CollisionInfo collisionInfo)
{
    collisionInfo.other->rb.Speed = 12;
    toDelete = true;
}
