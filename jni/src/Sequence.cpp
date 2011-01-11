#include "flx/flxG.h"

#include "Sequence.h"

#include "Billboard.h"
#include "Bomb.h"
#include "Crane.h"
#include "DemoMgr.h"
#include "GibEmitter.h"
#include "Hall.h"
#include "Leg.h"
#include "Obstacle.h"
#include "Window.h"

using namespace ci;
using namespace bluegin;
using namespace flx;

extern FlxGlobal FlxG;

static const char* ImgAntenna1Left    = "antenna-left";
static const char* ImgAntenna1Right   = "antenna-right";
static const char* ImgAntenna2Trimmed = "antenna2-trimmed";
static const char* ImgAntenna3Trimmed = "antenna3-trimmed";
static const char* ImgAntenna4Trimmed = "antenna4-trimmed";
static const char* ImgAntenna5Trimmed = "antenna5-trimmed";
static const char* ImgAntenna6Trimmed = "antenna6-trimmed";

static const char* ImgDishesTrimmed = "dishes-trimmed";

static const char* ImgAC          = "ac-trimmed";
static const char* ImgSkyLight    = "skylight";
static const char* ImgReservoir   = "reservoir-trimmed";
static const char* ImgPipe1Left   = "pipe1-left";
static const char* ImgPipe1Right  = "pipe1-right";
static const char* ImgPipe2Left   = "pipe2-left";
static const char* ImgPipe2Middle = "pipe2-middle";
static const char* ImgPipe2Right  = "pipe2-right";

static const char* ImgEscape = "escape-trimmed-filled";

static const char* ImgAccess = "access";
static const char* ImgFence  = "fence-trimmed";

#define DOVES

static const float tileSize = 16;
static const float decSize = 20;

static int _nextIndex; 
static int _nextType;
static int _curIndex;

static int _lastType;
static int _thisType;

static SequencePtr sequence1 = SequencePtr();
static SequencePtr sequence2 = SequencePtr();

static int sequenceIndex = 0;

static GibEmitterPtr collapseEmitter = GibEmitterPtr();
static GibEmitterPtr bombAndLegEmitter = GibEmitterPtr();
static GibEmitterPtr aftermathEmitter = GibEmitterPtr();

static CranePtr crane;
static HallPtr hall;
static BillboardPtr billboard;

void Sequence::setPlayer(Player* plr)
{
    player = plr;
}

Player* Sequence::getPlayer()
{
    return player;
}

void Sequence::setShardsA(EmitterPtr shardsa)
{
    shardsA = shardsa;
}

EmitterPtr Sequence::getShardsA()
{
    return shardsA;
}

void Sequence::setShardsB(flx::EmitterPtr shardsb)
{
    shardsB = shardsb;
}

flx::EmitterPtr Sequence::getShardsB()
{
    return shardsB;
}

