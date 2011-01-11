#include "bluegin/resourcemanager.h"
#include "flx/flxG.h"
#include "flx/data/rect.h"

#include "Crane.h"

static const float tileSize = 16;

static const char* ImgAntenna5 = "antenna5-trimmed";

static const char* ImgCrane1 = "crane1"; //beam
static const char* ImgCrane2 = "crane2-filled"; //post
static const char* ImgCrane3 = "crane3"; //counterweight
static const char* ImgCrane4 = "crane4"; //cabin
static const char* ImgCrane5 = "crane5"; //pulley

using namespace ci; 
using namespace bluegin; 
using namespace flx;

extern FlxGlobal FlxG;

Crane::Crane(float maxWidth)
{
    ResourceManager& res = *(FlxG.resources);

    beam = CBlockPtr(new CBlock(0, 0, 0, 0));
    beam->width = maxWidth;
    beam->height = tileSize*2;
    beam->loadGraphic(res.graphic(ImgCrane1));
    post = TileblockPtr(new Tileblock(0,0,0,0));
    post->width = tileSize*2;
    post->height = 400-tileSize*2;
    post->loadGraphic(res.graphic(ImgCrane2));
    counterweight = Sprite::create(0, 0, res.graphic(ImgCrane3));
    cabin    = Sprite::create(0, 0, res.graphic(ImgCrane4));
    pulley   = Sprite::create(0, 0, res.graphic(ImgCrane5));
    antenna1 = Sprite::create(0, 0, res.graphic(ImgAntenna5));
    antenna2 = Sprite::create(0, 0, res.graphic(ImgAntenna5));
    antenna3 = Sprite::create(0, 0, res.graphic(ImgAntenna5));
}

void Crane::create(float X, float Y, float Width, float Height, Player* player)
{
    ResourceManager& res = *(FlxG.resources);

    x = X;
    y = Y;
    width = Width;
    height = Height;

    Rect frame(x, y-tileSize*2, width, tileSize*2);
    trigger = CraneTriggerPtr(new CraneTrigger(frame, player));

    bool left = FlxU::random() < 0.5;
    int cx = width * 0.35;

    float ah = 160;

    beam->x = x;
    beam->y = y;
    beam->width = width;
    beam->height = tileSize*2;
    beam->loadGraphic(res.graphic(ImgCrane1));

    if (left) {
        post->x = x+cx;
        post->y = y+tileSize*2;
        post->width = tileSize*2;
        post->height = height-tileSize*2;
        post->loadGraphic(res.graphic(ImgCrane2));
        counterweight->x = x+8;
        counterweight->y = y+4;
        cabin->x = x+cx-8;
        cabin->y = y-9;
        cabin->width = 48;
        cabin->setFacing(RIGHT);
        pulley->x = x+cx+64+FlxU::random()*(width-cx-128);
        pulley->y = y+20;
        //antennas
        antenna1->x = x-8+(40-16)/2;
        antenna1->y = y-ah+40;
        antenna2->x = x+cx-8+(40-16)/2;
        antenna2->y = y-ah+40;
        antenna3->x = x+width-24+(40-16)/2;
        antenna3->y = y-ah+40;
    } else {
        post->x = x+width-cx-tileSize*2;
        post->y = y+tileSize*2;
        post->width = tileSize*2;
        post->height = height-tileSize*2;
        post->loadGraphic(res.graphic(ImgCrane2));
        counterweight->x = x+width-72;
        counterweight->y = y+4;
        cabin->x = x+width-cx-40;
        cabin->y = y-9;
        cabin->width = 48;
        cabin->setFacing(LEFT);
        pulley->x = x+FlxU::random()*(width-cx-128);
        pulley->y = y+20;
        //antennas
        antenna1->x = x-8+(40-16)/2;
        antenna1->y = y-ah+40;
        antenna2->x = x+width-cx-24+(40-16)/2;
        antenna2->y = y-ah+40;
        antenna3->x = x+width-24+(40-16)/2;
        antenna3->y = y-ah+40;
    }
}


void Crane::render()
{
    //turn off blending!
    // glDisable(GL_BLEND);
    post->render();
    // glEnable(GL_BLEND);
    beam->render();
    counterweight->render();
    cabin->render();
    pulley->render();
    antenna1->render();
    antenna2->render();
    antenna3->render();
}

void Crane::update()
{
    post->update();
    beam->update();
    counterweight->update();
    cabin->update();
    pulley->update();
    antenna1->update();
    antenna2->update();
    antenna3->update();
}

