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
        ToolBoxItem(QString name, QString category)
        {
            m_name=name;
            m_selected=false;
            m_category=category;
        }
        QString category()
        {
            return m_category;
        }
        QString name()
        {
            return m_name;
        }
    protected:
        void mousePressEvent(QMouseEvent * event)
        {
            if(event->button()!=Qt::LeftButton)
                return;
            setSelected(true);
        }
        void paintEvent(QPaintEvent* event)
        {
            QSvgWidget::paintEvent(event);
            if(m_selected)
            {
                QPainter painter(this);
                const QPen& pen=painter.pen();
                painter.setPen(QPen(QBrush(QColor(Qt::red)), 5));
                painter.drawRoundRect(2,2,width()-5,height()-5,15,15);
                painter.setPen(pen);
            }
        }
    private:
        bool m_selected;
        QString m_name;
        QString m_category;
    public slots:
        void setSelected(bool state)
        {
            m_selected=state;
            if(state)
                emit itemSelected(this);
            update();
            //qDebug()<<"ToolBoxItem::setSelected(...) called";
        }
        void clearSelection()
        {
            m_selected=false;
            update();
        }
    signals:
        void itemSelected(ToolBoxItem* item);
};
#endif
