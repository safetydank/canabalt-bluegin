#pragma once

#include "flx/sprite.h"
#include "flx/emitter.h"

class Walker;
typedef shared_ptr<Walker> WalkerPtr;

class Walker : public flx::Sprite
{
public:
    bool firing;
    float walkTimer;
    float idleTimer;
    vector<flx::EmitterPtr> smoke;

    static WalkerPtr create(vector<flx::EmitterPtr>& smokeArray);
    Walker(vector<flx::EmitterPtr>& smokeArray);

    virtual void update();
};

