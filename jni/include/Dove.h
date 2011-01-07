#pragma once

#include "bluegin/graphic.h"

#include "flx/group.h"
#include "flx/data/anim.h"
#include "flx/sprite.h"

class Player;
class DoveGroup;
typedef shared_ptr<DoveGroup> DoveGroupPtr;

class DoveGroup : public flx::Group
{
public:
    int doveCount;
    int visibleDoves;
    bluegin::Graphic graphic;

    static DoveGroupPtr create(int DoveCount);
    DoveGroup(bluegin::Graphic graphic, int DoveCount);

    void setVisibleDoves(int visibleDoves);
    virtual void render();
};

class Dove : public flx::Sprite
{
public:
    Player* player;
    float trigger;

    static void initialize();

    Dove(bluegin::Graphic gfx);

    void setTrigger(float trgr);
    
    virtual void update();
    virtual void render();
};
typedef shared_ptr<Dove> DovePtr;

