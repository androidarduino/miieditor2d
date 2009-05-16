#ifndef UNDER_H
#define UNDER_H
#include "component.h"

class MiiUnder: public MiiComponent
{
    public:
        MiiUnder():MiiComponent("under", false, false, true, true, 0.5, 0.5)
        {
        }
    private:
};

#endif
