#ifndef QLAB1PIXMAPITEM_H
#define QLAB1PIXMAPITEM_H

#include <QGraphicsPixmapItem>

class QLab1PixmapItem : public QGraphicsPixmapItem
{
public:
	QLab1PixmapItem(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);	
	void SetId(int id);
	void setColor1(QColor color,QRect bounRect,double m_scale_temp,double m_scale_w_temp);
	int GetId();
private:
	virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
	int m_id;

};

#endif // QLAB1PIXMAPITEM_H
