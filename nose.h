#ifndef NOSE_H
#define NOSE_H
#include "component.h"

class MiiNose: public MiiComponent
{
    public:
        MiiNose():MiiComponent("nose", true, false, true, false, 0.5, 0.6)
        {
        }
};

#endif
