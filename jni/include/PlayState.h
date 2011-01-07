#pragma once

#include "flx/state.h"
#include "flx/emitter.h"
#include "flx/button.h"
#include "flx/sprite.h"

#include "Player.h"
#include "Sequence.h"
#include "HUD.h"
#include "BG.h"
// #include "Dove.h"
// #include "Shard.h"

class PlayState : public flx::State
{
private:
    flx::TextPtr t1;

public:
    PlayerPtr player;
    flx::SpritePtr focus;

    HUDPtr dist;
    BGPtr midground;
    BGPtr background;
    flx::SpritePtr backgroundRect;
    // ShardManager * shardManagerA;
    // ShardManager * shardManagerB;
    flx::EmitterPtr shardsA;
    flx::EmitterPtr shardsB;
    SequencePtr seqA;
    SequencePtr seqB;
    // vector<> smoke;
    float gameover;
    string epitaph;
    int distance;
    float flash;
    flx::SpritePtr exitOn;
    flx::SpritePtr exitOff;
    flx::SpritePtr pauseButton;
    flx::SpritePtr pausedSprite;
    flx::SpritePtr fadedSprite;
    bool paused;
    bool justPaused;
    bool reallyJustPaused;
    bool touching;
    bool lastTouching;
    bool touchBegan;
    bool touchEnded;
    bool pressedExit;
    bool pauseVisibility;
    // FlxPoint * tmpP;
    bool firstTimeThroughUpdateLoop;
    // DoveGroup * doveGroup;

    void doPause();
    void setPaused(bool gamePaused);
    virtual void create();
    virtual void update();
};


