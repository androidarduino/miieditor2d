#include "toolboxitem.h"

ToolBoxItem::ToolBoxItem(QString name, QString category)
{
    m_name=name;
    m_selected=false;
    m_category=category;
}

QString ToolBoxItem::category()
{
    return m_category;
}

QString ToolBoxItem::name()
{
    return m_name;
}

void ToolBoxItem::mousePressEvent(QMouseEvent * event)
{
    if(event->button()!=Qt::LeftButton)
        return;
    setSelected(true);
}

void ToolBoxItem::paintEvent(QPaintEvent* event)
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

void ToolBoxItem::setSelected(bool state)
{
    m_selected=state;
    if(state)
        emit itemSelected(this);
    update();
    //qDebug()<<"ToolBoxItem::setSelected(...) called";
}

void ToolBoxItem::clearSelection()
{
    m_selected=false;
    update();
}
