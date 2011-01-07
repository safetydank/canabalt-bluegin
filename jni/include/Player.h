#pragma once

#include "flx/Sprite.h"

class Player : public flx::Sprite
{
public:
    float jump;
    float jumpLimit;
    bool  stumble;
    float my;
    
    float ft;
    float fc;
    // NSArray * feet;
    // NSArray * feetC;
    bool craneFeet;
    std::string epitaph;
    bool pause;

    Player();
    virtual ~Player();

    void update();
    virtual void hitBottom(Object& contact, float velocity);
    virtual void hitLeft(Object& contact, float velocity);
    void setStumble(bool stumbleValue);
};

typedef shared_ptr<Player> PlayerPtr;


