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
        MiiComponentStore(QString source)
        {
            doc=new QDomDocument();
            QFile file(source);
            file.open(QIODevice::ReadOnly | QIODevice::Text);
            doc->setContent(&file);
            createComponents();
        }
        QString getComponentSvg(QString item)
        {
            return components[item];
        }
        QMap<QString, QString> getPreview(QString prefix)
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
        QString getColorDefinitions()
        {
            return getDefs();
        }
    private:
        QDomDocument * doc;
        QMap<QString, QString> components;
        void createComponents()
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
        void splitHair(QString& lower, QString& upper, QString src)
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
        QString getDefs()
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
        QString generateHairWithFace(QString key)
        {
			return components[key.replace("hair", "under")]+components["face0"]+components[key];
        }
};

#endif
