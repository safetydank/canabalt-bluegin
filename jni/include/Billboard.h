#pragma once

#include "flx/object.h"
#include "flx/sprite.h"
#include "flx/tileblock.h"

typedef flx::Tileblock    RepeatBlock;
typedef flx::TileblockPtr RepeatBlockPtr;

class Billboard : public flx::Object
{
public:
    flx::SpritePtr post;
    flx::SpritePtr postTop;
    RepeatBlockPtr bottomEdge;
    RepeatBlockPtr topEdge;
    RepeatBlockPtr leftEdge;
    RepeatBlockPtr rightEdge;
    flx::SpritePtr center;
    flx::SpritePtr topRightCorner;
    flx::SpritePtr topLeftCorner;
    flx::SpritePtr bottomRightCorner;
    flx::SpritePtr bottomLeftCorner;
    RepeatBlockPtr catwalkMiddle;
    flx::SpritePtr catwalkLeft;
    flx::SpritePtr catwalkRight;
    flx::SpritePtr damage;

    void create(float X, float Y, float Width, float Height, float tileSize, int hallHeight);
    Billboard(float maxWidth=0);

    virtual void update();
    virtual void render();
};

typedef shared_ptr<Billboard> BillboardPtr;

