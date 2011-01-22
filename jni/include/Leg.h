#pragma once

#include "flx/emitter.h"
#include "flx/sprite.h"

class Player;
class Sequence;

class Leg;
typedef shared_ptr<Leg> LegPtr;

class Leg : public flx::Sprite
{
public:
    float myY;
    Player* p;
    flx::EmitterPtr e;
    // vector<> en;
    Sequence* s;
    flx::SpritePtr top;

    static LegPtr create(ci::Vec2f origin, Player* player, Sequence* sequence);
    Leg(ci::Vec2f Origin, Player* player, Sequence* sequence, bluegin::Graphic graphic);
    void add(flx::EmitterPtr gibs);

    virtual void update();
    virtual void render();
};

