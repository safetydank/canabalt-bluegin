#pragma once

#include "flx/emitter.h"

class SmokeEmitter : public flx::Emitter
{
public:
    SmokeEmitter(int smokeCount);
    int smokeCount;
};

typedef shared_ptr<SmokeEmitter> SmokeEmitterPtr;


