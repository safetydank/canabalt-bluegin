#include "bluegin/resourcemanager.h"
#include "flx/flxG.h"
#include "Walker.h"

using namespace ci;
using namespace bluegin;
using namespace flx;

extern FlxGlobal FlxG;

static const char* ImgWalker = "walker2";

static int s;

WalkerPtr Walker::create(vector<flx::EmitterPtr>& smokeArray)
{
    return WalkerPtr(new Walker(smokeArray));
}

Walker::Walker(vector<flx::EmitterPtr>& smokeArray)
    : smoke(smokeArray)
{
    ResourceManager& res = *(FlxG.resources);
    loadGraphic(res.graphic(ImgWalker), true, false, 120, 80);

    firing = false;
    walkTimer = 0.0;
    idleTimer = 0.0;

    x = -500;
    y = 40+FlxU::random()*10;

    width = 120;
    height = 80;

    // smoke = [smokeArray retain];

    scrollFactor.x = 0.1;
    scrollFactor.y = 0.15;

    int idle[] = { 0 };
    addAnimation("idle", 1, idle);
    int walk[] = { 0, 1, 2, 3, 4, 5 };
    addAnimation("walk", 6, walk, 8);
    int fire[] = { 6, 7, 8, 9, 10, 11 };
    addAnimation("fire", 6, fire, 8, false);
    play("idle");
}

void Walker::update()
{
    if (walkTimer > 0) {
        walkTimer -= FlxG.elapsed;
        if (walkTimer <= 0) {
            play("fire");
            firing = true;
            velocity.x = 0;
            if (++s >= smoke.size())
                s = 0;
            EmitterPtr se = smoke.at(s);
            se->x = x + ((getFacing() == 0) ? (width-22) : 10);
            se->y = y + height;
            //[se resetWithParam1:0 param2:0];
            se->start(false);
        }
    } else if (firing) {
        if (finished) {
            firing = false;
            idleTimer = 1 + FlxU::random()*2;
            play("idle");
        }
    } else if (idleTimer > 0) {
        idleTimer -= FlxG.elapsed;
        if (idleTimer <= 0) {
            if (FlxU::random() < 0.5) {
                walkTimer = 2 + FlxU::random()*4;
                play("walk");
                velocity.x = (getFacing() == 0 ? 40 : -40);
            } else {
                play("fire");
                firing = true;
                if (++s >= smoke.size())
                    s = 0;
                EmitterPtr se = smoke.at(s);
                se->x = x + ((getFacing() == 0) ? (width-22) : 10);
                se->y = y + height;
                //[se resetWithParam1:0 param2:0];
                se->start(false);
            }
        }
    }

    Vec2d p = getScreenXY(p);
    if (p.x + width*2 < 0) { //added *2 factor
        walkTimer = FlxU::random()*2;
        setFacing(FlxU::random() > 0.5 ? RIGHT : LEFT);
        x = x + FlxG.width + width*2 + FlxU::random()*FlxG.width; //added *2 factor
    }
    Sprite::update();
}

