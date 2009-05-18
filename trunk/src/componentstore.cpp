#include "componentstore.h"
#include <QFileDialog>

MiiComponentStore::MiiComponentStore(QString source)
{
    doc=new QDomDocument();
    QFile file(source);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        source = QFileDialog::getOpenFileName(0, QObject::tr("Please find all.svg"), "./", QObject::tr("all.svg (all.svg)"));
        file.setFileName(source);
        if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qDebug()<<QObject::tr("Can't load all.svg which is compulsory for the application to run.");
            return;
        }
    }
    doc->setContent(&file);
    createComponents();
}

QString MiiComponentStore::getComponentSvg(QString item)
{
    return components[item];
}

QMap<QString, QString> MiiComponentStore::getPreview(QString prefix)
{
    QMap<QString, QString> ls;
    bool special=(prefix.startsWith("hair")||prefix.startsWith("beard")||prefix.startsWith("mustach"));
    QString ret;
    foreach(QString str, components.keys())
    {
        if(str.startsWith(prefix))
        {
            ret="";
            if(!special)
                ret=components[str];
            else
                ret=generateHairWithFace(str);
            ls[str]=ret;
        }
    }
    return ls;
}

QString MiiComponentStore::getColorDefinitions()
{
    return getDefs();
}

void MiiComponentStore::createComponents()
{
    const QDomNodeList& all=doc->elementsByTagName("g");
    ////qDebug()<<all.count();
    for(int i=0;i<all.count();i++)
    {
        const QDomNode& node=all.at(i);
        QString itemname=node.attributes().namedItem("inkscape:label").nodeValue();
        if(itemname=="")
            continue;
        QString s=QString("<g id=\"%1\">\n").arg(itemname);
        const QDomNodeList& children=node.childNodes();
        QTextStream stream(&s);
        for(int j=0; j<children.count(); j++)
        {
            children.at(j).save(stream, 4);
        }
        stream<<"</g>";
        if(itemname.startsWith("hair"))
        {
            QString lower="", upper="";
            splitHair(lower, upper, s);
            components[itemname]=upper;
            components[itemname.replace("hair", "under")]=lower;
        }
        else
            components[itemname]=s;
    }
}

void MiiComponentStore::splitHair(QString& lower, QString& upper, QString src)
{
    QString s, header, tail;
    int p3,p4,p5,p6;
    p3=src.indexOf("<path");//beginning of the lower layer
    p4=src.indexOf("<path", p3+1);//end of lowerlayer
    p5=p4;//beginning of upperlayer
    if(p4==-1)
        p5=0;
    p6=src.indexOf("</g>");//end of the upper layer
    s=src;
    if(p4==-1&&s.indexOf("singleLayer")==-1)
        lower="";
    else
        lower=s.remove(p5, p6-p5).replace("hair","under");

    s=src;
    if(src.indexOf("hair62")!=-1)
        qDebug()<<"hair 62 found"<<p3<<p4<<p5<<p6<<src;

    if(s.indexOf("singleLayer")!=-1)
        upper=s;
    else
        upper=s.remove(p3, p4-p3);
}

QString MiiComponentStore::getDefs()
{
    const QDomNodeList& defs=doc->elementsByTagName("defs");
    QString s;
    QTextStream stream(&s);
    for(int i=0;i<defs.count();i++)
    {
        defs.at(i).save(stream, 4);
    }
    return s;
}

QString MiiComponentStore::generateHairWithFace(QString key)
{
    return components[key.replace("hair", "under")]+components["face0"]+components[key];
}
