#include "bluegin/resourcemanager.h"
#include "flx/flx.h"
#include "flx/flxG.h"
#include "flx/render.h"
#include "cinder/Rand.h"

#include <algorithm>

#include "Dove.h"
#include "Player.h"

static const char* ImgDove  = "dove";
static const char* SndFlap1 = "flap1";
static const char* SndFlap2 = "flap2";
static const char* SndFlap3 = "flap3";

static const char* flaps[] = { SndFlap1, SndFlap2, SndFlap3 };

using namespace ci;
using namespace bluegin;
using namespace flx;

extern FlxGlobal FlxG;

DoveGroupPtr DoveGroup::create(int DoveCount)
{
    ResourceManager& res = *(FlxG.resources);
    return DoveGroupPtr(new DoveGroup(res.graphic(ImgDove), DoveCount));
}

DoveGroup::DoveGroup(Graphic graphic, int DoveCount)
    : graphic(graphic)
{
    doveCount = DoveCount;
    for (int i=0; i<doveCount; i++) {
        DovePtr dove(new Dove(graphic));
        dove->active = false;
        add(dove);
    }
    visibleDoves = 0;
}

void DoveGroup::render()
{
    //  Set the batch state for all doves first
    BatchState batch(graphic.getTexture(), false);
    FlxG.renderer->setBatchState(batch);
    for (vector<ObjectPtr>::iterator it = members.begin(); it != members.end(); ++it) {
        if ((*it)->active)
            (*it)->render();
        else
            break;
    }
    // FlxG.renderer->drawBatch();
    // Group::render();
}

void DoveGroup::setVisibleDoves(int VisibleDoves)
{
    visibleDoves = (VisibleDoves > doveCount) ? doveCount : VisibleDoves;
    for (int i=visibleDoves; i < members.size(); ++i) {
        members[i]->active = false;
    }
}

void Dove::initialize()
{
    // XXX
    // flaps = [[NSArray alloc] initWithObjects:SndFlap1, SndFlap2, SndFlap3, nil];
}

Dove::Dove(Graphic gfx) : Sprite(0, 0)
{
    loadGraphic(gfx, true, false, graphic.getHeight(), graphic.getHeight()); 

    int idle[] = { 3 };
    addAnimation("idle", 1, idle);

    int start = FlxU::random() * 3;
    int fly[] = { start, (start+1) % 3, (start+2) % 3 };
    addAnimation("fly", 3, fly, 15);
    setFacing(FlxU::random() > 0.5f ? LEFT : RIGHT);

    play("idle");
}

void Dove::setTrigger(float trgr)
{
    trigger = trgr + FlxU::random()*(x-trgr)*0.5;
}

void Dove::update()
{
    ResourceManager& res = *(FlxG.resources);

    if (player->x > trigger) {
        if (velocity.y == 0) {
            if (FlxU::random() < 0.5) FlxG.play(res.sound(flaps[Rand::randInt(0, 3)]));
            play("fly");
            velocity.y = -50 - FlxU::random()*50;
            acceleration.y = -50 - FlxU::random()*300;
            int vel = (player->velocity.x-300)*FlxU::random();
            acceleration.x = (getFacing() == RIGHT) ? vel : -vel;
        }
    }
    Sprite::update();
    // [self setupVertices];
}

void Dove::render()
{
    //  Identical to Sprite::render() except we don't bind the dove texture
    //  (already bound via DoveGroup::render()) and we don't xform the quad

    if (!onScreen())
        return;

    // getScreenXY(_point);

    //  draw
    Rectf texRect = graphic.mapFrameRect(frameRect, (getFacing() == LEFT));
    Vec2f pt(_point.x, _point.y);
    FlxG.renderer->renderQuad(mColor, getFrameWidth(), getFrameHeight(), texRect, NULL, &pt);
}

