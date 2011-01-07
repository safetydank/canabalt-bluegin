#include "bluegin/resourcemanager.h"
#include "flx/flxG.h"
#include "Player.h"

using namespace ci;
using namespace bluegin;
using namespace flx;

extern FlxGlobal FlxG;

Player::Player() : Sprite(0, 0), stumble(false), pause(false), craneFeet(false)
{
    ResourceManager& res = *(FlxG.resources);
    loadGraphic(res.graphic("player2"), true, false, 30, 30);
    offset.x = 6;
    offset.y = 12;
    x = 0;
    y = 80-14;
    width = 16;
    height = 18;

    int run[]  = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
    int run4[] = { 0, 2, 4, 6, 8, 10, 12, 14 };
    addAnimation("run1", 16, run, 15);
    addAnimation("run2", 16, run, 28);
    addAnimation("run3", 16, run, 40);
    addAnimation("run4", 8, run4, 30);

    int jump[] = { 16, 17, 18, 19 };
    addAnimation("jump", 4, jump, 12);

    int fall[] = { 20, 21, 22, 23, 24, 25, 26 };
    addAnimation("fall", 7, fall, 14);

    int stumble[] = { 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37 };
    addAnimation("stumble1", 11, stumble, 14);
    addAnimation("stumble2", 11, stumble, 21);
    addAnimation("stumble3", 11, stumble, 28);
    addAnimation("stumble4", 11, stumble, 35);

    drag.x = 640;

    acceleration.x = 1;
    acceleration.y = 1200;
    maxVelocity.x = 1000;
    maxVelocity.y = 360;
    velocity.x = 125;
    velocity.y = 0;
    my = 0;

    fc = 0;
    // feet = [[NSArray alloc] initWithObjects:@"foot1.caf", @"foot2.caf", @"foot3.caf", @"foot4.caf", nil];
    // feetC = [[NSArray alloc] initWithObjects:@"footc1.caf", @"footc2.caf", @"footc3.caf", @"footc4.caf", nil];

    craneFeet = false;

    epitaph = string("fall");
}

Player::~Player()
{
}

void Player::update()
{
    ResourceManager& res = *(FlxG.resources);

    if (y > 484) {
        dead = true;
        return;
    }

    //walldeath
    if (acceleration.x <= 0) {
        Sprite::update();
        return;
    }

    //speed & acceleration
    if (velocity.x < 0) velocity.x = 0;
    else if (velocity.x < 100) acceleration.x = 60;
    else if (velocity.x < 250) acceleration.x = 36;
    else if (velocity.x < 400) acceleration.x = 24;
    else if (velocity.x < 600) acceleration.x = 12;
    else acceleration.x = 4;

    //jumping
    jumpLimit = velocity.x / (maxVelocity.x * 2.5);
    if (jumpLimit > 0.35) jumpLimit = 0.35;

    // if (jump >= 0 && FlxG.touch.pressed() && !pause) {
    if (jump >= 0 && FlxG.touch.pressed() && !pause) {
        if (jump == 0) {
            //NSLog(@"starting a jump");
            int rs = FlxU::random() * 4;
            switch (rs) {
                // XXX get sound resources
                case 0: FlxG.play(res.sound("jump1")); break;
                case 1: FlxG.play(res.sound("jump2")); break;
                case 2: FlxG.play(res.sound("jump3")); break;
                default: break;
            }
        }
        jump += FlxG.elapsed;
        if (jump > jumpLimit) {
            //NSLog(@"force ending a jump");
            jump = -1;
        }
    } else
        jump = -1;

    if (jump > 0) {
        craneFeet = false;
        if (jump < 0.08)
            velocity.y = -maxVelocity.y*0.65;
        else
            velocity.y = -maxVelocity.y;
    }

    if (onFloor) {
        ft = (1-velocity.x/maxVelocity.x)*0.35;
        if (ft < 0.15) ft = 0.15;
        fc += FlxG.elapsed;
        if (fc > ft) {
            fc = 0;
            if (craneFeet) {
                // XXX
                // [FlxG play:[feetC getRandom]];
                craneFeet = false;
            } else {
                // XXX
                // [FlxG play:[feet getRandom]];
            }
        }
        if (stumble && finished) setStumble(false);
        if (!stumble) {
            if (velocity.x < 150) play("run1");
            else if (velocity.x < 300) play("run2");
            else if (velocity.x < 550) play("run3");
            else play("run4");
        }
    }
    else if (velocity.y < -140) {
        play("jump");
    }
    else if (velocity.y > -140) {
        play("fall");
        setStumble(false);
    }


    //update
    Sprite::update();

    if (velocity.y == maxVelocity.y)
        my += FlxG.elapsed;
}

void Player::hitBottom(Object& contact, float velocity)
{
    if (my > 0.16)
        setStumble(true);
    if (!FlxG.touch.pressed()) jump = 0;
    my = 0;
    Object::hitBottom(contact, velocity);
}

void Player::hitLeft(Object& contact, float velocity)
{
    ResourceManager& res = *(FlxG.resources);
    FlxG.play(res.sound("wall"));
    acceleration.x = 0;
    this->velocity.x = 0;
    maxVelocity.y = 1000;
    epitaph = "hit";
    Object::hitLeft(contact, velocity);
}

void Player::setStumble(bool stumbleValue)
{
    ResourceManager& res = *(FlxG.resources);
    stumble = stumbleValue;
    if (stumble) {
        FlxG.play(res.sound("tumble"), 0.3f);
        if (velocity.x > 500) play("stumble4", true);
        else if (velocity.x > 300) play("stumble3", true);
        else if (velocity.x > 150) play("stumble2", true);
        else play("stumble1", true);
    }
}


