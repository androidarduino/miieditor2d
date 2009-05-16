#ifndef GLASSES_H
#define GLASSES_H
#include "component.h"

class MiiGlasses: public MiiComponent
{
    public:
        MiiGlasses():MiiComponent("glasses", false, false, true, true, 0.5, 0.5)
        {
        }
};

#endif
