#ifndef COMPONENT_H
#define COMPONENT_H

#include <QString>
#include <QDataStream>
#include <QDebug>

class MiiComponent
{
    public:
        QString m_prefix;
        double m_canvasWidth, m_canvasHeight;
        MiiComponent(QString prefix, bool canRotate, bool symetric, bool canPan, bool canReverse, double posX, double posY);
        virtual ~MiiComponent();

        void setItem(QString itemName);
        QString name();
        virtual void setSvgGroup(QString svgDoc);

		virtual void setTransparency(double transparency);

        virtual void setIndex(int index);
        virtual void scaleX(double ratio);
        virtual void scaleY(double ratio);
        virtual void zoom(double ratio);
        virtual void rotate(double angel);
        virtual void reverse();
        virtual void setColor(QString color);
        virtual void pan(double deltaX, double deltaY);
        virtual QString toSvgGroup();// includeDefs)
        bool canRotate();
        bool canReverse();
        bool canPan();
        void save(QDataStream& stream);
        void load(QDataStream& stream);
    private:
        double m_x,m_y, m_scaleX, m_scaleY;
        double m_rotation, m_transparency;
        QString m_color;
        int m_zOrder;
        bool m_symetric, m_canRotate, m_canReverse, m_canPan;
        int m_index;
        QString m_svgDefs;
        QString m_groupName;
};

#endif



