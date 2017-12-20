#include "qmygraphicsrectitem.h"

QMyGraphicsRectItem::QMyGraphicsRectItem(QGraphicsItem * parent, QGraphicsScene * scene)
	: QGraphicsRectItem(parent,scene)
{
	setFlag(QGraphicsRectItem::ItemIsSelectable);
	setFlag(QGraphicsRectItem::ItemIsMovable);
}

QMyGraphicsRectItem::~QMyGraphicsRectItem()
{

}
