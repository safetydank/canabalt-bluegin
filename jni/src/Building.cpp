#include "bluegin/resourcemanager.h"
#include "flx/flxG.h"

#include "Building.h"

using namespace ci;
using namespace bluegin;
using namespace flx;

extern FlxGlobal FlxG;

static const char* ImgWall1Left = "wall1-left";
static const char* ImgWall2Left = "wall2-left";
static const char* ImgWall3Left = "wall3-left";
static const char* ImgWall4Left = "wall4-left";
static const char* ImgWall1Middle = "wall1-middle";
static const char* ImgWall2Middle = "wall2-middle";
static const char* ImgWall3Middle = "wall3-middle";
static const char* ImgWall4Middle = "wall4-middle";
static const char* ImgWall1Right = "wall1-right";
static const char* ImgWall2Right = "wall2-right";
static const char* ImgWall3Right = "wall3-right";
static const char* ImgWall4Right = "wall4-right";


static const char* ImgRoof1Left = "roof1-left";
static const char* ImgRoof2Left = "roof2-left";
static const char* ImgRoof3Left = "roof3-left";
static const char* ImgRoof4Left = "roof4-left";
static const char* ImgRoof5Left = "roof6-left";
static const char* ImgRoof6Left = "roof5-left";
static const char* ImgRoof1Middle = "roof1-middle";
static const char* ImgRoof2Middle = "roof2-middle";
static const char* ImgRoof3Middle = "roof3-middle";
static const char* ImgRoof4Middle = "roof4-middle";
static const char* ImgRoof5Middle = "roof6-middle";
static const char* ImgRoof6Middle = "roof5-middle";
static const char* ImgRoof1Right = "roof1-right";
static const char* ImgRoof2Right = "roof2-right";
static const char* ImgRoof3Right = "roof3-right";
static const char* ImgRoof4Right = "roof4-right";
static const char* ImgRoof5Right = "roof6-right";
static const char* ImgRoof6Right = "roof5-right";

static const char* ImgWall1LeftCracked = "wall1-left-cracked";
static const char* ImgWall2LeftCracked = "wall2-left-cracked";
static const char* ImgWall3LeftCracked = "wall3-left-cracked";
static const char* ImgWall4LeftCracked = "wall4-left-cracked";
static const char* ImgWall1MiddleCracked = "wall1-middle-cracked";
static const char* ImgWall2MiddleCracked = "wall2-middle-cracked";
static const char* ImgWall3MiddleCracked = "wall3-middle-cracked";
static const char* ImgWall4MiddleCracked = "wall4-middle-cracked";
static const char* ImgWall1RightCracked = "wall1-right-cracked";
static const char* ImgWall2RightCracked = "wall2-right-cracked";
static const char* ImgWall3RightCracked = "wall3-right-cracked";
static const char* ImgWall4RightCracked = "wall4-right-cracked";

static const char* ImgRoof1LeftCracked = "roof1-left-cracked";
static const char* ImgRoof2LeftCracked = "roof2-left-cracked";
static const char* ImgRoof3LeftCracked = "roof3-left-cracked";
static const char* ImgRoof4LeftCracked = "roof4-left-cracked";
static const char* ImgRoof5LeftCracked = "roof6-left-cracked";
static const char* ImgRoof6LeftCracked = "roof5-left-cracked";
static const char* ImgRoof1MiddleCracked = "roof1-middle-cracked";
static const char* ImgRoof2MiddleCracked = "roof2-middle-cracked";
static const char* ImgRoof3MiddleCracked = "roof3-middle-cracked";
static const char* ImgRoof4MiddleCracked = "roof4-middle-cracked";
static const char* ImgRoof5MiddleCracked = "roof6-middle-cracked";
static const char* ImgRoof6MiddleCracked = "roof5-middle-cracked";
static const char* ImgRoof1RightCracked = "roof1-right-cracked";
static const char* ImgRoof2RightCracked = "roof2-right-cracked";
static const char* ImgRoof3RightCracked = "roof3-right-cracked";
static const char* ImgRoof4RightCracked = "roof4-right-cracked";
static const char* ImgRoof5RightCracked = "roof6-right-cracked";
static const char* ImgRoof6RightCracked = "roof5-right-cracked";


