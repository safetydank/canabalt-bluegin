#include "bluegin/resourcemanager.h"
#include "flx/flx.h"
#include "flx/flxG.h"

#include "Window.h"
#include "Player.h"

const float WindowW = 3.0f;

static const char* SndWindow1 = "window1";
static const char* SndWindow2 = "window2";

using namespace ci;
using namespace bluegin;
using namespace flx;

extern FlxGlobal FlxG;

WindowPtr Window::create(Vec2f point, float height, Player* player, EmitterPtr shards)
{
    return WindowPtr(new Window(point, height, player, shards));
}

Window::Window(Vec2f point, float Height, Player* plr, EmitterPtr glassShards)
{
    createGraphic(WindowW, Height, FlxU::color(0xffffffff));

    // self.enableBlend = NO;

    x = point.x;
    y = point.y-Height;
    width = 40;

    player = plr;

    shards = glassShards;
    shards->x = x;
    shards->y = y;
    shards->setSize(WindowW, height);
    shards->delay = -3;
    shards->minRotation = -720*2.0;
    shards->maxRotation = 720*2.0;
    shards->gravity = 500;
}

void Window::update()
{
    ResourceManager& res = *(FlxG.resources);
    if (overlaps(*player)) {
        if (FlxU::random() < 0.5)
            FlxG.play(res.sound(SndWindow1));//TODO - set volume for sound effect to 0.35 // i think this has already been premixed?
        else
            FlxG.play(res.sound(SndWindow2));
        exists = false;
        shards->minParticleSpeed = Vec2f(player->velocity.x/2,
                player->velocity.y/2 - FlxU::random()*40);
        shards->maxParticleSpeed = Vec2f(shards->minParticleSpeed.x*3,
                shards->minParticleSpeed.y*3);
        shards->start();
    }
}

