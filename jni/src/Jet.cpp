#include "bluegin/resourcemanager.h"
#include "flx/flx.h"
#include "flx/flxG.h"
#include "Jet.h"

using namespace bluegin;
using namespace flx;

extern FlxGlobal FlxG;

Jet::Jet(Graphic graphic) : Sprite(0, 0, graphic)
{
    x = -500;
    scrollFactor.x = 0;
    scrollFactor.y = 0.3;
    timer = 0;
    limit = 12+FlxU::random()*4;
    velocity.x = -1200;
    velocity.y = 0;
}

void Jet::update()
{
    ResourceManager& res = *(FlxG.resources);
    timer += FlxG.elapsed;
    if (timer > limit) {
        x = 960;
        y = -20 + FlxU::random()*120;
        if (FlxG.iPad)
            FlxG.quake.start(0.02f, 1.5f);
        else
            FlxG.quake.start(0.01f, 1.5f);
        FlxG.play(res.sound("flyby"));
        timer = 0;
        limit = 10+FlxU::random()*20;
    }
    if (x < -width)
        return;
    Sprite::update();
}

