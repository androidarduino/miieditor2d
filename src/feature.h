#ifndef FACEFEATURE_H
#define FACEFEATURE_H
#include "component.h"

class MiiFeature: public MiiComponent
{
    public:
        MiiFeature():MiiComponent("feature", true, true, true, true, 0.66, 0.625)
        {
        }
};

#endif
