#ifndef HEAD_H
#define HEAD_H

#include "face.h"
#include "under.h"
#include "feature.h"
#include "hair.h"
#include "brow.h"
#include "eye.h"
#include "nose.h"
#include "lip.h"
#include "glasses.h"
#include "mustach.h"
#include "beard.h"
#include "componentstore.h"

class MiiHead
{
    public:
        MiiHead();
        QString toSvgGroup() ;
    private:
            MiiFace face;
            MiiFeature feature;
            MiiBrow brows;
            MiiHair hair;
            MiiUnder underhair;
            MiiEye eyes;
            MiiNose nose;
            MiiLip lip;
            MiiGlasses glasses;
            MiiMustach mustach;
            MiiBeard beard;
            MiiComponentStore* components;
};

#endif
