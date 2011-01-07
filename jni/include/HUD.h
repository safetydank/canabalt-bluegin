#pragma once

#include "flx/data/rect.h"
#include "flx/text.h"

// XXX a placeholder
class HUD : public flx::Text
{
public:
    int distance;

    HUD(flx::Rect frame);

    void setDistance(int newDistance);
    void render();
};

typedef shared_ptr<HUD> HUDPtr;

