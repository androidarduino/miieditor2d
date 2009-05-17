#include "head.h"

MiiHead::MiiHead()
{
    components=new MiiComponentStore("all.svg");
}

QString MiiHead::toSvgGroup()
{
    QString t=components->getColorDefinitions();
    t+= "<defs>";
    t+=components->getComponentSvg(face.name());
    t+=components->getComponentSvg(feature.name());
    t+=components->getComponentSvg(underhair.name());
    t+=components->getComponentSvg(hair.name());
    t+=components->getComponentSvg(brows.name());
    t+=components->getComponentSvg(eyes.name());
    t+=components->getComponentSvg(nose.name());
    t+=components->getComponentSvg(lip.name());
    t+=components->getComponentSvg(glasses.name());
    t+=components->getComponentSvg(mustach.name());
    t+=components->getComponentSvg(beard.name());
    t+="</defs>";
    t+=underhair.toSvgGroup();
    //qDebug()<<underhair.toSvgGroup();
    t+=face.toSvgGroup();
    t+=feature.toSvgGroup();
    t+=brows.toSvgGroup();
    t+=eyes.toSvgGroup();
    t+=nose.toSvgGroup();
    t+=lip.toSvgGroup();
    t+=mustach.toSvgGroup();
    t+=beard.toSvgGroup();
    t+=hair.toSvgGroup();
    t+=glasses.toSvgGroup();
    return t;
}
