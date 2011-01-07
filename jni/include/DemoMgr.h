#pragma once

#include "flx/object.h"

class Player;
class DemoMgr;
typedef shared_ptr<DemoMgr> DemoMgrPtr;

class DemoMgr : public flx::Object
{
public:
    Player* p;
    bool go;
    vector<flx::ObjectPtr> c;

    static DemoMgrPtr create(float X, Player* player, vector<flx::ObjectPtr>& children);
    DemoMgr(float x, Player* player, vector<flx::ObjectPtr>& children);
    void add(flx::ObjectPtr object);

    virtual void update();
};

