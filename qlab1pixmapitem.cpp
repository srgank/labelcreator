#include "qlab1pixmapitem.h"
#include <QPainter>

QLab1PixmapItem::QLab1PixmapItem(QGraphicsItem *parent,QGraphicsScene *scene)
: QGraphicsPixmapItem(parent)
{
	setFlag(QGraphicsItem::ItemIsSelectable);
	setFlag(QGraphicsItem::ItemIsMovable);
}
void QLab1PixmapItem::SetId(int id)
{
	m_id=id;
}

int QLab1PixmapItem::GetId()
{
	return m_id;
}
void QLab1PixmapItem::paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget)
{
	QGraphicsPixmapItem::paint(painter, option, widget);

	if(isSelected())
	{
		double distance=boundingRect().width()*0.01>2?boundingRect().width()*0.01:2;	
		painter->drawRect(boundingRect().width()-distance/2, boundingRect().height()-distance/2, distance,distance);
	}

}
void QLab1PixmapItem::setColor1(QColor color,QRect bounRect,double m_scale_temp,double m_scale_w_temp)
{
	QPixmap pixmap(bounRect.width(),bounRect.height());
	QPainter painter(&pixmap);
	painter.fillRect(0, 0, bounRect.width(),bounRect.height(), color);
	setPixmap(pixmap);
}
