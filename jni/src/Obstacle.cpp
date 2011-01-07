#include "bluegin/resourcemanager.h"
#include "flx/flxG.h"

#include "Obstacle.h"
#include "Player.h"

static const char* ImgObstacles1 = "obstacles";
static const char* ImgObstacles2 = "obstacles2";
static const char* SndOb1 = "obstacle1";
static const char* SndOb2 = "obstacle2";
static const char* SndOb3 = "obstacle3";

using namespace ci;
using namespace bluegin;
using namespace flx;

extern FlxGlobal FlxG;

ObstaclePtr Obstacle::create(ci::Vec2f origin, Player* player, bool alt)
{
    return ObstaclePtr(new Obstacle(origin, player, alt));
}

Obstacle::Obstacle(ci::Vec2f origin, Player* player, bool alt)
: Sprite(origin.x, origin.y)
{
    ResourceManager& res = *(FlxG.resources);

    loadGraphic(res.graphic(alt ? ImgObstacles2 : ImgObstacles1), true);
    randomFrame();
    height = 2;
    offset = Vec2f(offset.x, 16);
    y -= height;
    p = player;
}

void Obstacle::update()
{
    ResourceManager& res = *(FlxG.resources);

    if (!dead && overlaps(*p)) {
        p->setStumble(true);
        p->velocity = Vec2f(p->velocity.x*0.7, p->velocity.y);
        int rs = FlxU::random() * 3;
         switch (rs) {
         case 0: FlxG.play(res.sound(SndOb1)); break;
         case 1: FlxG.play(res.sound(SndOb2)); break;
         case 2: FlxG.play(res.sound(SndOb3)); break;
         default: break;
         }
        velocity.x = p->velocity.x + FlxU::random() * 100 - 50;
        velocity.y = -120;
        acceleration.y = 320;
        kill();
    }

    Sprite::update();
}

void Obstacle::hitBottom(Object& obj, float Velocity)
{
    velocity.y = -velocity.y / 4;
}

void Obstacle::kill()
{
    dead = true;
    flicker(0);
    angularVelocity = FlxU::random() * 720 - 360;
}


