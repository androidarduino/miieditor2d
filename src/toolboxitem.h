#ifndef TOOLBOXITEM_H
#define TOOLBOXITEM_H

#include <QSvgWidget>
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>

class ToolBoxItem:public QSvgWidget
{
    Q_OBJECT
public:
    ToolBoxItem(QString name, QString category);
    QString category();
    QString name();
protected:
    void mousePressEvent(QMouseEvent * event);
    void paintEvent(QPaintEvent* event);
private:
    bool m_selected;
    QString m_name;
    QString m_category;
public slots:
    void setSelected(bool state);
    void clearSelection();
signals:
    void itemSelected(ToolBoxItem* item);
};
#endif
