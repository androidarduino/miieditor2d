#ifndef LIP_H
#define LIP_H
#include "component.h"

class MiiLip: public MiiComponent
{
    public:
        MiiLip():MiiComponent("lip", true, false, true, true, 0.5, 0.73)
        {
        }
};

#endif
