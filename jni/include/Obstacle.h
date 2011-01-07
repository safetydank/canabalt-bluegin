#pragma once

#include "flx/sprite.h"

class Player;
class Obstacle;
typedef shared_ptr<Obstacle> ObstaclePtr;

class Obstacle : public flx::Sprite
{
public:
    Player* p;

    static ObstaclePtr create(ci::Vec2f origin, Player* player, bool alt=false);
    Obstacle(ci::Vec2f origin, Player* player, bool alt);

    virtual void update();
    virtual void hitBottom(Object& obj, float velocity);
    virtual void kill();
};
