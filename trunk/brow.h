#ifndef EYEBROW_H
#define EYEBROW_H
#include "component.h"

class MiiBrow: public MiiComponent
{
    public:
        MiiBrow():MiiComponent("brow", true, true, true, false, 0.67, 0.45)
        {
        }
};

#endif
