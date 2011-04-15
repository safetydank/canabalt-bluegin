#include "bluegin/resourcemanager.h"
#include "flx/flxG.h"

#include "PlayState.h"
#include "Hall.h"
#include "HUD.h"
#include "Jet.h"
#include "Sequence.h"
#include "Shard.h"
#include "Smoke.h"
#include "Walker.h"

using namespace ci;
using namespace bluegin;
using namespace flx;

extern FlxGlobal FlxG;

static const char* MusicRun          = "run";
static const char* SndCrumble        = "crumble";

static const char* ImgMidground1     = "midground1-trimmed";
static const char* ImgMidground2     = "midground2-trimmed";
static const char* ImgBackground     = "background-trimmed";
static const char* ImgMidground1IPad = "midground1-trimmed.ipad";
static const char* ImgMidground2IPad = "midground2-trimmed.ipad";
static const char* ImgBackgroundIPad = "background-trimmed.ipad";
static const char* ImgMothership     = "mothership-filled";
static const char* ImgDarkTower      = "dark_tower-filled";
static const char* ImgGirder1        = "girder-tall";
static const char* ImgGameOver       = "gameover";

static const char* ImgPauseButton    = "pause";
static const char* ImgPaused         = "paused";

static const char* ImgExitOn         = "gameover_exit_on";
static const char* ImgExitOff        = "gameover_exit_off";

#define GLASS_SHARDS
#define SMOKE

static int   frameCount = 0;
static float fpsElapsed = 0;

//  quake compensation
const int QUAKE_OVERHANG = 10;

void PlayState::doPause()
{
    paused = true;
    fadedSprite->visible = true;
    pausedSprite->visible = true;
    pauseButton->visible = false;
    // FlxG.pauseMusic();
}

void PlayState::setPaused(bool gamePaused)
{
    if (gamePaused) {
        doPause();
        //maybe do this on the next iteration?
        // FlxG.pauseFollow = true;
        // player.pause = true;
    }
}   