//  static initialization of both sequences
void Sequence::initialize()
{
    sequence1 = SequencePtr(new Sequence());
    sequence2 = SequencePtr(new Sequence());

    GibEmitterPtr ge;

    // int gibCount = 40;
    int gibCount = 40 * 3;
    if (FlxG.iPad) {
        gibCount = 40*3;
    } else {
        if (FlxG.iPhone3G || FlxG.iPhone1G || FlxG.iPodTouch1G)
            gibCount = 20;
        else
            gibCount = 40;
    }

    ge = GibEmitterPtr(new GibEmitter(gibCount));
    ge->delay = 0.02 / 3;
    // if (FlxG.iPad) {
    //     ge->delay = 0.02/3;
    // } else {
    //     if (FlxG.iPhone3G || FlxG.iPhone1G || FlxG.iPodTouch1G)
    //         ge->delay = 0.02*2;
    //     else
    //         ge->delay = 0.02;
    // }
    ge->minParticleSpeed = Vec2f(-200, -120);
    ge->maxParticleSpeed = Vec2f(200, 0);
    ge->minParticleSpeed = Vec2f(-200, -120);
    ge->maxParticleSpeed = Vec2f(200, 0);
    ge->minRotation = -720;
    ge->maxRotation = 720;
    ge->gravity = 400;
    ge->particleDrag = Vec2f(0, 0);
    collapseEmitter = ge;

    //bombAndLegEmitter
    if (FlxG.iPhone3G || FlxG.iPhone1G || FlxG.iPodTouch1G) {
        if (FlxG.iPhone3G)
            gibCount = 40/2;
        else
            gibCount = 40/4;
    } else
        gibCount = 40;

    ge = GibEmitterPtr(new GibEmitter(gibCount));
    if (FlxG.iPhone3G || FlxG.iPhone1G || FlxG.iPodTouch1G) {
        if (FlxG.iPhone3G)
            ge->delay = -3*2;
        else
            ge->delay = -3*4;
    } else
        ge->delay = -3;

    ge->minParticleSpeed = Vec2f(-240,
            -320);
    ge->maxParticleSpeed = Vec2f(240,
            0);
    ge->minRotation = 0;
    ge->maxRotation = 0;
    //ge->minRotation = -720;
    //ge->maxRotation = 720;
    ge->gravity = 800;
    ge->particleDrag = Vec2f(0, 0);
    bombAndLegEmitter = ge;

    //aftermath emitter
    if (FlxG.iPad)
        gibCount = 50*3;
    else
        gibCount = 50;
    ge = GibEmitterPtr(new GibEmitter(gibCount));
    ge->delay = -10.0;
    ge->minParticleSpeed = Vec2f(0, -200);
    ge->maxParticleSpeed = Vec2f(0, 100);
    ge->minRotation = -720;
    ge->maxRotation = 720;
    ge->gravity = 150;
    ge->particleDrag = Vec2f(0, 0);

    aftermathEmitter = ge;

    //create the crane now, reuse later
    float maxWidth = 1344.0;
    if (FlxG.iPad)
        maxWidth = 1440.0;
    crane = CranePtr(new Crane(maxWidth));
    hall = HallPtr(new Hall(maxWidth));
    billboard = BillboardPtr(new Billboard(maxWidth));
}

Sequence::Sequence() 
    : Object(), player(NULL), shardsA(EmitterPtr()), shardsB(EmitterPtr())
{
    _thisType = 0;
    _lastType = 0;

    layer = Group::create();
    foregroundLayer = Group::create();
    renderLayer = Group::create();
    backgroundRenderLayer = Group::create();
    layerLeg = Group::create();

    blocks = Group::create();

    //create the building now, reuse later
    float maxWidth = 1344.0;
    if (FlxG.iPad)
        maxWidth = 1440.0;
    // building = [[Building alloc] initWithMaxWidth:maxWidth];
    building = BuildingPtr(new Building(maxWidth));

    fence = TileblockPtr(new Tileblock(0, 0, 0, 0));
    // escape = [[RepeatBlock repeatBlockWithX:0 y:0 width:0 height:0] retain];
    escape = TileblockPtr(new Tileblock(0, 0, 0, 0));

    roof = false;

    int deviceScale;
    if(FlxG.iPad)
        deviceScale = 8;
    //else if(FlxG.retinaDisplay)
    //    deviceScale = 6;
    else
        deviceScale = 4;
    doveGroup = DoveGroup::create((maxWidth/120)*(1+deviceScale));
}

SequencePtr Sequence::get(Player* player, EmitterPtr shardsA, EmitterPtr shardsB)
{
    SequencePtr ret = (sequenceIndex == 0) ? sequence1 : sequence2;
    sequenceIndex = ((sequenceIndex+1) % 2);
    ret->player = player;
    ret->shardsA = shardsA;
    ret->shardsB = shardsB;
    ret->x = 0;
    ret->y = 0;
    ret->width = 0;
    ret->height = 0;
    ret->roof = false;
    return ret;
}

void Sequence::setNextIndex(int ni)
{
    _nextIndex = ni;
}

void Sequence::setNextType(int nt)
{
    _nextType = nt;
}

void Sequence::setCurIndex(int ci)
{
    _curIndex = ci;
}

int Sequence::getNextIndex()
{
    return _nextIndex;
}

int Sequence::getNextType()
{
    return _nextType;
}

int Sequence::getCurIndex()
{
    return _curIndex;
}

void Sequence::setLastType(int lt)
{
    _lastType = lt;
}

