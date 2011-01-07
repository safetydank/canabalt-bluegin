#include "bluegin/resourcemanager.h"
#include "flx/flxG.h"

#include "Smoke.h"

static const char* ImgSmoke = "smoke";

using namespace ci;
using namespace bluegin;
using namespace flx;

extern FlxGlobal FlxG;

SmokeEmitter::SmokeEmitter(int smokeCount) : Emitter(-100, -100)
{
    ResourceManager& res = *(FlxG.resources);
    this->smokeCount = smokeCount;
    createSprites(res.graphic(ImgSmoke), smokeCount);
}

