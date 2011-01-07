#include "bluegin/resourcemanager.h"
#include "flx/flxG.h"
#include "GibEmitter.h"

using namespace ci;
using namespace bluegin;
using namespace flx;

extern FlxGlobal FlxG;

GibEmitter::GibEmitter(int gibCount) : Emitter(-100, -100)
{
    ResourceManager& res = *(FlxG.resources);
    this->gibCount = gibCount;
    createSprites(res.graphic("demo_gibs"), gibCount);
}