static const char* ImgFloor1Left = "floor1-left";
static const char* ImgFloor2Left = "floor2-left";
static const char* ImgFloor1Middle = "floor1-middle";
static const char* ImgFloor2Middle = "floor2-middle";
static const char* ImgFloor1Right = "floor1-right";
static const char* ImgFloor2Right = "floor2-right";


static const char* ImgWindow1 = "window1";
static const char* ImgWindow2 = "window2";
static const char* ImgWindow3 = "window3";
static const char* ImgWindow4 = "window4";

static vector<Graphic> leftWalls;
static vector<Graphic> rightWalls;
static vector<Graphic> middleWalls;
static vector<Graphic> leftWallsCracked;
static vector<Graphic> rightWallsCracked;
static vector<Graphic> middleWallsCracked;


static vector<Graphic> leftFloors;
static vector<Graphic> middleFloors;
static vector<Graphic> rightFloors;

static vector<Graphic> leftRoofs;
static vector<Graphic> middleRoofs;
static vector<Graphic> rightRoofs;

static vector<Graphic> leftRoofsCracked;
static vector<Graphic> middleRoofsCracked;
static vector<Graphic> rightRoofsCracked;

static vector<Graphic> windowImages;

enum {
    ROOF,
    HALLWAY,
    COLLAPSE,
    BOMB,
    CRANE,
    BILLBOARD,
    LEG
};

const static float TILE_SIZE = 16.0f;

