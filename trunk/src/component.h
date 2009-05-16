#ifndef COMPONENT_H
#define COMPONENT_H

#include <QString>
#include <QDebug>

class MiiComponent
{
    public:
        double m_canvasWidth, m_canvasHeight;
        MiiComponent(QString prefix, bool canRotate, bool symetric, bool canPan, bool canReverse, double posX, double posY)
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

        virtual ~MiiComponent()
        {

        }

        void setItem(QString itemName)
        {
            if(itemName.startsWith(m_prefix))
                setIndex(itemName.remove(m_prefix).toInt());
        }

        QString name()
        {
            QString s="%1%2";
            return s.arg(m_prefix).arg(m_index);
        }

        virtual void setSvgGroup(QString svgDoc)
        {
            m_svgDefs=svgDoc;
        }

		virtual void setTransparency(double transparency)
		{
			m_transparency=transparency;
		}

        virtual void setIndex(int index)
        {
            m_index=index;
        }
        virtual void scaleX(double ratio)
        {
            m_scaleX*=ratio;
        }
        virtual void scaleY(double ratio)
        {
            m_scaleY*=ratio;
        }
        virtual void zoom(double ratio)
        {
            scaleX(ratio);
            scaleY(ratio);
        }
        virtual void rotate(double angel)
        {
            if(!m_canRotate)
                return;
            m_rotation+=angel;
            if(m_rotation>=360)
                m_rotation-=360;
            if(m_rotation<=-360)
                m_rotation+=360;
        }
        virtual void reverse()
        {
            if(!m_canReverse)
                return;
            m_x*=-1;
        }
        virtual void setColor(QString color)
        {
            m_color=color;
        }
        virtual void pan(double deltaX, double deltaY)
        {
            if(!m_canPan)
                return;
            m_x+=deltaX;
            m_y+=deltaY;
        }
        virtual QString toSvgGroup()// includeDefs)
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
        bool canRotate()
        {
            return m_canRotate;
        }
        bool canReverse()
        {
            return m_canReverse;
        }
        bool canPan()
        {
            return m_canPan;
        }
    private:
        double m_x,m_y, m_scaleX, m_scaleY;
        double m_rotation, m_transparency;
        QString m_color;
        QString m_prefix;
        int m_zOrder;
        bool m_symetric, m_canRotate, m_canReverse, m_canPan;
        int m_index;
        QString m_svgDefs;
        QString m_groupName;
};

#endif