void PlayState::create()
{
    //  XXX one-off initialization, can we put it outside of create???
    //  Order of initialization is significant (!)
    Hall::initialize();
    Building::initialize();
    Sequence::initialize();

    bgColor = FlxU::color(0xffb0b0bf);

    FlxG.score = 0;
    ResourceManager& res = *(FlxG.resources);

    firstTimeThroughUpdateLoop = true;
    reallyJustPaused = false;

    pauseVisibility = true;

    int i;

    //Far BG 'Easter Egg' objects
    SpritePtr s = Sprite::create(0, 0, res.graphic(ImgMothership));
    // s->enableBlend = false;
    s->x = 900;
    s->scrollFactor = Vec2f(0.015, 0);
    add(s);
    s = Sprite::create(0, 0, res.graphic(ImgDarkTower));
    // s.enableBlend = false;
    s->x = 1700;
    s->scrollFactor = Vec2f(0.015,0);
    add(s);

    EmitterPtr e;

#ifdef SMOKE
    vector<EmitterPtr> smoke;

    if (!FlxG.iPhone1G && !FlxG.iPodTouch1G) {
        int numSmokes = 8;
        // int numSmokes = 4;
        if (FlxG.iPad)
            numSmokes = 8;
        if (FlxG.iPhone3G)
            numSmokes = 1;
        for (i=0; i<numSmokes; ++i) {
            // int num_clouds = 15;
            int num_clouds = 25;
            if (FlxG.iPad)
                num_clouds = 25;
            if (FlxG.iPhone3G)
                num_clouds = 7;

            e = SmokeEmitterPtr(new SmokeEmitter(num_clouds));
            for (vector<ObjectPtr>::iterator it = e->members.begin();
                    it != e->members.end(); ++it) {
                Sprite& s = static_cast<Sprite&>(**it);
                s.randomFrame();
                s.scrollFactor = Vec2f(0.1, 0.05);
                add(*it);
            }

            e->delay = 0.6;
            e->minParticleSpeed = Vec2f(-3,-15);
            e->maxParticleSpeed = Vec2f(3,-15);
            if(FlxG.iPhone3G || FlxG.iPhone1G || FlxG.iPodTouch1G)
            {
                e->minRotation = 0;
                e->maxRotation = 0;
            }
            else
            {
                e->minRotation = -30;
                e->maxRotation = 30;
            }
            e->gravity = 0;
            e->particleDrag = Vec2f(0,0);
            add(e);
            smoke.push_back(e);
        }
        add(Walker::create(smoke));
        if (!FlxG.iPhone3G)
            add(Walker::create(smoke));
    }
#endif

    BGPtr mg;
    SpritePtr bg; //for solid background rectangle...
    if (FlxG.iPad)
        mg = BGPtr(new BG(0, 0, res.graphic(ImgBackgroundIPad)));
    else
        mg = BGPtr(new BG(0, 0, res.graphic(ImgBackground)));

    mg->x = 0;
    mg->y = 30;
    mg->scrollFactor = Vec2f(0.15, 0.25);
    mg->y += 36;
    add(mg);
    background = mg;
    if (FlxG.iPad)
        mg = BGPtr(new BG(0, 0, res.graphic(ImgBackgroundIPad)));
    else
        mg = BGPtr(new BG(0, 0, res.graphic(ImgBackground)));
    mg->x = FlxG.width;
    mg->y = 30;
    mg->y += 36;
    mg->scrollFactor = Vec2f(0.15, 0.25);
    add(mg);
    //add below - since these are trimmed images
    bg = Sprite::create(0, 30+36+48);
    bg->x -= QUAKE_OVERHANG;
    if (FlxG.iPad)
        bg->createGraphic(FlxG.width + 2*QUAKE_OVERHANG, 156, FlxU::color(0x868696));
    else
        bg->createGraphic(FlxG.width + 2*QUAKE_OVERHANG, 76+12, FlxU::color(0x868696));
    bg->scrollFactor = Vec2f(0, 0.25); //don't scroll in the x direction at all!
    // bg->enableBlend = false;
    add(bg);
    backgroundRect = bg;

    if (FlxG.iPad)
        mg = BGPtr(new BG(0, 0, res.graphic(ImgMidground1)));
    else
        mg = BGPtr(new BG(0, 0, res.graphic(ImgMidground1)));
    mg->x = 0;
    mg->y = 104+8;
    mg->scrollFactor = Vec2f(0.4, 0.5);
    add(mg);
    midground = mg;
    if (FlxG.iPad)
        mg = BGPtr(new BG(0, 0, res.graphic(ImgMidground2IPad)));
    else
        mg = BGPtr(new BG(0, 0, res.graphic(ImgMidground2)));
    if (FlxG.iPad)
        mg->x = 512;
    else
        mg->x = 480;
    mg->y = 104+8;
    mg->scrollFactor = Vec2f(0.4, 0.5);
    add(mg);
    bg = Sprite::create(0, 104+8+97);
    bg->x -= QUAKE_OVERHANG;
    bg->createGraphic(FlxG.width+2*QUAKE_OVERHANG, 223, FlxU::color(0x646a7d));
    bg->scrollFactor = Vec2f(0, 0.5); //don't scroll in the x direction at all!
    // bg->enableBlend = false;
    add(bg);

    // [self add:[Jet jet]];
    add(JetPtr(new Jet(res.graphic("jet"))));

    focus = Sprite::create();
    FlxG.follow(focus, 15);
    FlxG.followBounds(0, 0, INT_MAX, 480);
    FlxG.followAdjust(1.5, 0);

    player = PlayerPtr(new Player());
    // player->play("run1");

    //Infinite level sequence objects
#ifdef GLASS_SHARDS
    // int numShards = 40;
    int numShards = 80;
    if (FlxG.iPad /*|| FlxG.retinaDisplay*/)
        numShards = 80;
    if (FlxG.iPhone1G)
        numShards = 20;
#else
    int numShards = 0;
#endif

    // shardsA = [ShardEmitter shardEmitterWithShardCount:numShards];
    // shardsB = [ShardEmitter shardEmitterWithShardCount:numShards];

    shardsA = EmitterPtr(new ShardEmitter(numShards));
    shardsB = EmitterPtr(new ShardEmitter(numShards));

    //  XXX shard placeholders using gib emitters
    // shardsA = EmitterPtr(new Emitter());
    // shardsA->createSprites(res.graphic("shard"), numShards, 0, false, 0.5f);
    // for (vector<ObjectPtr>::iterator it = shardsA->members.begin();
    //         it != shardsA->members.end(); ++it) {
    //     Sprite& sp = static_cast<Sprite&>(**it);
    //     sp.scale = Vec2f(1.25f - FlxU::random(), 1.25f - FlxU::random());
    //     sp.offset.set(0,-1);
    // }

    // shardsB = EmitterPtr(new Emitter());
    // shardsB->createSprites(res.graphic("shard"), numShards, 0, false, 0.6f);
    // for (vector<ObjectPtr>::iterator it = shardsB->members.begin();
    //         it != shardsB->members.end(); ++it) {
    //     Sprite& sp = static_cast<Sprite&>(**it);
    //     sp.scale = Vec2f(1.25f - FlxU::random(), 1.25f - FlxU::random());
    //     sp.offset.set(0,-1);
    // }

    Sequence::setCurIndex(0);
    Sequence::setNextIndex((int)(FlxU::random()*3+3));
    Sequence::setNextType(1);

    seqA = Sequence::get(player.get(), shardsA, shardsB);
    seqB = Sequence::get(player.get(), shardsA, shardsB);
    add(seqA);
    add(seqB);
    seqA->initSequence(seqB.get());
    seqB->initSequence(seqA.get());

    add(shardsA);
    add(shardsB);

    add(player);

    if (!(FlxG.iPhone3G || FlxG.iPhone1G || FlxG.iPodTouch1G)) {
        mg = BGPtr(new BG(0, 0, res.graphic(ImgGirder1)));
        mg->random = true;
        mg->x = 3000;
        mg->y = 0;
        mg->scrollFactor = Vec2f(3, 0);
        add(mg);
    }
    mg = BGPtr(new BG(0, 0, Graphic()));
    mg->createGraphic(32, FlxG.height, FlxU::color(0x35353d));
    // mg->enableBlend = false;
    mg->random = true;
    mg->x = 3000;
    mg->y = 0;
    mg->scrollFactor = Vec2f(4, 0);
    add(mg);

    dist = HUDPtr(new HUD(Rect(FlxG.width-80-5,2+3,80,16)));
    dist->scrollFactor = Vec2f(0, 0);
    dist->setDistance(0);
    add(dist);

    //need this to be above everything else
    // pauseButton = [FlxSprite spriteWithGraphic:ImgPauseButton];
    // pauseButton.x = 8;
    // pauseButton.y = 6;
    // pauseButton.scrollFactor = CGPointMake(0, 0);
    // if (pauseVisibility == false)
    //   pauseButton.visible = false;
    // [self add:pauseButton];
    // 
    // fadedSprite = [FlxSprite spriteWithX:0 y:0 graphic:nil];
    // [fadedSprite createGraphicWithWidth:FlxG.width height:FlxG.height color:0xffffff];
    // fadedSprite.scrollFactor = CGPointMake(0, 0);
    // fadedSprite.alpha = 0.5;
    // fadedSprite.visible = false;
    // [self add:fadedSprite];

    // pausedSprite = [FlxSprite spriteWithGraphic:ImgPaused];
    // pausedSprite.x = ([FlxG width]-pausedSprite.width)/2;
    // pausedSprite.y = ([FlxG height]-pausedSprite.height)/2;
    // pausedSprite.scrollFactor = CGPointMake(0, 0);
    // pausedSprite.visible = false;
    // [self add:pausedSprite];
    paused = false;

    if (FlxG.iPad)
        FlxG.quake.start(0.007, 3.1);
    else
        FlxG.quake.start(0.0065, 2.5);

    gameover = 0;

    bluegin_music_volume(0.8f, 0.8f);
    FlxG.playMusic(res.sound(MusicRun));
    FlxG.play(res.sound(SndCrumble));
}

