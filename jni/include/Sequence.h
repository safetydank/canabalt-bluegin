#pragma once

#include "flx/object.h"
#include "flx/group.h"
#include "flx/emitter.h"
#include "flx/tileblock.h"

#include "Building.h"
#include "Dove.h"
#include "Player.h"

class Sequence;
typedef shared_ptr<Sequence> SequencePtr;

class Sequence : public flx::Object
{
public:
    Sequence();
    // equivalent to iOS sequenceWithPlayer
    static SequencePtr get(Player* player, flx::EmitterPtr shardsA, flx::EmitterPtr shardsB);

    flx::GroupPtr blocks;

    bool roof;
    int  type;
    bool passed; //helps with the epitaph type tracking
    flx::GroupPtr foregroundLayer;
    flx::GroupPtr layer;
    flx::GroupPtr renderLayer;
    flx::GroupPtr backgroundRenderLayer;
    flx::GroupPtr layerLeg;
    Sequence*     seq;
    Player*       player;

    flx::EmitterPtr shardsA;
    flx::EmitterPtr shardsB;

    // NSArray * walls;
    // NSArray * roofs;
    // NSArray * floors;
    // NSArray * windows;
    // NSArray * antennas;

    BuildingPtr building;
    flx::TileblockPtr escape;
    flx::TileblockPtr fence;

    DoveGroupPtr doveGroup;
    static void setNextIndex(int ni);
    static void setNextType(int nt);
    static void setCurIndex(int ci);
    static int getNextIndex();
    static int getNextType();
    static int getCurIndex();

    static void setLastType(int lt);
    static void setThisType(int tt);

    int getLastType();
    int getThisType();

    int getType();
    void clear();
    void aftermath();
    void stomp();

    void initSequence(Sequence* sequence);

    virtual void update();
    virtual void render();
    void reset();

    static void initialize();

private:
    void decorate(float seqX, float seqY, float seqWidth);
    void setPlayer(Player* plr);
    Player* getPlayer();
    void setShardsA(flx::EmitterPtr shardsa);
    flx::EmitterPtr getShardsA();
    void setShardsB(flx::EmitterPtr shardsb);
    flx::EmitterPtr getShardsB();
};
