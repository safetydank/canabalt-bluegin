#pragma once

#include "flx/sprite.h"
#include "flx/tileblock.h"

class Building : public flx::Object
{
public:
    flx::TileblockPtr leftEdge;
    flx::TileblockPtr rightEdge;
    flx::TileblockPtr topEdge;
    flx::SpritePtr leftCorner;
    flx::SpritePtr rightCorner;
    vector<flx::TileblockPtr> windows;
    vector<flx::TileblockPtr> walls;
    //vector<> cracks;
    vector<flx::TileblockPtr> extraWindows;
    vector<flx::TileblockPtr> extraWalls;

    Building(float maxWidth=0);
    void create(float X, float Y, float Width, float Height, float tileSize,
            int buildingType, int wallType, int windowType);

    static void initialize();

    virtual void render();
    virtual void update();
};

typedef shared_ptr<Building> BuildingPtr;

