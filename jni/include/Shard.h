#pragma once

#include "flx/sprite.h"
#include "flx/emitter.h"

class Shard : public flx::Sprite
{
public:
    Shard(bluegin::Graphic graphic);
    virtual ~Shard() { }

    virtual void hitBottom(flx::Object& contact, float vel);
    bool makesSound;
};

class ShardEmitter : public flx::Emitter
{
public:
    ShardEmitter(int count);
    virtual ~ShardEmitter() { }
};

