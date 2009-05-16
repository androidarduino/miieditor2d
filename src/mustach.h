#ifndef MUSTACH_H
#define MUSTACH_H
#include "component.h"

class MiiMustach: public MiiComponent
{
    public:
        MiiMustach():MiiComponent("mustach", false, false, true, true, 0.5, 0.7)
        {
        }
};

#endif
