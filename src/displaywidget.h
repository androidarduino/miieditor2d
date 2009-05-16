#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QSvgWidget>
#include "componentstore.h"
#include "toolboxitem.h"

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
#include <QSvgRenderer>

class DisplayWidget:public QSvgWidget
{
    Q_OBJECT
    public:
        QString currentSVG;
        DisplayWidget(MiiComponentStore* database)
        {
            m_store=database;
            renderer()->setViewBox(QRectF(0,0,744,1052));
            setFixedSize(372, 526);
            currentItem=&face;
        }
        public slots:
            void refresh()
            {

                QString t;
                t+= "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?><svg width=\"744\" height=\"1052\">";
                t+=m_store->getColorDefinitions();
                t+="<defs>";
                t+=m_store->getComponentSvg(face.name());
                t+=m_store->getComponentSvg(feature.name());
                t+=m_store->getComponentSvg(underhair.name());
                t+=m_store->getComponentSvg(hair.name());
                t+=m_store->getComponentSvg(brows.name());
                t+=m_store->getComponentSvg(eyes.name());
                t+=m_store->getComponentSvg(nose.name());
                t+=m_store->getComponentSvg(lip.name());
                t+=m_store->getComponentSvg(glasses.name());
                t+=m_store->getComponentSvg(mustach.name());
                t+=m_store->getComponentSvg(beard.name());
                t+="</defs>";
                t+=underhair.toSvgGroup();
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
                t+="</svg>";
                load(t.toUtf8());
                //qDebug()<<t;
                currentSVG=t.toUtf8();

                update();
            }

        void updateDisplay(ToolBoxItem* item)
        {
            components[item->category()]=m_store->getComponentSvg(item->name());
            qDebug()<<"updating display...";
            face.setItem(item->name());
            feature.setItem(item->name());
            brows.setItem(item->name());
            hair.setItem(item->name());
            eyes.setItem(item->name());
            nose.setItem(item->name());
            lip.setItem(item->name());
            glasses.setItem(item->name());
            mustach.setItem(item->name());
            beard.setItem(item->name());
            if(item->name().startsWith("hair"))//underhair is so painful...
                underhair.setIndex(item->name().remove("hair").toInt());
            qDebug()<<item->name();
            refresh();
        }
        void modify(char actionType, QString value)
        {
            MiiComponent *i=currentItem;
            switch(actionType)
            {
                case 'c':
                    i->setColor(value);
                    break;
                case 't':
                    i->setTransparency(value.toDouble());
                case 'u':
                    i->pan(0, -1*value.toDouble());
                    break;
                case 'd':
                    i->pan(0, value.toDouble());
                    break;
                case 'l':
                    i->pan(-1*value.toDouble(),0);
                    break;
                case 'r':
                    i->pan(value.toDouble(), 0);
                    break;
                case 'e':
                    i->reverse();
                    break;
                case 'i':
                    i->zoom(value.toDouble());
                    break;
                case 'o':
                    i->zoom(1/value.toDouble());
                    break;
                case 'h':
                    i->scaleX(value.toDouble());
                    break;
                case 'v':
                    i->scaleY(value.toDouble());
                    break;
                case 's':
                    i->rotate(value.toDouble());
                    break;
            }
            if(i==&hair)
            {
                i=&underhair;
                modify(actionType, value);
                i=&hair;
            }
            refresh();
        }

        void setCurrentItem(int index)
        {
            switch(index)
            {
                case 0:
                    currentItem=&face;
                    break;
                case 1:
                    currentItem=&hair;
                    break;
                case 2:
                    currentItem=&eyes;
                    break;
                case 3:
                    currentItem=&brows;
                    break;
                case 4:
                    currentItem=&nose;
                    break;
                case 5:
                    currentItem=&lip;
                    break;
                case 6:
                    currentItem=&feature;
                    break;
                case 7:
                    currentItem=&glasses;
                    break;

            }
        }

    protected:
        int heightForWidth(int w) const
        {
            return int(((double)w)/744*1052);
        }

    private:
        MiiComponentStore* m_store;
        QMap<QString, QString> components;
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
        MiiComponent *currentItem;
};
#endif
