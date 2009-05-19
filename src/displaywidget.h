#ifndef DISPLAYWIDGET_H
#define DISPLAYWIDGET_H

#include <QSvgWidget>
#include <QFileDialog>
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
    DisplayWidget(MiiComponentStore* database);
    QString currentCategory();

public slots:
    void refresh();
    void updateDisplay(ToolBoxItem* item);
    void modify(char actionType, QString value);
    void setCurrentItem(int index);
    void save(QString fn="");
    void loadFromFile();

protected:
    int heightForWidth(int w) const;

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
    QString currentFileName;
};
#endif
