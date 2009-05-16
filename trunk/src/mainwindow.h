#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H
#include "ui_mainwindow.h"
#include "componentstore.h"
#include "displaywidget.h"
#include "toolboxitem.h"
#include <QSvgWidget>
#include <QSvgRenderer>
#include <QFileDialog>

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
		void unClockRotate(){displayWidget->modify('s',"-5");}
		void reverse(){displayWidget->modify('e',"");}
		void zoomIn(){displayWidget->modify('i',"1.1");}
		void zoomOut(){displayWidget->modify('o',"1.1");}
		void HExpand(){displayWidget->modify('h',"1.1");}
		void VExpand(){displayWidget->modify('v',"1.1");}
		void setColor(){displayWidget->modify('c',"#000000");}
		void setTransparency(){displayWidget->modify('t',"1.0");}
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
