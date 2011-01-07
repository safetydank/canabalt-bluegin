#include "bluegin/resourcemanager.h"
#include "flx/flxG.h"
#include "Billboard.h"

static const char* ImgBillboardTopMiddle = "billboard_top-middle";
static const char* ImgBillboardTopLeft = "billboard_top-left";
static const char* ImgBillboardTopRight = "billboard_top-right";

static const char* ImgBillboardMiddleLeft = "billboard_middle-left";
static const char* ImgBillboardMiddleRight = "billboard_middle-right";

static const char* ImgBillboardBottomMiddle = "billboard_bottom-middle";
static const char* ImgBillboardBottomLeft = "billboard_bottom-left";
static const char* ImgBillboardBottomRight = "billboard_bottom-right";

static const char* ImgBillboardCatwalkMiddle = "billboard_catwalk-middle";
static const char* ImgBillboardCatwalkLeft = "billboard_catwalk-left";
static const char* ImgBillboardCatwalkRight = "billboard_catwalk-right";
//static NSString * ImgBillboardPost = "billboard_post";
static const char* ImgBillboardPost2 = "billboard_post2";
static const char* ImgBillboardDmg1 = "billboard_dmg1-filled";
static const char* ImgBillboardDmg2 = "billboard_dmg2-filled";
static const char* ImgBillboardDmg3 = "billboard_dmg3-filled";

static const float TILE_SIZE = 16.0;
static const float HALL_HEIGHT = 8*16.0*2;

using namespace ci;
using namespace bluegin;
using namespace flx;

extern FlxGlobal FlxG;

Billboard::Billboard(float maxWidth)
{
    ResourceManager& res = *(FlxG.resources);

    post = SpritePtr(new Sprite());
    postTop = SpritePtr(new Sprite(0,0,res.graphic(ImgBillboardPost2)));
    bottomEdge = RepeatBlockPtr(new RepeatBlock(0, 0, 0, 0));
    bottomEdge->width = maxWidth-TILE_SIZE*4;
    bottomEdge->height = TILE_SIZE*2;
    bottomEdge->loadGraphic(res.graphic(ImgBillboardBottomMiddle));
    bottomLeftCorner = SpritePtr(new Sprite(0, 0, res.graphic(ImgBillboardBottomLeft)));
    bottomRightCorner = SpritePtr(new Sprite(0, 0, res.graphic(ImgBillboardBottomRight)));
    center = SpritePtr(new Sprite());
    leftEdge = RepeatBlockPtr(new RepeatBlock(0, 0, 0, 0));
    leftEdge->width = TILE_SIZE*2;
    leftEdge->height = HALL_HEIGHT-TILE_SIZE*2;
    leftEdge->loadGraphic(res.graphic(ImgBillboardMiddleLeft));
    rightEdge = RepeatBlockPtr(new RepeatBlock(0, 0, 0, 0));
    rightEdge->width = TILE_SIZE*2;
    rightEdge->height = HALL_HEIGHT-TILE_SIZE*2;
    rightEdge->loadGraphic(res.graphic(ImgBillboardMiddleRight));
    topEdge = RepeatBlockPtr(new RepeatBlock(0, 0, 0, 0));
    topEdge->width = maxWidth-TILE_SIZE*4;
    topEdge->height = TILE_SIZE*2;
    topEdge->loadGraphic(res.graphic(ImgBillboardTopMiddle));
    topLeftCorner = SpritePtr(new Sprite(0, 0, res.graphic(ImgBillboardTopLeft)));
    topRightCorner = SpritePtr(new Sprite(0, 0, res.graphic(ImgBillboardTopRight)));
    catwalkMiddle = RepeatBlockPtr(new RepeatBlock(0, 0, 0, 0));
    catwalkMiddle->width = maxWidth-TILE_SIZE*2;
    catwalkMiddle->height = 13;
    catwalkMiddle->loadGraphic(res.graphic(ImgBillboardCatwalkMiddle));
    catwalkLeft = SpritePtr(new Sprite(0, 0, res.graphic(ImgBillboardCatwalkLeft)));
    catwalkRight = SpritePtr(new Sprite(0, 0, res.graphic(ImgBillboardCatwalkRight)));
    damage = SpritePtr(new Sprite());
}

