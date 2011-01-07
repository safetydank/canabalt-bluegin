#include "CraneTrigger.h"
#include "Player.h"

using namespace ci; 
using namespace bluegin; 
using namespace flx;

CraneTriggerPtr CraneTrigger::create(Rect frame, Player* player)
{
    return CraneTriggerPtr(new CraneTrigger(frame, player));
}

CraneTrigger::CraneTrigger(Rect frame, Player* player)
    : Object(frame.x, frame.y, frame.width, frame.height), player(player)
{ }

void CraneTrigger::update()
{
    if (overlaps(*player)) {
        player->craneFeet = true;
    }
}