void Building::initialize()
{
    ResourceManager& res = *(FlxG.resources);
    leftWalls.clear();
    leftWalls.push_back(res.graphic(ImgWall1Left));
    leftWalls.push_back(res.graphic(ImgWall2Left));
    leftWalls.push_back(res.graphic(ImgWall3Left));
    leftWalls.push_back(res.graphic(ImgWall4Left));

    rightWalls.clear();
    rightWalls.push_back(res.graphic(ImgWall1Right));
    rightWalls.push_back(res.graphic(ImgWall2Right));
    rightWalls.push_back(res.graphic(ImgWall3Right));
    rightWalls.push_back(res.graphic(ImgWall4Right));

    middleWalls.clear();
    middleWalls.push_back(res.graphic(ImgWall1Middle));
    middleWalls.push_back(res.graphic(ImgWall2Middle));
    middleWalls.push_back(res.graphic(ImgWall3Middle));
    middleWalls.push_back(res.graphic(ImgWall4Middle));

    leftWallsCracked.clear();
    leftWallsCracked.push_back(res.graphic(ImgWall1LeftCracked));
    leftWallsCracked.push_back(res.graphic(ImgWall2LeftCracked));
    leftWallsCracked.push_back(res.graphic(ImgWall3LeftCracked));
    leftWallsCracked.push_back(res.graphic(ImgWall4LeftCracked));

    rightWallsCracked.clear();
    rightWallsCracked.push_back(res.graphic(ImgWall1RightCracked));
    rightWallsCracked.push_back(res.graphic(ImgWall2RightCracked));
    rightWallsCracked.push_back(res.graphic(ImgWall3RightCracked));
    rightWallsCracked.push_back(res.graphic(ImgWall4RightCracked));

    middleWallsCracked.clear();
    middleWallsCracked.push_back(res.graphic(ImgWall1MiddleCracked));
    middleWallsCracked.push_back(res.graphic(ImgWall2MiddleCracked));
    middleWallsCracked.push_back(res.graphic(ImgWall3MiddleCracked));
    middleWallsCracked.push_back(res.graphic(ImgWall4MiddleCracked));

    leftFloors.clear();
    leftFloors.push_back(res.graphic(ImgFloor1Left));
    leftFloors.push_back(res.graphic(ImgFloor2Left));

    middleFloors.clear();
    middleFloors.push_back(res.graphic(ImgFloor1Middle));
    middleFloors.push_back(res.graphic(ImgFloor2Middle));

    rightFloors.clear();
    rightFloors.push_back(res.graphic(ImgFloor1Right));
    rightFloors.push_back(res.graphic(ImgFloor2Right));

    leftRoofs.clear();
    leftRoofs.push_back(res.graphic(ImgRoof1Left));
    leftRoofs.push_back(res.graphic(ImgRoof2Left));
    leftRoofs.push_back(res.graphic(ImgRoof3Left));
    leftRoofs.push_back(res.graphic(ImgRoof4Left));
    leftRoofs.push_back(res.graphic(ImgRoof5Left));
    leftRoofs.push_back(res.graphic(ImgRoof6Left));

    middleRoofs.clear();
    middleRoofs.push_back(res.graphic(ImgRoof1Middle));
    middleRoofs.push_back(res.graphic(ImgRoof2Middle));
    middleRoofs.push_back(res.graphic(ImgRoof3Middle));
    middleRoofs.push_back(res.graphic(ImgRoof4Middle));
    middleRoofs.push_back(res.graphic(ImgRoof5Middle));
    middleRoofs.push_back(res.graphic(ImgRoof6Middle));

    rightRoofs.clear();
    rightRoofs.push_back(res.graphic(ImgRoof1Right));
    rightRoofs.push_back(res.graphic(ImgRoof2Right));
    rightRoofs.push_back(res.graphic(ImgRoof3Right));
    rightRoofs.push_back(res.graphic(ImgRoof4Right));
    rightRoofs.push_back(res.graphic(ImgRoof5Right));
    rightRoofs.push_back(res.graphic(ImgRoof6Right));

    leftRoofsCracked.clear();
    leftRoofsCracked.push_back(res.graphic(ImgRoof1LeftCracked));
    leftRoofsCracked.push_back(res.graphic(ImgRoof2LeftCracked));
    leftRoofsCracked.push_back(res.graphic(ImgRoof3LeftCracked));
    leftRoofsCracked.push_back(res.graphic(ImgRoof4LeftCracked));
    leftRoofsCracked.push_back(res.graphic(ImgRoof5LeftCracked));
    leftRoofsCracked.push_back(res.graphic(ImgRoof6LeftCracked));

    middleRoofsCracked.clear();
    middleRoofsCracked.push_back(res.graphic(ImgRoof1MiddleCracked));
    middleRoofsCracked.push_back(res.graphic(ImgRoof2MiddleCracked));
    middleRoofsCracked.push_back(res.graphic(ImgRoof3MiddleCracked));
    middleRoofsCracked.push_back(res.graphic(ImgRoof4MiddleCracked));
    middleRoofsCracked.push_back(res.graphic(ImgRoof5MiddleCracked));
    middleRoofsCracked.push_back(res.graphic(ImgRoof6MiddleCracked));

    rightRoofsCracked.clear();
    rightRoofsCracked.push_back(res.graphic(ImgRoof1RightCracked));
    rightRoofsCracked.push_back(res.graphic(ImgRoof2RightCracked));
    rightRoofsCracked.push_back(res.graphic(ImgRoof3RightCracked));
    rightRoofsCracked.push_back(res.graphic(ImgRoof4RightCracked));
    rightRoofsCracked.push_back(res.graphic(ImgRoof5RightCracked));
    rightRoofsCracked.push_back(res.graphic(ImgRoof6RightCracked));

    windowImages.clear();
    windowImages.push_back(res.graphic(ImgWindow1));
    windowImages.push_back(res.graphic(ImgWindow2));
    windowImages.push_back(res.graphic(ImgWindow3));
    windowImages.push_back(res.graphic(ImgWindow4));
}

