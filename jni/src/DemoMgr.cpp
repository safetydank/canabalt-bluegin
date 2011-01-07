#include "bluegin/resourcemanager.h"
#include "flx/flxG.h"
#include "flx/emitter.h"

#include "DemoMgr.h"
#include "Player.h"

using namespace bluegin;
using namespace ci;
using namespace flx;

extern FlxGlobal FlxG;

static const char* SndCrumble = "crumble";

DemoMgrPtr DemoMgr::create(float X, Player* player, vector<ObjectPtr>& children)
{
    return DemoMgrPtr(new DemoMgr(X, player, children)); 
}

DemoMgr::DemoMgr(float x, Player* player, vector<ObjectPtr>& children)
    : Object(x, 0, 0, 0), c(children)
{
    p = player;
    maxVelocity.y = 300;
    velocity.y = 60;
    acceleration.y = 40;
    go = false;
}

void DemoMgr::add(flx::ObjectPtr object)
{
    c.push_back(object);
}

void DemoMgr::update()
{
    ResourceManager& res = *(FlxG.resources);

    if (!go) {
        if (p->x + p->width >= x && y < 480) {
            go = true;
            FlxG.play(res.sound(SndCrumble));
            if (FlxG.iPad)
                FlxG.quake.start(0.01f, 3.0f);
            else
                FlxG.quake.start(0.005f, 3.0f);

            //  XXX type check
            //assume the last object is an emitter
            ObjectPtr obj = c.back();
            // if ([e isKindOfClass:[FlxEmitter class]])
            if (true) {
                Emitter& e = static_cast<Emitter&>(*obj);
                e.start(false);
            }

            for (vector<ObjectPtr>::iterator it = c.begin(); it != c.end(); ++it) {
                Object& object = **it;
                object.maxVelocity  = Vec2f(object.maxVelocity.x, maxVelocity.y);
                object.velocity     = Vec2f(object.velocity.x, 60);
                object.acceleration = Vec2f(object.acceleration.x, 40);
            }
        }
    }
    if (go) {
        //     CGFloat oy = y;
        //     [super update];
        //     CGFloat ny = y;
        //     for (FlxObject * object in c) {
        //       object.y += ny - oy;
        //     }

        //     for (FlxObject * object in c)
        //       [object update];
        // FlxG.vibrate();

        if(y > 480)
            go = false;
    }
}
