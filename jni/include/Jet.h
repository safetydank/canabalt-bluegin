#pragma once

#include "flx/sprite.h"

class Jet : public flx::Sprite
{
public:
    float timer;
    float limit;

    Jet(bluegin::Graphic graphic);

    virtual void update();
};

typedef shared_ptr<Jet> JetPtr;