void Sequence::setThisType(int tt)
{
    _thisType = tt;
}

int Sequence::getLastType()
{
    return _lastType;
}

int Sequence::getThisType()
{
    return _thisType;
}


enum {
  ROOF,
  HALLWAY,
  COLLAPSE,
  BOMB,
  CRANE,
  BILLBOARD,
  LEG
};

void Sequence::reset()
{
    ResourceManager& res = *(FlxG.resources);
    assert(player);

    clear();
    int i;
    int n;
    passed = false;

    //  4 window types, limit index to [0,3]
    int wallType = math<int>::clamp(FlxU::random()*4, 0, 3);//[walls count];
    int windowType = math<int>::clamp(FlxU::random()*4, 0, 3);//[windows count];

    type = ROOF;
    int types[] = {HALLWAY, COLLAPSE, BOMB, CRANE, BILLBOARD, LEG};
    if (_curIndex == _nextIndex) {
        type = types[_nextType];
        _nextIndex += 3 + FlxU::random() * 5;
        _nextType = FlxU::random() * 6;
    }

    if (_curIndex == 0) {
        x = -4*tileSize;
        y = 5*tileSize;
        width = 60*tileSize;
        height = 480-5*tileSize;
        type = HALLWAY;
    } else if (_curIndex == 1) {
        x = seq->x + seq->width + 10*tileSize;
        y = 15*tileSize;
        width = 42*tileSize;
        height = 480-15*tileSize;
    }

    int hallHeight = 0;
    if (type == HALLWAY) {
        if (player->velocity.x > 640)
            hallHeight = 7;
        else if (player->velocity.x > 480)
            hallHeight = 6;
        else if (player->velocity.x > 320)
            hallHeight = 5;
        else if(_curIndex > 0)
            hallHeight = 4;
        else
            hallHeight = 3;
    }

    TileblockPtr mainBlock;
    float screenTiles = FlxU::ceil(FlxG.width/tileSize)+2;
    float maxGap = ((player->velocity.x*0.75)/decSize)*0.75;
    float minGap = maxGap * 0.4;
    if(minGap < 4)
        minGap = 4;
    float fg = FlxU::random();
    float gap = (float)((int)(minGap + fg*(maxGap-minGap)));
    float minW = screenTiles-gap;
    if ((minW < 15) && (player->velocity.x < player->maxVelocity.x*0.8))
        minW = 15;
    else if (minW < 6)
        minW = 6;
    float maxW = minW*2;
    float maxJ = seq->y/tileSize-2-hallHeight;
    float mpj = 6*player->jumpLimit/0.35;
    if (maxJ > mpj) maxJ = mpj;
    if (maxJ > 0) maxJ = FlxU::ceil(maxJ*(1-fg));
    float maxDrop = seq->height/tileSize-4;
    if (maxDrop > 10)
        maxDrop = 10;
    if (_curIndex > 1) {
        x = seq->x + seq->width + gap*tileSize;
        float drop = (float)((int)(FlxU::random()*maxDrop-maxJ));
        if (type == HALLWAY && gap > 10) drop = 0;
        if (drop == 0)
            drop--;
        y = seq->y + drop*tileSize;
        height = 480-y;
        width = FlxU::floor(minW+FlxU::random()*maxW)*tileSize;
    }

    // 1 - If collapsing is likely going to kill the player, just don't do it
    // 2 - Only bomb roofs that are pretty wide
    // 3 - Don't put cranes right on the very bottom, that's dumb

    if ((type == COLLAPSE && width/height > player->velocity.x*0.015) ||
        (type == BOMB && width < player->velocity.x * 1.5) ||
        (type == CRANE && (height < tileSize*2 || width < tileSize*24)) ||
        (type == LEG && width > tileSize*28) ) {
        type = ROOF;
        _nextIndex = _curIndex+1;
    }

    //Make sure crane and billboard and leg are on the right offset
    if (type == LEG) {
        // the main collision block for this sequence
        int legWidth = 120;
        mainBlock = TileblockPtr(new Tileblock(x + (width - legWidth)/2, seq->y + 3,
                   legWidth+20, 480));
        blocks->add(mainBlock);
        layer->add(mainBlock);
    }
    else if ((type == CRANE) || (type == BILLBOARD)) {
        width = (FlxU::ceil(width/(tileSize*2)))*tileSize*2;

        //Tweak the size of the billboard
        if(type == BILLBOARD)
        {
            hallHeight = (3+(int)(FlxU::random()*5))*tileSize*2;
            if(width > hallHeight*2)
            {
                int diff = width - hallHeight*2;
                if(diff > 4*tileSize)
                    x += 4*tileSize;
                else
                    x += (width - hallHeight*2);
                width = hallHeight*2;
            }
        }

        // the main collision block for this sequence
        mainBlock = TileblockPtr(new Tileblock(x, y, width+10, 2*tileSize));
        blocks->add(mainBlock);
        layer->add(mainBlock);
    }
    else {
        // the main collision block for this sequence
        mainBlock = TileblockPtr(new Tileblock(x, y, width+10, height+2*tileSize));
        blocks->add(mainBlock);
        layer->add(mainBlock);
    }

    //put decorations on roof
    BombPtr b;
    LegPtr l;
    //FlxEmitter * f;
    //   float ah = 160;
    if (type == ROOF || type == COLLAPSE || type == BOMB || type == LEG) {
        //     if (y > seq.y) {
        //       FlxSprite * a = [FlxSprite spriteWithGraphic:[antennas randomObject]];
        //       a.x = x+tileSize;
        //       a.y = y-ah;
        //     }

        float rt = FlxU::random();
        int rw;
        int rh;
        if (rt < 0.2) {
            decorate(x, y, width);
        }
        else if (rt < 0.6) {
            //BLOCK ROOF
            int indent = 2 + FlxU::random()*((width/decSize)/4);
            rw = width/decSize - indent*2;
            rh = 1 + FlxU::random()*4;
            if (rh > 2) {
                SpritePtr bs = Sprite::create(x+indent*decSize, y-rh*decSize);
                bs->createGraphic(rw*decSize, (rh-1)*decSize, FlxU::color(0x4d4d59));
                // bs.enableBlend = NO;
                backgroundRenderLayer->add(bs);
                bs = Sprite::create(x+(indent+1)*decSize, y-decSize);
                bs->createGraphic((rw-2)*decSize, decSize, FlxU::color(0x4d4d59));
                // bs.enableBlend = NO;
                backgroundRenderLayer->add(bs);
            } else {
                SpritePtr bs = Sprite::create(x+indent*decSize, y-rh*decSize);
                bs->createGraphic(rw*decSize, rh*decSize, FlxU::color(0x4d4d59));
                // bs.enableBlend = NO;
                backgroundRenderLayer->add(bs);
            }
            decorate(x+indent*decSize, y-rh*decSize, rw*decSize);
        } else {
            // XXX TODO
            // //SLOPE ROOF
            // rh = 1 + FlxU::random()*5;
            // if (self.width < 12*tileSize) rh = 1;
            // Trapezoid * t;
            // t = [[Trapezoid alloc] initWithX:self.x+tileSize y:self.y-rh*tileSize graphic:nil];
            // [t createGraphicWithWidth:self.width-2*tileSize height:tileSize*rh color:0x4d4d59];
            // t.enableBlend = NO;
            // [backgroundRenderLayer add:t];
            // [t release];
            // [self decorateSeqX:self.x+rh*tileSize seqY:self.y-rh*tileSize seqWidth:self.width-2*(rh+1)*tileSize];
        }

        //Fire escapes
        if (FlxU::random() < 0.5) {
            escape->x = x+width;
            escape->y = y+tileSize;
            escape->width = tileSize;
            escape->height = height;
            escape->loadGraphic(res.graphic(ImgEscape));
            // escape.enableBlend = NO;
            renderLayer->add(escape);
        }

        if (type == BOMB) {
            // NSMutableArray * entry = [NSMutableArray array];
            // for (i = 0; i < 6; ++i) {
            //     Gib * g = [Gib gib];
            //     [entry addObject:g];
            // }
            b = Bomb::get(Vec2f(x+width/2, y), player, this);
            layer->add(b);
            // for (FlxSprite * fs in entry)
            //     [layer add:fs];
        }
        else if (type == LEG) {
            l = Leg::get(Vec2f(x+width/2, seq->y), player, this);
            layerLeg->add(l);
        }
    }

    //add graphics for the wall and roof
    if (type == CRANE) {
        crane->create(x, y, width, height, player);
        layer->add(crane->trigger);
        renderLayer->add(crane);
    } 
    else if (type == BILLBOARD) {
        billboard->create(x, y, width, height, tileSize, hallHeight);
        renderLayer->add(billboard);
    } 
    else {
        building->create(x, y, width, height, tileSize, type, wallType, windowType);
        renderLayer->add(building);
    }

    if (type != HALLWAY) {
        //Doves!
        if (FlxU::random() < 0.35) {
            //max width is 60*tileSize (60*16 = 960)
            //max n is (960/120)*(8) => 64
            int deviceScale = 8;
            if(FlxG.iPad)
                deviceScale = 8;
            //else if(FlxG.retinaDisplay)
            //    deviceScale = 6;
            else
                deviceScale = 4;
            n = (width/120)*(1+FlxU::random()*deviceScale);
#ifdef DOVES        
            int doveHeight = y - 10;
            if (type == BILLBOARD)
                doveHeight -= hallHeight;
            doveGroup->setVisibleDoves(n);
            for (i = 0; i < doveGroup->visibleDoves; ++i) {
                ObjectPtr dovep = doveGroup->members.at(i);
                Dove& dove = static_cast<Dove&>(*dovep);
                dove.x = x + (FlxU::random()*(width-10));
                dove.y = doveHeight;
                dove.acceleration = Vec2f(0,0);
                dove.velocity = Vec2f(0,0);
                dove.player = player;
                dove.trigger = x;
                dove.visible = true;
                dove.exists = true;
                dove.active = true;
                dove.play("idle");
                foregroundLayer->add(dovep);
            }
            foregroundLayer->add(doveGroup);
#endif
        }
    }

    if (type == BOMB) {
        bombAndLegEmitter->x = x+width/2 - tileSize*2;
        bombAndLegEmitter->y = y;
        bombAndLegEmitter->width = tileSize*4;
        bombAndLegEmitter->height = 0;
        bombAndLegEmitter->minRotation = 0;
        bombAndLegEmitter->maxRotation = 0;
        bombAndLegEmitter->kill();
        b->add(bombAndLegEmitter);
        foregroundLayer->add(bombAndLegEmitter);
    }
    else if(type == LEG) {
        bombAndLegEmitter->x = x+50;
        bombAndLegEmitter->y = y;
        bombAndLegEmitter->width = width-100;
        bombAndLegEmitter->height = height;
        bombAndLegEmitter->minRotation = -720;
        bombAndLegEmitter->maxRotation = 720;

        bombAndLegEmitter->kill();
        l->add(bombAndLegEmitter);
        layerLeg->add(bombAndLegEmitter);
    }
    else if (type == COLLAPSE) {
        DemoMgrPtr dm = DemoMgr::create(x, player, layer->members);
        //need to add in renderLayer members also?
        for (vector<ObjectPtr>::iterator it = renderLayer->members.begin();
                it != renderLayer->members.end(); ++it) {
            dm->add(*it);
        }
        //are doves added to this?
        for (vector<ObjectPtr>::iterator it = backgroundRenderLayer->members.begin();
                it != backgroundRenderLayer->members.end(); ++it) {
            dm->add(*it);
        }

        collapseEmitter->x = x;
        collapseEmitter->y = y;
        collapseEmitter->width = width;
        if (FlxG.iPhone3G || FlxG.iPhone1G || FlxG.iPodTouch1G)
            collapseEmitter->height = 40;
        else
            collapseEmitter->height = height;
        //reset the emitter
        collapseEmitter->kill();

        foregroundLayer->add(collapseEmitter);
        dm->add(collapseEmitter);

        layer->add(dm);
    } 
    else if (type == ROOF && _curIndex > 1) {
        //normal rooftops should sometimes get some obstacles if you're not going too fast
        for (i = 0; i < 3; ++i)
            if (FlxU::random() < 0.15)
                foregroundLayer->add(Obstacle::create(Vec2f(x+width/8+FlxU::random()*(width/2), y), player, true));
    }

    //Hallways get a lot of special treatment - special obstacles, doors, windows, etc
    if (type == HALLWAY) {
        hallHeight *= tileSize;
        blocks->add(TileblockPtr(new Tileblock(x, -128, width, y-hallHeight+128)));
        hall->create(x, y, width, height, tileSize, hallHeight, wallType, windowType);
        renderLayer->add(hall);

        foregroundLayer->add(Window::create(Vec2f(x+width-WindowW-1, y),
                    hallHeight, player, shardsA));
        foregroundLayer->add(Window::create(Vec2f(x+1, y),
                    hallHeight, player, shardsB));

        if (_curIndex == 0) {
            //put a couple of obstacles in the launch hallway
        	foregroundLayer->add(Obstacle::create(Vec2f(32*tileSize,y), player));
            foregroundLayer->add(Obstacle::create(Vec2f(48*tileSize,y), player));
        } else {
            //throw in a few obstacles here and there
            for (i = 0; i < 3; ++i)
                if (FlxU::random() < 0.65)
                    foregroundLayer->add(Obstacle::create(Vec2f(x+width/8+FlxU::random()*(width/2),y), player));
        }
    }

    //Estimate out basic sequence changes due to the collapsing building's height change
    if (type == COLLAPSE) {
        int cd = (width/tileSize)*0.5;
        if (cd > height/tileSize-1)
            cd = height/tileSize-1;
        height -= cd*tileSize;
        y += cd*tileSize;
    }

    _curIndex++;
}