void Billboard::create(float X, float Y, float Width, float Height, float tileSize, int hallHeight)
{
    ResourceManager& res = *(FlxG.resources);

    x = X;
    y = Y;
    width = Width;
    height = Height;

    post->x = x+width/2-tileSize+3;
    post->y = y;
    post->createGraphic((tileSize*2)-3*2, height, FlxU::color(0x4d4d59));

    postTop->x = x+width/2-tileSize;
    postTop->y = y+12;

    bottomEdge->x = x+tileSize*2;
    bottomEdge->y = y-tileSize*2;
    bottomEdge->width = width-tileSize*4;
    bottomEdge->height = tileSize*2;
    bottomEdge->loadGraphic(res.graphic(ImgBillboardBottomMiddle));

    bottomLeftCorner->x  = x+1;
    bottomLeftCorner->y  = y-tileSize*2;
    bottomRightCorner->x = x+width-tileSize*2;
    bottomRightCorner->y = y-tileSize*2;

    center->x = x+tileSize*2-1;
    center->y = y-hallHeight+tileSize*2;
    center->createGraphic((width-tileSize*4)+2, hallHeight-tileSize*4, FlxU::color(0x868696));

    leftEdge->x = x+1;
    leftEdge->y = y-hallHeight+tileSize*2;
    leftEdge->width = tileSize*2;
    leftEdge->height = hallHeight-tileSize*4;
    leftEdge->loadGraphic(res.graphic(ImgBillboardMiddleLeft));
    rightEdge->x = x+width-tileSize*2-1;
    rightEdge->y = y-hallHeight+tileSize*2;
    rightEdge->width = tileSize*2;
    rightEdge->height = hallHeight-tileSize*4;
    rightEdge->loadGraphic(res.graphic(ImgBillboardMiddleRight));


    topEdge->x = x+tileSize*2;
    topEdge->y = y-hallHeight;
    topEdge->width = width-tileSize*4;
    topEdge->height = tileSize*2;
    topEdge->loadGraphic(res.graphic(ImgBillboardTopMiddle));
    topLeftCorner->x = x+1;
    topLeftCorner->y = y-hallHeight;
    topRightCorner->x = x+width-tileSize*2;
    topRightCorner->y = y-hallHeight;

    catwalkMiddle->x = x+tileSize;
    catwalkMiddle->y = y;
    catwalkMiddle->width = width-tileSize*2;
    catwalkMiddle->height = 13;
    catwalkMiddle->loadGraphic(res.graphic(ImgBillboardCatwalkMiddle));
    catwalkLeft->x = x;
    catwalkLeft->y = y;
    catwalkRight->x = x+width-tileSize;
    catwalkRight->y = y;

    //Damage decals
    int padding = 6;
    int third = (width-tileSize*4) / 3;
    if (FlxU::random() < 0.5)
    {
        if (FlxU::random() < 0.65) {
            damage->x = x+padding+(int)(FlxU::random()*third);
            damage->y = y+padding-hallHeight+(int)(FlxU::random()*(hallHeight-3*tileSize-padding*2));
            damage->loadGraphic(res.graphic(ImgBillboardDmg1));
        }
        if (FlxU::random() < 0.35) {
            damage->x = x+third+(int)(FlxU::random()*third);
            damage->y = y+padding-hallHeight+(int)(FlxU::random()*(hallHeight-3*tileSize-padding*2));
            damage->loadGraphic(res.graphic(ImgBillboardDmg2));
        }
        if (FlxU::random() < 0.65) {
            damage->x = x-padding+third+third+(int)(FlxU::random()*third);
            damage->y = y+padding-hallHeight+(int)(FlxU::random()*(hallHeight-3*tileSize-padding*2));
            damage->loadGraphic(res.graphic(ImgBillboardDmg3));
        }
    }
    else
    {
        if (FlxU::random() < 0.65) {
            damage->x = x+padding+(int)(FlxU::random()*third);
            damage->y = y+padding-hallHeight+(int)(FlxU::random()*(hallHeight-3*tileSize-padding*2));
            damage->loadGraphic(res.graphic(ImgBillboardDmg3));
        }
        if (FlxU::random() < 0.35) {
            damage->x = x+third+(int)(FlxU::random()*third);
            damage->y = y+padding-hallHeight+(int)(FlxU::random()*(hallHeight-3*tileSize-padding*2));
            damage->loadGraphic(res.graphic(ImgBillboardDmg2));
        }
        if (FlxU::random() < 0.65) {
            damage->x = x-padding+third+third+(int)(FlxU::random()*third);
            damage->y = y+padding-hallHeight+(int)(FlxU::random()*(hallHeight-3*tileSize-padding*2));
            damage->loadGraphic(res.graphic(ImgBillboardDmg1));
        }
    }

}

void Billboard::render()
{
    // glDisable(GL_BLEND);
    post->render();
    topEdge->render();
    leftEdge->render();
    rightEdge->render();
    center->render();
    bottomEdge->render();
    bottomLeftCorner->render();
    bottomRightCorner->render();
    damage->render();
    catwalkMiddle->render();
    // glEnable(GL_BLEND);

    postTop->render();
    topLeftCorner->render();
    topRightCorner->render();
    catwalkLeft->render();
    catwalkRight->render();
}

void Billboard::update()
{
    Object::update();
    post->update();
    postTop->update();
    bottomEdge->update();
    topEdge->update();
    leftEdge->update();
    rightEdge->update();
    center->update();
    topRightCorner->update();
    topLeftCorner->update();
    bottomRightCorner->update();
    bottomLeftCorner->update();
    catwalkMiddle->update();
    catwalkLeft->update();
    catwalkRight->update();
    damage->update();
}


