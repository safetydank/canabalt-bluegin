#include "bluegin/resourcemanager.h"
#include "rdv/MenuState.h"
#include "rdv/PlayState.h"
#include "flx/flxG.h"

using namespace ci;
using namespace bluegin;
using namespace flx;

extern FlxGlobal FlxG;

void onFade(void*)
{
    FlxG.setState(StatePtr(new PlayState()));
}

static void onStart(void* data)
{
    FlxG.flash.start(Color(1.0f, 1.0f, 1.0f),0.5f);
    FlxG.fade.start(Color::black(),1,onFade);
}

void MenuState::create()
{
    FlxG.score = 0;
    ResourceManager& res = *(FlxG.resources);

    t1 = Text::create(FlxG.width/2 - 320, 20, 640, "Rendezvous");
    t1->setSize(80.0f);
    t1->setColor(FlxU::color(0xFF4744));
    t1->setAlignment(ALIGN_CENTER);
    add(t1);

    TextPtr t1, t2;
    b1 = Button::create(FlxG.width / 2 - 90, 200, onStart);
    SpritePtr image = Sprite::create();
    image->createGraphic(180, 64, FlxU::color(0x5F5DB7));
    SpritePtr imageHi = Sprite::create();
    imageHi->createGraphic(image->width, image->height, FlxU::color(0x8482FF));
    b1->loadGraphic(image, imageHi);
    t1 = Text::create(1, 5, 178, "Start");
    t1->setColor(Color::white());
    t1->setSize(56.0f);
    t1->setAlignment(ALIGN_CENTER);
    t2 = Text::create(t1->x,t1->y,t1->width,t1->getText());
    t2->setColor(Color::white());
    t2->setAlignment(t1->getAlignment());
    t2->setSize(t1->getSize());
    b1->loadText(t1,t2);
    add(b1);

    FlxG.flash.start(Color::black(),1.0f);
}

void MenuState::update()
{
    State::update();
}