Building::Building(float maxWidth)
{
    leftEdge = TileblockPtr(new Tileblock(0, 0, 0, 0));
    leftEdge->width = TILE_SIZE;
    leftEdge->height = 400-TILE_SIZE;
    leftEdge->loadGraphic(leftWalls.back());
    rightEdge = TileblockPtr(new Tileblock(0, 0, 0, 0));
    rightEdge->width = TILE_SIZE;
    rightEdge->height = 400-TILE_SIZE;
    rightEdge->loadGraphic(rightWalls.back());
    topEdge = TileblockPtr(new Tileblock(0, 0, 0, 0));
    topEdge->width = maxWidth-TILE_SIZE*2;
    topEdge->height = TILE_SIZE;
    topEdge->loadGraphic(middleRoofs.back());
    leftCorner  = Sprite::create();
    rightCorner = Sprite::create();
    //prepopulate these.. need to know max height...
    //assume for now height of 400...
    int n = (400/TILE_SIZE-1)/2;
    for (int i=0; i<n+1; ++i) {
        TileblockPtr wall = TileblockPtr(new Tileblock(0, 0, 0, 0));
        wall->width = maxWidth-2*TILE_SIZE;
        wall->height = TILE_SIZE;
        wall->loadGraphic(middleWalls.back());
        extraWalls.push_back(wall);
    }
    for (int i = 0; i < n; ++i) {
        TileblockPtr window = TileblockPtr(new Tileblock(0, 0, 0, 0));
        window->width = maxWidth-2*TILE_SIZE;
        window->height = TILE_SIZE;
        window->loadGraphic(windowImages.back());
        extraWindows.push_back(window);
    }
}

void Building::create(float X, float Y, float Width, float Height, float tileSize,
                      int buildingType, int wallType, int windowType)
{
    x = X;
    y = Y;
    width = Width;
    height = Height;

    velocity.y = 0;
    acceleration.y = 0;

    leftEdge->x = x;
    leftEdge->y = y+tileSize;
    leftEdge->width = tileSize;
    leftEdge->height = height-tileSize;
    if (buildingType == COLLAPSE)
        leftEdge->loadGraphic(leftWallsCracked.at(wallType));
    else
        leftEdge->loadGraphic(leftWalls.at(wallType));

    rightEdge->x = x+width-tileSize;
    rightEdge->y = y+tileSize;
    rightEdge->width = tileSize;
    rightEdge->height = height-tileSize;
    if (buildingType == COLLAPSE)
        rightEdge->loadGraphic(rightWallsCracked.at(wallType));
    else
        rightEdge->loadGraphic(rightWalls.at(wallType));

    topEdge->x = x+tileSize;
    topEdge->y = y;
    topEdge->width = width-tileSize*2;
    topEdge->height = tileSize;

    leftCorner->x = x;
    leftCorner->y = y;
    rightCorner->x = x+width-tileSize;
    rightCorner->y = y;

    if (buildingType == HALLWAY) {
        int floorIndex = middleFloors.size()*FlxU::random();
        topEdge->loadGraphic(middleFloors.at(floorIndex));
        leftCorner->loadGraphic(leftFloors.at(floorIndex));
        leftCorner->setFrame(0);
        rightCorner->loadGraphic(rightFloors.at(floorIndex));
        rightCorner->setFrame(0);
    } else {
        int roofIndex = middleRoofs.size()*FlxU::random();
        if (buildingType == COLLAPSE) {
            topEdge->loadGraphic(middleRoofsCracked.at(roofIndex));
            leftCorner->loadGraphic(leftRoofsCracked.at(roofIndex), true);
            leftCorner->setFrame(FlxU::random()*leftRoofsCracked.size());
            rightCorner->loadGraphic(rightRoofsCracked.at(roofIndex), true);
            rightCorner->setFrame(FlxU::random()*rightRoofsCracked.size());
        } else {
            topEdge->loadGraphic(middleRoofs.at(roofIndex));
            leftCorner->loadGraphic(leftRoofs.at(roofIndex));
            leftCorner->setFrame(0);
            rightCorner->loadGraphic(rightRoofs.at(roofIndex));
            rightCorner->setFrame(0);
        }
    }

    int n = (height/tileSize-1)/2;

    if (walls.size() < n+1) {
        while (!extraWalls.empty() && walls.size() < n+1) {
            walls.push_back(extraWalls.back());
            extraWalls.pop_back();
        }
        while (walls.size() < n+1)
            walls.push_back(TileblockPtr(new Tileblock(0,0,0,0)));
    } else {
        while (walls.size() > n+1) {
            extraWalls.push_back(walls.back());
            walls.pop_back();
        }
    }

    // XXX refactor
    if (buildingType == COLLAPSE)
        for (int i=0; i<n+1; ++i) {
            TileblockPtr wall = walls.at(i);
            wall->x = x+tileSize;
            wall->y = y + (1+i*2)*tileSize;
            wall->width = width-2*tileSize;
            wall->height = tileSize;
            wall->loadGraphic(middleWallsCracked.at(wallType));
        }
    else
        for (int i=0; i<n+1; ++i) {
            TileblockPtr wall = walls.at(i);
            wall->x = x+tileSize;
            wall->y = y + (1+i*2)*tileSize;
            wall->width = width-2*tileSize;
            wall->height = tileSize;
            wall->loadGraphic(middleWalls.at(wallType));
        }


        if (windows.size() < n) {
            while (extraWindows.size() > 0 && windows.size() < n) {
                windows.push_back(extraWindows.back());
                extraWindows.pop_back();
            }
            while (windows.size() < n)
                windows.push_back(TileblockPtr(new Tileblock(0,0,0,0)));
        } else {
            while (windows.size() > n) {
                extraWindows.push_back(windows.back());
                windows.pop_back();
            }
        }

        for (int i = 0; i < n; ++i) {
            TileblockPtr window = windows.at(i);
            window->x = x+tileSize;
            window->y = y+(2+i*2)*tileSize;
            window->width = width-2*tileSize;
            window->height = tileSize;
            window->loadGraphic(windowImages.at(windowType));
        }

}

