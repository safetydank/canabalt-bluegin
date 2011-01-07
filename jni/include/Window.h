#pragma once

#include "flx/sprite.h"
#include "flx/emitter.h"

class Player;

extern const float WindowW;

class Window;
typedef shared_ptr<Window> WindowPtr;

class Window : public flx::Sprite
{
public:
    flx::EmitterPtr shards;
    Player* player;

    static WindowPtr create(ci::Vec2f point, float height, Player* player, flx::EmitterPtr shards);
    Window(ci::Vec2f point, float height, Player* plr, flx::EmitterPtr shards);

    virtual void update();
};
