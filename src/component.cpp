#include "component.h"

MiiComponent::MiiComponent(QString prefix, bool canRotate, bool symetric, bool canPan, bool canReverse, double posX, double posY)
{
    m_scaleX=1;
    m_scaleY=1;
    m_rotation=0;
    m_color="";
    m_zOrder=10;
    m_prefix=prefix;
    m_symetric=symetric;
    m_canPan=canPan;
    m_canRotate=canRotate;
    m_canReverse=canReverse;
    m_transparency=1;
    m_index=0;
    m_canvasWidth=744;
    m_canvasHeight=1052;
    m_x=m_canvasWidth*posX;
    m_y=m_canvasHeight*posY;
}

MiiComponent::~MiiComponent()
{

}

void MiiComponent::save(QDataStream& stream)
{
    stream<<m_x<<m_y<<m_scaleX<<m_scaleY<<m_rotation<<m_transparency<<m_color<<m_prefix<<m_zOrder<<m_symetric<<m_canRotate<<m_canReverse<<m_canPan<<m_index<<m_svgDefs<<m_groupName;
}

void MiiComponent::load(QDataStream& stream)
{
    stream>>m_x>>m_y>>m_scaleX>>m_scaleY>>m_rotation>>m_transparency>>m_color>>m_prefix>>m_zOrder>>m_symetric>>m_canRotate>>m_canReverse>>m_canPan>>m_index>>m_svgDefs>>m_groupName;
}

void MiiComponent::setItem(QString itemName)
{
    if(itemName.startsWith(m_prefix))
        setIndex(itemName.remove(m_prefix).toInt());
}

QString MiiComponent::name()
{
    QString s="%1%2";
    return s.arg(m_prefix).arg(m_index);
}

void MiiComponent::setSvgGroup(QString svgDoc)
{
    m_svgDefs=svgDoc;
}

void MiiComponent::setTransparency(double transparency)
{
    m_transparency=transparency;
}

void MiiComponent::setIndex(int index)
{
    m_index=index;
}

void MiiComponent::scaleX(double ratio)
{
    m_scaleX*=ratio;
}

void MiiComponent::scaleY(double ratio)
{
    m_scaleY*=ratio;
}

void MiiComponent::zoom(double ratio)
{
    scaleX(ratio);
    scaleY(ratio);
}

void MiiComponent::rotate(double angel)
{
    if(!m_canRotate)
        return;
    m_rotation+=angel;
    if(m_rotation>=360)
        m_rotation-=360;
    if(m_rotation<=-360)
        m_rotation+=360;
}

void MiiComponent::reverse()
{
    if(!m_canReverse)
        return;
    m_scaleX*=-1;
}

void MiiComponent::setColor(QString color)
{
    m_color=color;
}

void MiiComponent::pan(double deltaX, double deltaY)
{
    if(!m_canPan)
        return;
    m_x+=deltaX;
    m_y+=deltaY;
}

QString MiiComponent::toSvgGroup()// includeDefs)
{
    QString prefixString="<g id=\"%1\">";
    prefixString=prefixString.arg(m_prefix);
    QString t="<defs><use xlink:href=\"#%1%2\" transform=\"scale(%3,%4) rotate(%5) \" id=\"%1%2tmp\"/></defs><use xlink:href=\"#%1%2tmp\"  x=\"%6\" y=\"%7\" />";
    QString oneSide=t.arg(m_prefix).arg(m_index).arg(m_scaleX).arg(m_scaleY).arg(m_rotation).arg(m_x).arg(m_y);
    if(m_symetric)
    {
        QString st="<defs><use xlink:href=\"#%1%2\" id=\"%1%2mirrortmp\" transform=\"scale(-%3,%4) rotate(%5)\"/></defs><use xlink:href=\"#%1%2mirrortmp\"  x=\"%6\" y=\"%7\" />";
        QString otherSide=st.arg(m_prefix).arg(m_index).arg(m_scaleX).arg(m_scaleY).arg(m_rotation).arg(m_canvasWidth-m_x).arg(m_y);
        return prefixString+oneSide+otherSide+"</g>";
    }
    else
    {
        return prefixString+oneSide+"</g>";
    }
}

bool MiiComponent::canRotate()
{
    return m_canRotate;
}

bool MiiComponent::canReverse()
{
    return m_canReverse;
}

bool MiiComponent::canPan()
{
    return m_canPan;
}
