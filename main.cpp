#include "head.h"
#include "componentstore.h"
#include "mainwindow.h"
#include <QApplication>
#include <QtGui>
#include <QSvgWidget>
#include <QSvgRenderer>
#include <QtDebug>

int main(int argc, char** argv)
{
	QApplication app(argc, argv);
//        if(QString(argv[1])=="win")
        {
                EditorWindow win;
                win.show();
                return app.exec();
        }
/* //for testing purpose only
   QWidget widget;
    MiiComponentStore store("all.svg");
    const QMap<QString, QString>& eyes=store.getPreview(argv[1]);
    QGridLayout layout;
    QString defs="<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?><svg>";
    defs=defs+store.getColorDefinitions();
    ////qDebug()<<defs;
    double maxW=0, maxH=0;
    QList<QSvgWidget*> svgList;
    for(int i=0;i<eyes.count();i++)
    {
        QSvgWidget *svg=new QSvgWidget();
        svgList<<svg;
        QString content=((defs+eyes.values().at(i)+"</svg>"));
        svg->load(content.toUtf8());
        QRectF rect=svg->renderer()->boundsOnElement(eyes.keys().at(i));
        if(maxW<rect.width())
            maxW=rect.width();
        if(maxH<rect.height())
            maxH=rect.height();
        int x=i%5;
        int y=i/5;
        layout.addWidget(svg, x, y);
    }
    foreach(QSvgWidget* svg, svgList)
    {
        QRectF rect(-maxW/2, -maxH/2, maxW, maxH);
        svg->renderer()->setViewBox(rect);
        svg->setFixedSize(90, int(maxH/maxW*90));
    }
    widget.setLayout(&layout);
	widget.show();
    }
    else
    {
        MiiHead head;
        QSvgWidget* widget=new QSvgWidget();
        widget->load(("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?><svg>"+ head.toSvgGroup()+"</svg>").toUtf8());
        widget->renderer()->setViewBox(QRectF(0,0,744,1052));
        widget->setFixedSize(185, 263);
        widget->show();
    }
    */
	return app.exec();
}
