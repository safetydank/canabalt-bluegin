#pragma once

#include "flx/emitter.h"

class GibEmitter : public flx::Emitter
{
public:
    GibEmitter(int gibCount);
    int gibCount;
};

typedef shared_ptr<GibEmitter> GibEmitterPtr;