void PlayState::update()
{
    ResourceManager& res = *(FlxG.resources);

    fpsElapsed += FlxG.elapsed;
    frameCount++;
    if (fpsElapsed > 1.0f) {
        Log("FPS: %d", frameCount);
        fpsElapsed = 0;
        frameCount = 0;
    }

    if (reallyJustPaused) {
        doPause();
    }
    reallyJustPaused = false;

    //check for pause touch
    // if (gameover == 0) {
    //     if (!paused) {
    //         if (FlxG.touches.touchesBegan &&
    //                 CGRectContainsPoint(pauseRect, FlxG.touches.screenTouchBeganPoint) &&
    //                 !firstTimeThroughUpdateLoop) {
    //             justPaused = true;
    //             reallyJustPaused = true;
    //             FlxG.pauseFollow = true;
    //             player.pause = true;
    //         }
    //     } else {
    //         if (FlxG.touches.touchesEnded) {
    //             if (justPaused) {
    //                 justPaused = false;
    //             } else {
    //                 player.pause = false;
    //                 paused = false;
    //                 fadedSprite.visible = false;
    //                 pausedSprite.visible = false;
    //                 if (pauseVisibility == true)
    //                     pauseButton.visible = true;
    //                 //start following again
    //                 FlxG.pauseFollow = false;
    //                 [FlxG unpauseMusic];
    //             }
    //         }
    //     }
    // }

    // if (pressedExit) {
    //     //still touching?
    //     //released in bounds?
    //     if (FlxG.touches.touchesEnded) {
    //         //switch state
    //         FlxG.state = [[[MenuState alloc] init] autorelease];
    //         return;
    //     }
    // }
    // pressedExit = false;

    if (exitOn && exitOff) {
        exitOff->visible = true;
        exitOn->visible = false;
    }

    if (gameover > 0)
        gameover += FlxG.elapsed;
    if (gameover > 0.35 && FlxG.touch.pressed()) {
        bool switchState = true;

    //     if (exitOn && exitOff) {
    //         if (CGRectContainsPoint(CGRectInset(CGRectMake(exitOff.x, exitOff.y, exitOff.width, exitOff.height), -20, -20), FlxG.touches.screenTouchPoint)) {
    //             //pressing button
    //             exitOff.visible = false;
    //             exitOn.visible = true;
    //             pressedExit = true;
    //             switchState = false;
    //         }
    //     }

        if (switchState) {
            FlxG.stopMusic();
            FlxG.setState(StatePtr(new PlayState()));
            return;
        }
    }

    focus->x = player->x + FlxG.width*0.5;
    focus->y = player->y + FlxG.height*0.18 + (player->onFloor ? 0 : 20);

    bool wasDead = player->dead;

    //only do this if we aren't paused...
    if (!paused)
        State::update();

    FlxU::collide(*player, *(seqA->blocks));
    FlxU::collide(*player, *(seqB->blocks));

    FlxU::collide(*(seqA->blocks), *shardsA);
    FlxU::collide(*(seqA->blocks), *shardsB);
    FlxU::collide(*(seqB->blocks), *shardsA);
    FlxU::collide(*(seqB->blocks), *shardsB);

    // if(FlxG.iPad)
    // {
    //     [FlxU alternateCollideWithParam1:seqA.blocks param2:shardsA];
    //     [FlxU alternateCollideWithParam1:seqA.blocks param2:shardsB];
    //     [FlxU alternateCollideWithParam1:seqB.blocks param2:shardsA];
    //     [FlxU alternateCollideWithParam1:seqB.blocks param2:shardsB];
    // }
    // else
    // {
    //     Sequence* sq = (seqA.x < seqB.x)?seqA:seqB;
    //     FlxEmitter* sh;
    //     if(shardsA.exists && shardsB.exists)
    //         sh = (shardsA.x > shardsB.x)?shardsA:shardsB;
    //     else if(shardsB.exists)
    //         sh = shardsB;
    //     else
    //         sh = shardsA;
    //     [FlxU alternateCollideWithParam1:sq.blocks param2:sh];
    // }

    dist->setDistance((int)(player->x/10));

    if (player->dead && !wasDead) {
    //     //hide pause button
    //     // pausedSprite.visible = false;
    //     // fadedSprite.visible  = false;
    //     // pauseButton.visible  = false;

        distance = player->x/10;

    //Write player's epitaph based on special events and/or the environmental context
    if(player->epitaph.compare("bomb") == 0)
        player->epitaph = "\nturning into a fine mist.";
    else if(player->epitaph.compare("hit") == 0)
    {
        if (distance < 105) {
            player->epitaph = "just barely\nstumbling out of the first hallway.";
        }
        else {
            //ran into the front of the sequence in question
            Sequence& s = (seqA->x < seqB->x) ? *seqA : *seqB;
            // int type = s.getType();
            int type = s.type;
            switch(type)
            {
                case 1: //hallway
                    player->epitaph = "\nmissing another window.";
                    break;
                case 2: //collapse
                    player->epitaph = "\nknocking a building down.";
                    break;
                case 4: //crane
                    player->epitaph = "somehow\nhitting the edge of a crane.";
                    break;
                case 5: //billboard
                    player->epitaph = "somehow\nhitting the edge of a billboard.";
                    break;
                case 6: //leg
                    player->epitaph = "colliding\nwith some enormous obstacle.";
                    break;
                default: //basic wallcase
                    player->epitaph = "hitting\na wall and tumbling to your death.";
                    break;
            }
        }
    }
    else {
        //fell off the screen
        int preType = seqA->getLastType(); //These are static, player-dependent values
        int type = seqA->getThisType();
        if(type > 0)
        {
            switch(type)
            {
                case 1: //hallway
                    player->epitaph = "completely\n missing the entire hallway.";
                    break;
                case 4: //crane
                    player->epitaph = "\nmissing a crane completely.";
                    break;
                case 5: //billboard
                    player->epitaph = "not\nquite reaching a billboard.";
                    break;
                case 6: //leg
                    player->epitaph = "landing\nwhere a building used to be.";
                    break;
                default: //basic fall case
                    player->epitaph = "\nfalling to your death.";
                    break;            
            }
        }
        else {
            switch(preType)
            {
                case 1: //hallway
                    player->epitaph = "\nfalling out of a hallway.";
                    break;
                case 2: //collapse
                    player->epitaph = "riding\na falling building all the way down.";
                    break;
                case 3: //bomb
                    player->epitaph = "dodging\n a bomb only to miss the next roof.";
                    break;
                case 4: //crane
                    player->epitaph = "\nfalling off a crane.";
                    break;
                case 5: //billboard
                    player->epitaph = "\nstumbling off the edge of a billboard.";
                    break;
                case 6: //leg
                    player->epitaph = "jumping\nclear over...something.";
                    break;
                default: //basic fall case
                    player->epitaph = "\nfalling to your death.";
                    break;            
            }
        }
    }
    //End epitaph decision tree


    //     //show exit button
    //     exitOn = [FlxSprite spriteWithGraphic:ImgExitOn];
    //     exitOff = [FlxSprite spriteWithGraphic:ImgExitOff];
    //     exitOn.x = FlxG.width-62;
    //     exitOn.y = 0;
    //     exitOn.scrollFactor = CGPointMake(0, 0);
    //     exitOff.x = exitOn.x;
    //     exitOff.y = exitOn.y;
    //     exitOff.scrollFactor = exitOn.scrollFactor;
    //     [self add:exitOn];
    //     [self add:exitOff];

    //     exitOff.visible = true;
    //     exitOn.visible = false;

        gameover = 0.01;
        int h = 88;
        SpritePtr bigGray = Sprite::create();
        bigGray->createGraphic(FlxG.width+2*QUAKE_OVERHANG, 64, FlxU::color(0xff35353d));
        bigGray->x = 0-QUAKE_OVERHANG;
        bigGray->y = h+35;
        bigGray->width = FlxG.width+2*QUAKE_OVERHANG;
        bigGray->height = 64;
        bigGray->scrollFactor = Vec2f(0, 0);
        add(bigGray);
        SpritePtr littleWhite = Sprite::create();
        littleWhite->createGraphic(FlxG.width+2*QUAKE_OVERHANG, 2, FlxU::color(0xffffffff));
        littleWhite->x = 0-QUAKE_OVERHANG;
        littleWhite->y = h+35+64;
        littleWhite->width = FlxG.width+2*QUAKE_OVERHANG;
        littleWhite->height = 2;
        littleWhite->scrollFactor = Vec2f(0, 0);
        add(littleWhite);
        SpritePtr s = Sprite::create();
        s->createGraphic(FlxG.width+2*QUAKE_OVERHANG, 30+QUAKE_OVERHANG, FlxU::color(0xff35353d));
        s->x = 0 - QUAKE_OVERHANG;
        s->y = FlxG.height-30;
        s->width = FlxG.width+2*QUAKE_OVERHANG;
        s->height = 30 + QUAKE_OVERHANG;
        s->scrollFactor = Vec2f(0, 0);
        add(s);
        SpritePtr gameOver = Sprite::create(0, 0, res.graphic(ImgGameOver));
        gameOver->x = (FlxG.width-390)/2.0;
        gameOver->y = h;
        gameOver->scrollFactor = Vec2f(0, 0);
        add(gameOver);

        const float margin = 30.0f;
        TextPtr epitaphText = Text::create(0+margin, h+50+5, FlxG.width-2*margin, epitaph);
        epitaphText->setAlignment(ALIGN_CENTER);
        epitaphText->setColor(FlxU::color(0xffffffff));
        epitaphText->scrollFactor = Vec2f(0, 0);
        epitaphText->setSize(18.0f);
        epitaphText->printf("You ran %dm before %s", distance, player->epitaph.c_str());
        add(epitaphText);

        TextPtr t = Text::create(0, FlxG.height-27+4, FlxG.width-3, string("Tap to retry your daring escape"));
        t->setSize(18.0f);
        t->setAlignment(ALIGN_RIGHT);
        t->setColor(FlxU::color(0xffffffff));
        t->scrollFactor = Vec2f(0,0);
        add(t);

        dist->visible = false;
    }

    if (firstTimeThroughUpdateLoop) {
        //don't set to false unless we aren't touching the screen
        // if (FlxG.touches.touching == false)
        //     firstTimeThroughUpdateLoop = false;
    }
}

