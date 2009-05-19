#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H
#include "ui_mainwindow.h"
#include "ui_color.h"
#include "componentstore.h"
#include "displaywidget.h"
#include "toolboxitem.h"
#include <QSvgWidget>
#include <QSvgRenderer>
#include <QFileDialog>
#include <QColorDialog>

class ColorDialog:public QDialog
{
    Q_OBJECT
    public:
        ColorDialog(QString lightColor, QString darkColor, double transparency, QWidget* parent=0);
        void getValues(QString& cl, QString& cd, double & t);
    protected slots:
        void changeLightColor();
        void changeDarkColor();
    private:
        Ui_Dialog* dlg;

};

class EditorWindow:public QMainWindow
{
    Q_OBJECT
    public:
        EditorWindow(QWidget * parent = 0, Qt::WindowFlags flags = 0);
    public slots:
        void selectionChanged(ToolBoxItem* item);
		void moveDown(){displayWidget->modify('d',"25");}
		void moveUp(){displayWidget->modify('u',"25");}
		void moveLeft(){displayWidget->modify('l',"25");}
		void moveRight(){displayWidget->modify('r',"25");}
		void clockRotate(){displayWidget->modify('s',"5");}
		void counterClockRotate(){displayWidget->modify('s',"-5");}
		void reverse(){displayWidget->modify('e',"");}
		void zoomIn(){displayWidget->modify('i',"1.1");}
		void zoomOut(){displayWidget->modify('o',"1.1");}
		void HExpand(){displayWidget->modify('h',"1.1");}
		void VExpand(){displayWidget->modify('v',"1.1");}
		void setColor();
		void setTransparency();
                void save();
    private:
        Ui::MainWindow *ui;
        DisplayWidget *displayWidget;
        MiiComponentStore *store;
        void setupToolBox();
        void connectToolBox();
        void connectToolBar();
        QWidget* getToolBoxItems(QString category);
        QMap<QString, QList<ToolBoxItem*>*> toolItems;
    signals:
        void updateDisplay(ToolBoxItem *item);
};
#endif
