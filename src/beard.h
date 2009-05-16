#ifndef BEARD_H
#define BEARD_H
#include "component.h"

class MiiBeard: public MiiComponent
{
    public:
        MiiBeard():MiiComponent("beard", false, false, true, true, 0.5, 0.9)
        {
        }
};

#endif
