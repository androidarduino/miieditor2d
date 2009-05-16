#ifndef FACE_H
#define FACE_H
#include "component.h"

class MiiFace: public MiiComponent
{
    public:
        MiiFace():MiiComponent("face", false, false, true, true, 0.5, 0.5)
        {
        }

};

#endif
