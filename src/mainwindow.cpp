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
    displayWidget->refresh();
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

void EditorWindow::setColor()
{
    QString category=displayWidget->currentCategory();
    QString lightColor, darkColor;
    double opacity;
    if(category=="hair")
    {
        lightColor=store->colors["color_hair"];
        darkColor=store->colors["color_under"];
        opacity=1;
    }
    if(category=="mole")
    {
        lightColor=store->colors["color_mole"];
        darkColor="white";
        opacity=1;
    }
    if(category=="lip")
    {
        lightColor=store->colors["color_lip_light"];
        darkColor=store->colors["color_lip_dark"];
        opacity=1;
    }
    if(category=="mustach"||category=="brow"||category=="beard")
    {
        lightColor=store->colors["color_brow"];
        darkColor="white";
        opacity=1;
    }
    if(category=="glasses")
    {
        lightColor=store->colors["color_glasses"];
        darkColor=store->colors["color_border_glasses"];
        opacity=store->colors["opacity_glasses"].toDouble();
    }
    if(category=="face")
    {
        lightColor=store->colors["color_face_light"];
        darkColor=store->colors["color_face_dark"];
        opacity=1;
    }
    if(category=="eye")
    {
        lightColor=store->colors["color_eye"];
        darkColor="white";
        opacity=1;
    }
    if(category=="feature")
    {
        lightColor=store->colors["color_grove"];
        darkColor="white";
        opacity=1;
    }
    ColorDialog dlg(lightColor,darkColor,opacity);
    dlg.exec();
    dlg.getValues(lightColor, darkColor, opacity);
    qDebug()<<lightColor<<darkColor<<opacity;
    if(category=="hair")
    {
        store->colors["color_hair"]=lightColor;
        store->colors["color_under"]=darkColor;
    }
    if(category=="mole")
    {
        store->colors["color_mole"]=lightColor;
    }
    if(category=="lip")
    {
        store->colors["color_lip_light"]=lightColor;
        store->colors["color_lip_dark"]=darkColor;
    }
    if(category=="mustach"||category=="brow"||category=="beard")
    {
        store->colors["color_brow"]=lightColor;
    }
    if(category=="glasses")
    {
        store->colors["color_glasses"]=lightColor;
        store->colors["color_border_glasses"]=darkColor;
        store->colors["opacity_glasses"]=QString().setNum(opacity);
    }
    if(category=="face")
    {
        store->colors["color_face_light"]=lightColor;
        store->colors["color_face_dark"]=darkColor;
    }
    if(category=="eye")
    {
        store->colors["color_eye"]=lightColor;
    }
    if(category=="feature")
    {
        store->colors["color_grove"]=lightColor;
    }
    displayWidget->refresh();
}

void EditorWindow::setTransparency()
{

}

ColorDialog::ColorDialog(QString lightColor, QString darkColor, double transparency, QWidget* parent):QDialog(parent)
{
    dlg=new Ui_Dialog();
    dlg->setupUi(this);
    dlg->opacity->setValue(100*transparency);
    QPalette palLight, palDark;
    palLight.setColor(QPalette::Normal, QPalette::Button, QColor(lightColor));
    dlg->lightColor->setPalette(palLight);
    palDark.setColor(QPalette::Normal, QPalette::Button, QColor(darkColor));
    dlg->darkColor->setPalette(palDark);
    connect(dlg->lightColor, SIGNAL(clicked()), this, SLOT(changeLightColor()));
    connect(dlg->darkColor, SIGNAL(clicked()), this, SLOT(changeDarkColor()));
}

void ColorDialog::changeLightColor()
{
    QColor c= QColorDialog::getColor(dlg->lightColor->palette().color(QPalette::Button));
    QPalette pal;
    pal.setColor(QPalette::Button, c);
    dlg->lightColor->setPalette(pal);
}

void ColorDialog::changeDarkColor()
{
    QColor c= QColorDialog::getColor(dlg->darkColor->palette().color(QPalette::Button));
    QPalette pal;
    pal.setColor(QPalette::Button, c);
    dlg->darkColor->setPalette(pal);
}

void ColorDialog::getValues(QString& cl, QString& cd, double& t)
{
    cl= dlg->lightColor->palette().color(QPalette::Button).name();
    cd= dlg->darkColor->palette().color(QPalette::Button).name();
    t=((double)dlg->opacity->value())/100;
}
