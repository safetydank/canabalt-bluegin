#include "flx/flxG.h"
#include "flx/flx.h"
#include "BG.h"

using namespace ci;
using namespace bluegin;
using namespace flx;

extern FlxGlobal FlxG;

BG::BG(float x, float y, Graphic graphic) : Sprite(x, y, graphic)
{
    random = false;
}

void BG::update()
{
    Vec2d _point = getScreenXY(_point);
    if (_point.x + width < 0) {
        if (random) {
            x += FlxG.width*10 + FlxU::random()*FlxG.width*10;
            scrollFactor.x = 2+FlxU::random()*3;
        } else 
            x += width*2;
    }
}

