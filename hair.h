#ifndef HAIR_H
#define HAIR_H
#include "component.h"

class MiiHair: public MiiComponent
{
    public:
        MiiHair():MiiComponent("hair", false, false, true, true, 0.5, 0.5)
        {
        }
    private:
};

#endif