void Building::render()
{
    leftCorner->render();
    rightCorner->render();
    leftEdge->render();
    rightEdge->render();
    // glDisable(GL_BLEND);
    topEdge->render();
    for (vector<TileblockPtr>::iterator it = windows.begin(); it != windows.end(); ++it)
        (*it)->render();
    for (vector<TileblockPtr>::iterator it = walls.begin(); it != walls.end(); ++it)
        (*it)->render();
    // glEnable(GL_BLEND);
}

void Building::update()
{
    //treat this like it's a group
    float oldx = x;
    float oldy = y;
    float mx = 0;
    float my = 0;
    Object::update();
    bool moved = false;
    if (x != oldx || y != oldy) {
        moved = true;
        mx = x-oldx;
        my = y-oldy;
    }
    if (moved) {
        leftEdge->x += mx;
        leftEdge->y += my;
        rightEdge->x += mx;
        rightEdge->y += my;
        topEdge->x += mx;
        topEdge->y += my;
        leftCorner->x += mx;
        leftCorner->y += my;
        rightCorner->x += mx;
        rightCorner->y += my;
        for (vector<TileblockPtr>::iterator it = windows.begin(); it != windows.end(); ++it) {
            (*it)->x += mx;
            (*it)->y += my;
        }
        for (vector<TileblockPtr>::iterator it = walls.begin(); it != walls.end(); ++it) {
            (*it)->x += mx;
            (*it)->y += my;
        }
    }
    leftEdge->update();
    rightEdge->update();
    topEdge->update();
    leftCorner->update();
    rightCorner->update();
    for (vector<TileblockPtr>::iterator it = windows.begin(); it != windows.end(); ++it)
        (*it)->update();
    for (vector<TileblockPtr>::iterator it = walls.begin(); it != walls.end(); ++it)
        (*it)->update();
}