void Sequence::initSequence(Sequence* sequence)
{
    seq = sequence;
    reset();
}

void Sequence::update()
{
    Vec2d p = getScreenXY(p);
    if (p.x + width < 0) reset();
    if(!passed && (player->x > x))
    {
        passed = true;
        setLastType(getThisType());
        setThisType(type);
    }

    Object::update();

    foregroundLayer->update();
    layer->update();
    renderLayer->update();
    backgroundRenderLayer->update();
    layerLeg->update();
}

void Sequence::render()
{
    Object::render();
    backgroundRenderLayer->render();
    layer->render();
    renderLayer->render();
    foregroundLayer->render();
    layerLeg->render();
}

void Sequence::clear()
{
    layer->removeAll();
    foregroundLayer->removeAll();
    renderLayer->removeAll();
    backgroundRenderLayer->removeAll();
    layerLeg->removeAll();
    blocks->removeAll();
}

void Sequence::aftermath()
{
    FlxG.flash.start(FlxU::color(0xffffffff), 4);
    clear();

    aftermathEmitter->x = x + width/2;
    aftermathEmitter->y = -FlxG.height;
    aftermathEmitter->width = FlxG.width;
    aftermathEmitter->height = FlxG.height;
    //reset it
    aftermathEmitter->kill();

    layer->add(aftermathEmitter);
    aftermathEmitter->start();
}

