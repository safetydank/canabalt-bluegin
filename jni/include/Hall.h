#pragma once

#include "flx/sprite.h"
#include "flx/tileblock.h"

class Hall : public flx::Sprite
{
public:
    flx::TileblockPtr leftEdge;
    flx::TileblockPtr rightEdge;
    vector<flx::TileblockPtr> windows;
    vector<flx::TileblockPtr> walls;
    vector<flx::SpritePtr> doors;
    flx::TileblockPtr hall1;
    flx::TileblockPtr hall2;
    flx::SpritePtr hall3;
    vector<flx::TileblockPtr> extraWindows;
    vector<flx::TileblockPtr> extraWalls;
    vector<flx::SpritePtr> extraDoors;  

    static void initialize();

    Hall(float maxWidth=0);
    void create(float X, float Y, float Width, float Height, float tileSize,
            float hallHeight, int wallType, int windowType);

    virtual void render();
    virtual void update();
};

typedef shared_ptr<Hall> HallPtr;
