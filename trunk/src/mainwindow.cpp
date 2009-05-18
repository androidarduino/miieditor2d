#include "mainwindow.h"

EditorWindow::EditorWindow(QWidget* parent, Qt::WindowFlags flags):QMainWindow(parent, flags)
{
    ui=new Ui::MainWindow();
    ui->setupUi(this);
    store=new MiiComponentStore("all.svg");
    displayWidget=new DisplayWidget(store);
    ui->scrollArea->setWidget(displayWidget);
    setupToolBox();
    connectToolBox();
    connectToolBar();
}

void EditorWindow::setupToolBox()
{
    ui->scrollArea_2->setWidget(getToolBoxItems("face"));
    ui->scrollArea_3->setWidget(getToolBoxItems("hair"));
    ui->scrollArea_4->setWidget(getToolBoxItems("eye"));
    ui->scrollArea_5->setWidget(getToolBoxItems("nose"));
    ui->scrollArea_6->setWidget(getToolBoxItems("lip"));
    ui->scrollArea_7->setWidget(getToolBoxItems("feature"));
    ui->scrollArea_8->setWidget(getToolBoxItems("glasses"));
    ui->scrollArea_9->setWidget(getToolBoxItems("brow"));
}

QWidget* EditorWindow::getToolBoxItems(QString category)
{
    QWidget* boxWidget=new QWidget();
    QGridLayout *layout=new QGridLayout();
    const QMap<QString, QString>& items=store->getPreview(category);
    QString defs="<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?><svg>";
    defs=defs+store->getColorDefinitions();
    double maxW=0, maxH=0;
    QList<ToolBoxItem*>* svgList=new QList<ToolBoxItem*>();
    for(int i=0;i<items.count();i++)
    {
        QString content=((defs+items.values().at(i)+"</svg>"));
        ToolBoxItem *svg=new ToolBoxItem(items.keys().at(i), category);
        connect(svg, SIGNAL(itemSelected(ToolBoxItem*)), this, SLOT(selectionChanged(ToolBoxItem*)));
        *svgList<<svg;
		//qDebug()<<content;
        svg->load(content.toUtf8());
        QRectF rect=svg->renderer()->boundsOnElement(items.keys().at(i));
        if(maxW<rect.width())
            maxW=rect.width();
        if(maxH<rect.height())
            maxH=rect.height();
        int x=i%5;
        int y=i/5;
        layout->addWidget(svg, x, y);
    }
    foreach(ToolBoxItem* svg, *svgList)
    {
        QRectF rect(-maxW/2, -maxH/2, maxW, maxH);
        svg->renderer()->setViewBox(rect);
        svg->setFixedSize(90, int(maxH/maxW*90));
    }
    boxWidget->setLayout(layout);
    toolItems[category]=svgList;
    svgList->at(0)->setSelected(true);
    emit updateDisplay(svgList->at(0));
    return boxWidget;
}

void EditorWindow::selectionChanged(ToolBoxItem* item)
{
    QList<ToolBoxItem*>* list=toolItems[item->category()];
    ToolBoxItem* i=item;
    foreach(i, *list)
        if(i!=item)
            i->setSelected(false);
    emit updateDisplay(item);
}

void EditorWindow::connectToolBox()
{
    connect(this, SIGNAL(updateDisplay(ToolBoxItem*)), displayWidget, SLOT(updateDisplay(ToolBoxItem*)));
}

void EditorWindow::connectToolBar()
{
	connect(ui->toolBox, SIGNAL(currentChanged(int)), displayWidget, SLOT(setCurrentItem(int)));
	connect(ui->actionMove_down, SIGNAL(triggered()), this, SLOT(moveDown()));
	connect(ui->actionMove_up, SIGNAL(triggered()), this, SLOT(moveUp()));
	connect(ui->actionMove_Left, SIGNAL(triggered()), this, SLOT(moveLeft()));
	connect(ui->actionMove_Right, SIGNAL(triggered()), this, SLOT(moveRight()));
	connect(ui->actionChange_Color, SIGNAL(triggered()), this, SLOT(setColor()));
	connect(ui->actionRotate_Clockwise, SIGNAL(triggered()), this, SLOT(clockRotate()));
	connect(ui->actionRotate_Counter_Clockwise, SIGNAL(triggered()), this, SLOT(counterClockRotate()));
	connect(ui->actionReverse, SIGNAL(triggered()), this, SLOT(reverse()));
	connect(ui->actionZoom_in, SIGNAL(triggered()), this, SLOT(zoomIn()));
	connect(ui->actionZoom_out, SIGNAL(triggered()), this, SLOT(zoomOut()));
	connect(ui->actionChange_Transparency, SIGNAL(triggered()), this, SLOT(setTransparency()));
	connect(ui->actionHorizontally_Stetch, SIGNAL(triggered()), this, SLOT(HExpand()));
	connect(ui->actionVertically_Stretch, SIGNAL(triggered()), this, SLOT(VExpand()));
	connect(ui->action_Save, SIGNAL(triggered()), this, SLOT(save()));
	connect(ui->action_Open, SIGNAL(triggered()), displayWidget, SLOT(loadFromFile()));
}

void EditorWindow::save()
{
    QString sf=QFileDialog::getSaveFileName(this, tr("Save File"),"untitled.mee",tr("MEE (*.mee);; SVG (*.svg);;PNG (*.png);;JPG (*.jpg)"));
    if(sf.endsWith(".mee"))
    {
        displayWidget->save(sf);
        return;
    }
    if(sf.endsWith(".svg"))
    {
        QFile file(sf);
        if (file.open(QFile::WriteOnly | QFile::Truncate))
        {
            QTextStream out(&file);
            out << displayWidget->currentSVG;
            file.close();
        }
        qDebug()<<displayWidget->currentSVG;
        return;
    }
    if(!(sf.endsWith(".png")||sf.endsWith(".jpg")))
    {
        qDebug()<<tr("invalid file type");
        return;
    }
    QImage img(744,1052,QImage::Format_RGB32);
    QPainter p(&img);
    p.setViewport(0, 0, img.width(), img.height());
    displayWidget->renderer()->render(&p);
    img.save(sf);
    qDebug()<<tr("Image file saved to: ")<<sf;
}