void Sequence::stomp()
{
    //  XXX called by Leg
}

void Sequence::decorate(float seqX, float seqY, float seqWidth)
{
    ResourceManager& res = *(FlxG.resources);
    int i;
    int n;
    int s;

    s = 40;
    n = seqWidth/s;
    for (i = 0; i < n; ++i)
        if (FlxU::random() < 0.3)
            backgroundRenderLayer->add(Sprite::create(seqX+decSize+s*i, seqY-decSize, res.graphic(ImgAC)));

    int ah = 160;

    if (FlxU::random() < 0.5) {
        //pipes roof
        s = 120;
        n = (seqWidth-100) / s; //subtract 100 so that it doesn't go off the edge
        for (i = 0; i < n; ++i)
            if (FlxU::random() < 0.35) {
                //add 3 parts of the pipe...
                backgroundRenderLayer->add(Sprite::create(seqX+decSize+s+i, seqY-decSize, res.graphic(ImgPipe1Left)));
                backgroundRenderLayer->add(Sprite::create(seqX+decSize+s+i+100-12, seqY-decSize, res.graphic(ImgPipe1Right)));
                SpritePtr pipe = Sprite::create(seqX+decSize+s+i+13, seqY-decSize);
                pipe->createGraphic(100-12-13, 8, FlxU::color(0x4d4d59));
                backgroundRenderLayer->add(pipe);
                //[backgroundRenderLayer add:[FlxSprite spriteWithX:seqX+decSize+s*i y:seqY-decSize graphic:ImgPipe1]];
            }
        s = 80;
        n = (seqWidth-40) / s; // subtract 40 so that it doesn't hang over the edge
        for (i = 0; i < n; ++i)
            if (FlxU::random() < 0.35) {
                backgroundRenderLayer->add(Sprite::create(seqX+decSize+s*i+2, seqY-decSize*2+5, res.graphic(ImgPipe2Left)));
                backgroundRenderLayer->add(Sprite::create(seqX+decSize+s*i+2+15, seqY-decSize*2+4, res.graphic(ImgPipe2Middle)));
                backgroundRenderLayer->add(Sprite::create(seqX+decSize+s*i+2+15+10, seqY-decSize*2+5, res.graphic(ImgPipe2Right)));
            }

        if (FlxU::random() < 0.5) {
            s = 40;
            n = (seqWidth-32)/s;
            for (i = 0; i < n; ++i)
                if (FlxU::random() < 0.3) {
                    switch ((int)(FlxU::random()*7)) {
                        case 0:
                            backgroundRenderLayer->add(Sprite::create(seqX+decSize+s*i, seqY-ah, res.graphic(ImgAntenna1Left)));
                            backgroundRenderLayer->add(Sprite::create(seqX+decSize+s*i+18, seqY-ah+160-19, res.graphic(ImgAntenna1Right)));
                            break;
                        case 1:
                            backgroundRenderLayer->add(Sprite::create(seqX+decSize+s*i+3, seqY-ah, res.graphic(ImgAntenna2Trimmed)));
                            break;
                        case 2:
                            backgroundRenderLayer->add(Sprite::create(seqX+decSize+s*i, seqY-ah, res.graphic(ImgAntenna3Trimmed)));
                            break;
                        case 3:
                            backgroundRenderLayer->add(Sprite::create(seqX+decSize+s*i, seqY-ah+40, res.graphic(ImgAntenna4Trimmed)));
                            break;
                        case 4:
                            backgroundRenderLayer->add(Sprite::create(seqX+decSize+s*i+(40-16)/2, seqY-ah+40, res.graphic(ImgAntenna5Trimmed)));
                            break;
                        case 5:
                            backgroundRenderLayer->add(Sprite::create(seqX+decSize+s*i+6, seqY-ah+4, res.graphic(ImgAntenna6Trimmed)));
                            break;
                        case 6:
                            backgroundRenderLayer->add(Sprite::create(seqX+decSize+s*i+1, seqY-ah, res.graphic(ImgDishesTrimmed)));
                            break;
                    }				  
                }
        }
    } else {
        //Skylights, roof access + reservoirs
        s = 140;
        n = seqWidth / s;
        for(i = 0; i < n; ++i)
            if(FlxU::random() < 0.5)
                backgroundRenderLayer->add(Sprite::create(seqX+decSize+s*i, seqY-decSize+1, res.graphic(ImgSkyLight)));
        s = 200;
        n = seqWidth / s;
        for(i = 0; i < n; ++i)
            if(FlxU::random() < 0.25)
                backgroundRenderLayer->add(Sprite::create(seqX+decSize+s*i, seqY-30, res.graphic(ImgAccess)));
        s = 200;
        n = seqWidth / s;
        for(i = 0; i < n; ++i)
            if(FlxU::random() < 0.5)
                backgroundRenderLayer->add(Sprite::create(seqX+decSize+s*i+2, seqY-decSize*6, res.graphic(ImgReservoir)));
    }

    if(FlxU::random() < 0.4) {
        //Add chainlink fences
        n = seqWidth/(tileSize*2)-2;
        fence->x = seqX+tileSize*2;
        fence->y = seqY-tileSize*2+(32-19);
        fence->width = n*tileSize*2;
        fence->height = tileSize*2;
        fence->loadGraphic(res.graphic(ImgFence));
        backgroundRenderLayer->add(fence);
    }
}
