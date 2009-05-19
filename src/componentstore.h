#ifndef MIISVGPARSER_H
#define MIISVGPARSER_H

#include <QDomDocument>
#include <QStringList>
#include <QDebug>
#include <QFile>
#include <QTextStream>

class MiiComponentStore
{
    public:
        MiiComponentStore(QString source);
        QString getComponentSvg(QString item);
        QMap<QString, QString> getPreview(QString prefix);
        QString getColorDefinitions();
        QMap<QString, QString> colors;
    private:
        QDomDocument * doc;
        QMap<QString, QString> components;
        void createComponents();
        void splitHair(QString& lower, QString& upper, QString src);
        QString getDefs();
        QString generateHairWithFace(QString key);
};

#endif
