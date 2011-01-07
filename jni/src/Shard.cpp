#include "bluegin/resourcemanager.h"
#include "bluegin/graphic.h"
#include "flx/flxG.h"

#include "Shard.h"

using namespace ci;
using namespace bluegin;
using namespace flx;

extern FlxGlobal FlxG;

static const char* SndGlass1 = "glass1";
static const char* SndGlass2 = "glass2";
static const char* shardSounds[] = { SndGlass1, SndGlass2 };

Shard::Shard(Graphic graphic) : Sprite(0, 0, graphic)
{
    makesSound = FlxU::random() > 0.8f;
}

void Shard::hitBottom(Object& contact, float vel)
{
    ResourceManager& res = *(FlxG.resources);

    if (makesSound && velocity.y > 120)
        FlxG.play(res.sound(shardSounds[FlxU::random() > 0.5 ? 0 : 1]));
    velocity.x *= 0.5+FlxU::random()*0.6;
    velocity.y *= -0.2-FlxU::random()*0.3;
    int vy = velocity.y*3;
    angularVelocity = (FlxU::random()*vy-vy*2)/16.0 * 100;
}

ShardEmitter::ShardEmitter(int count) : Emitter(0, 0)
{
    ResourceManager& res = *(FlxG.resources);

    //  Add shards to emitter
    SpritePtr s;
    float sw;
    float sh;

    float Collide = 0.5f;
    for (int i=0; i < count; ++i) {
        s = SpritePtr(new Shard(res.graphic("shard")));
        sw = s->width;
        sh = s->height;
        s->width  *= Collide;
        s->height *= Collide;
        s->offset.x = (sw - s->width)/2;
        s->offset.y = (sh - s->height)/2;
        s->solid = true;
        s->exists = false;
        s->scrollFactor = scrollFactor;
        s->scale = Vec2f(1.25f - FlxU::random(), 1.25f - FlxU::random());
        s->offset.set(0,-1);
        add(s);
    }
}

