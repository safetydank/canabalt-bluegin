#include "bluegin/resourcemanager.h"
#include "flx/flxG.h"

#include "Bomb.h"
#include "Player.h"
#include "Sequence.h"

using namespace ci;
using namespace bluegin;
using namespace flx;

extern FlxGlobal FlxG;

static const char* ImgBomb        = "bomb";
static const char* SndBombLaunch  = "bomb_launch";
static const char* SndBombPre     = "bomb_pre";
static const char* SndBombHit     = "bomb_hit";
static const char* SndBombExplode = "bomb_explode";

BombPtr Bomb::create(Vec2f Origin, Player* player, Sequence* sequence)
{
    ResourceManager& res = *(FlxG.resources);
    return BombPtr(new Bomb(Origin, player, sequence, res.graphic(ImgBomb)));
}

Bomb::Bomb(Vec2f Origin, Player* player, Sequence* sequence, Graphic graphic)
    : Sprite(0, 0, graphic)
{
    ResourceManager& res = *(FlxG.resources);

    x = Origin.x;
    y = -80;
    myY = Origin.y-30;
    p = player;
    // en = [entry retain];
    s = sequence;

    x -= width/2;
    height = 60;
    offset.x = 0;
    offset.y = 20;

    velocity.y = 1200;

    FlxG.play(res.sound(SndBombLaunch));
}

void Bomb::add(flx::EmitterPtr gibs)
{
    e = gibs;
}

void Bomb::update()
{
    ResourceManager& res = *(FlxG.resources);
    if (y <= -64)
        if (p->x > x-480) {
            FlxG.play(res.sound(SndBombPre));
        }
    if (p->x > x-480)
        Sprite::update();
    if (velocity.y > 0) {
        if (y > myY) {
            velocity.y = 0;
            y = myY;
            angularVelocity = FlxU::random()*120-60;
            angularDrag = abs(angularVelocity);
            //[e resetWithParam1:0 param2:0];
            e->start();
            if (FlxG.iPad)
                FlxG.quake.start(0.1f, 0.15f);
            else
                FlxG.quake.start(0.05f, 0.15f);
            int i = 0;
            // for (FlxSprite * sprite in en) {
            //     sprite.x = self.x-16 + i*8;
            //     sprite.y = myY + 16 + FlxU.random*8;
            //     [sprite randomFrame];
            //     ++i;
            // }
            FlxG.play(res.sound(SndBombHit));
            // [FlxG vibrate];
        }
    } else if (overlaps(*p)) { //player death
        FlxG.play(res.sound(SndBombExplode));
        // [FlxG vibrate];
        p->y = 600;
        p->epitaph = "bomb";
        // XXX not implemented
        // [s performSelector:@selector(aftermath)
        //     withObject:nil
        //     afterDelay:0.0];
    }

}

