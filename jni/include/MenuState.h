#pragma once

#include "flx/state.h"
#include "flx/emitter.h"
#include "flx/button.h"

class MenuState : public flx::State
{
private:
    flx::TextPtr t1;
    flx::ButtonPtr b1;

public:
    virtual void create();
    virtual void update();
};

