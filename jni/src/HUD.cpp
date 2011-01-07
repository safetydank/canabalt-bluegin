#include "flx/text.h"

#include "HUD.h"

using namespace ci;
using namespace bluegin;
using namespace flx;

HUD::HUD(Rect frame)
    : Text(frame.x, frame.y, frame.width)
{
    height = frame.height;
    setSize(16.0f);
    setAlignment(ALIGN_RIGHT);
}

void HUD::render()
{
    this->printf("%dm", distance);
    Text::render();
}

void HUD::setDistance(int newDistance)
{
    distance = newDistance;
}
