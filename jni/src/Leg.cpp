#include "bluegin/resourcemanager.h"
#include "flx/flxG.h"

#include "Leg.h"
#include "Sequence.h"

using namespace ci;
using namespace bluegin;
using namespace flx;

extern FlxGlobal FlxG;

static const char* ImgLeg = "giant_leg_bottom";
static const char* ImgLegTop = "giant_leg_top";

static const char* SndLegLaunch = "giant_leg";
static const char* SndLegRelease = "giant_leg_release";
static const char* SndBombPre = "bomb_pre";
static const char* SndBombHit = "bomb_hit";
static const char* SndBombExplode = "bomb_explode";

LegPtr Leg::get(Vec2f Origin, Player* player, Sequence* sequence)
{
    ResourceManager& res = *(FlxG.resources);
    return LegPtr(new Leg(Origin, player, sequence, res.graphic(ImgLeg)));
}

Leg::Leg(Vec2f Origin, Player* player, Sequence* sequence, Graphic graphic)
    : Sprite(0, 0, graphic)
{
    ResourceManager& res = *(FlxG.resources);
    origin.x = Origin.x-64;
    origin.y = -480;

    x = origin.x;
    y = origin.y;
    myY = Origin.y+2;
    p = player;
    s = sequence;

    // top = [[FlxSprite spriteWithX:self.x y:-480 graphic:ImgLegTop] retain];
    top = Sprite::create(x, -480, res.graphic(ImgLegTop));

    velocity.y = 1600;

    FlxG.play(res.sound(SndLegLaunch));
}

void Leg::add(flx::EmitterPtr gibs)
{
    e = gibs;
}

void Leg::update()
{
    ResourceManager& res = *(FlxG.resources);
    if (y <= -64)
        if (p->x > x-480) {
            FlxG.play(res.sound(SndBombPre));
        }
    if (p->x > x-480)
        Sprite::update();
    if (velocity.y > 0)
    {
        if (y > myY)    
        {
            velocity.y = 0;
            y = myY;
            //[e resetWithParam1:0 param2:0];
            e->start();
            if (FlxG.iPad)
                FlxG.quake.start(0.35f, 0.2f);
            else
                FlxG.quake.start(0.25f, 0.2f);
            FlxG.play(res.sound(SndBombHit));
            FlxG.play(res.sound(SndBombExplode));
            FlxG.play(res.sound(SndLegRelease));
            // FlxG.vibrate();
            s->stomp();
        }
    }
    top->x = x - (x - p->x)/16;
    top->y = y - 400 - (480-(x - p->x))/8;
}

void Leg::render()
{
    top->render();
    Sprite::render();
}

