#pragma once

#include "flx/object.h"
#include "flx/data/rect.h"

class Player;

class CraneTrigger;
typedef shared_ptr<CraneTrigger> CraneTriggerPtr;

class CraneTrigger : public flx::Object
{
public:
    Player* player;
    static CraneTriggerPtr create(flx::Rect frame, Player* player);
    CraneTrigger(flx::Rect frame, Player* player);

    virtual void update();
    virtual void render() { }
};
