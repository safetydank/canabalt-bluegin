#pragma once

#include "flx/emitter.h"
#include "flx/sprite.h"

class Player;
class Sequence;

class Bomb;
typedef shared_ptr<Bomb> BombPtr;

class Bomb : public flx::Sprite
{
public:
    float myY;
    Player* p;
    flx::EmitterPtr e;
    Sequence* s;
    // vector<> en;

    static BombPtr get(ci::Vec2f origin, Player* player, Sequence* sequence);
    Bomb(ci::Vec2f Origin, Player* player, Sequence* sequence, bluegin::Graphic graphic);
    void add(flx::EmitterPtr gibs);

    virtual void update();
};

