#pragma once

#include "flx/object.h"
#include "flx/sprite.h"
#include "flx/tileblock.h"

#include "CraneTrigger.h"

typedef flx::Tileblock CBlock;
typedef flx::TileblockPtr CBlockPtr;

class Crane;
typedef shared_ptr<Crane> CranePtr;

class Crane : public flx::Object
{
public:
    CraneTriggerPtr trigger;
    CBlockPtr beam;
    flx::TileblockPtr post;
    flx::SpritePtr counterweight;
    flx::SpritePtr cabin;
    flx::SpritePtr pulley;
    flx::SpritePtr antenna1;
    flx::SpritePtr antenna2;
    flx::SpritePtr antenna3;

    Crane(float maxWidth=0);
    void create(float X, float Y, float Width, float Height, Player* player);

    virtual void update();
    virtual void render();
};
