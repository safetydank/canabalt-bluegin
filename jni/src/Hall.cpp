#include "bluegin/resourcemanager.h"
#include "flx/flxG.h"

#include "Hall.h"
#include "Player.h"
#include "Sequence.h"

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

static const char* ImgWindow1 = "window1";
static const char* ImgWindow2 = "window2";
static const char* ImgWindow3 = "window3";
static const char* ImgWindow4 = "window4";

static const char* ImgDoors = "doors";

static const char* ImgHall1 = "hall1";
static const char* ImgHall2 = "hall2";

static vector<Graphic> leftWalls;
static vector<Graphic> rightWalls;
static vector<Graphic> middleWalls;
static vector<Graphic> windowImages;

static const float TILE_SIZE = 16.0f;

void Hall::initialize()
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

    windowImages.clear();
    windowImages.push_back(res.graphic(ImgWindow1));
    windowImages.push_back(res.graphic(ImgWindow2));
    windowImages.push_back(res.graphic(ImgWindow3));
    windowImages.push_back(res.graphic(ImgWindow4));
}

Hall::Hall(float maxWidth)
{
    ResourceManager& res = *(FlxG.resources);
    leftEdge = TileblockPtr(new Tileblock(0, 0, 0, 0));
    leftEdge->width = TILE_SIZE;
    leftEdge->height = 400; //for lack of a better guess
    leftEdge->loadGraphic(leftWalls.back());
    rightEdge = TileblockPtr(new Tileblock(0, 0, 0, 0));
    rightEdge->width = TILE_SIZE;
    rightEdge->height = 400;
    rightEdge->loadGraphic(rightWalls.back());
    // windows = [[NSMutableArray alloc] init];
    // walls = [[NSMutableArray alloc] init];
    // hall1 = [[CBlock cBlockWithX:0 y:0 width:0 height:0] retain];
    hall1 = TileblockPtr(new Tileblock(0, 0, 0, 0));
    hall1->width = maxWidth;
    hall1->height = TILE_SIZE;
    hall1->loadGraphic(res.graphic(ImgHall1));
    // hall2 = [[CBlock cBlockWithX:0 y:0 width:0 height:0] retain];
    hall2 = TileblockPtr(new Tileblock(0, 0, 0, 0));
    hall2->width = maxWidth;
    hall2->height = TILE_SIZE;
    hall2->loadGraphic(res.graphic(ImgHall2));
    hall3 = Sprite::create();
    // doors = [[NSMutableArray alloc] init];
    // extraWindows = [[NSMutableArray alloc] init];
    // extraWalls = [[NSMutableArray alloc] init];
    // extraDoors = [[NSMutableArray alloc] init];

    int n = ((400)/TILE_SIZE)/2;
    for (int i = 0; i < n; ++i) {
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

void Hall::create(float X, float Y, float Width, float Height, float tileSize,
        float hallHeight, int wallType, int windowType)
{
    ResourceManager& res = *(FlxG.resources);

    x = X;
    y = Y;
    width = Width;
    height = Height;

    leftEdge->x = x;
    leftEdge->y = 0;
    leftEdge->width = tileSize;
    leftEdge->height = y-hallHeight;
    leftEdge->loadGraphic(leftWalls.at(wallType));

    rightEdge->x = x+width-tileSize;
    rightEdge->y = 0;
    rightEdge->width = tileSize;
    rightEdge->height = y-hallHeight;
    rightEdge->loadGraphic(rightWalls.at(wallType));

    int n = ((y-hallHeight)/tileSize)/2;

    if (walls.size() < n) {
        while (extraWalls.size() > 0 && walls.size() < n) {
            walls.push_back(extraWalls.back());
            extraWalls.pop_back();
        }
        while (walls.size() < n)
            walls.push_back(TileblockPtr(new Tileblock(0, 0, 0, 0)));
    } else {
        while (walls.size() > n) {
            extraWalls.push_back(walls.back());
            walls.pop_back();
        }
    }
    for (int i = 0; i < n; ++i) {
        TileblockPtr wall = walls.at(i);
        wall->x = x+tileSize;
        wall->y = (y-hallHeight)-(1+i*2)*tileSize;
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
        window->y = (y-hallHeight)-(2+i*2)*tileSize;
        window->width = width-2*tileSize;
        window->height = tileSize;
        window->loadGraphic(windowImages.at(windowType));
    }

    hall1->x = x;
    hall1->y = y-tileSize;
    hall1->width = width;
    hall1->height = tileSize;
    hall1->loadGraphic(res.graphic(ImgHall1));
    hall2->x = x;
    hall2->y = y-2*tileSize;
    hall2->width = width;
    hall2->height = tileSize;
    hall2->loadGraphic(res.graphic(ImgHall2));

    hall3->x = x;
    hall3->y = y-hallHeight;
    hall3->createGraphic(width, hallHeight-2*tileSize, FlxU::color(0xff35353d));

    n = (width/tileSize-3)/4;
    int doorIndex = 0;
    for (int i = 1; i < n; ++i) {
        if (FlxU::random() > 0.65) continue;
        while (doors.size() <= doorIndex) {
            while (doors.size() <= doorIndex && extraDoors.size() > 0) {
                doors.push_back(extraDoors.back());
                extraDoors.pop_back();
            }
            while (doors.size() <= doorIndex)
                doors.push_back(Sprite::create());
        }
        SpritePtr door = doors.at(doorIndex);
        door->loadGraphic(res.graphic(ImgDoors), true, false, 15, 24);
        door->x = x+i*tileSize*4-tileSize;
        door->y = y-24;
        door->width = 15;
        door->randomFrame();
        doorIndex++;
    }
    while (doors.size() > doorIndex) {
        extraDoors.push_back(doors.back());
        doors.pop_back();
    }
}

void Hall::render()
{
    leftEdge->render();
    rightEdge->render();
    // glDisable(GL_BLEND);
    for (vector<TileblockPtr>::iterator it = windows.begin(); it != windows.end(); ++it)
        (*it)->render();
    for (vector<TileblockPtr>::iterator it = walls.begin(); it != walls.end(); ++it)
        (*it)->render();

    hall1->render();
    hall2->render();
    hall3->render();

    for (vector<SpritePtr>::iterator it = doors.begin(); it != doors.end(); ++it)
        (*it)->render();
    // glEnable(GL_BLEND);
}

void Hall::update()
{
    leftEdge->update();
    rightEdge->update();
    // glDisable(GL_BLEND);
    for (vector<TileblockPtr>::iterator it = windows.begin(); it != windows.end(); ++it)
        (*it)->update();
    for (vector<TileblockPtr>::iterator it = walls.begin(); it != walls.end(); ++it)
        (*it)->update();

    hall1->update();
    hall2->update();
    hall3->update();

    for (vector<SpritePtr>::iterator it = doors.begin(); it != doors.end(); ++it)
        (*it)->update();
}


