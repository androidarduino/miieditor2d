#ifndef EYE_H
#define EYE_H
#include "component.h"

class MiiEye: public MiiComponent
{
    public:
        MiiEye():MiiComponent("eye", true, true, true, false, 0.67, 0.5)
        {
        }
};

#endif
