#include "qlab1picture.h"
#include <QPainter>
#include "ean13.h"

QLab1Picture::QLab1Picture(QGraphicsItem *parent, QGraphicsScene *scene)
    : QGraphicsTextItem(parent)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);

    m_flag=0;
}
void QLab1Picture::SetId(int id)
{
    m_id=id;
}


void QLab1Picture::Set_m_Text(QString a_text)
{
    m_text=a_text;
}


int QLab1Picture::GetId()
{
    return m_id;
}

void QLab1Picture::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    //   	if((m_id==0)&&(m_text!=""))
    //   	{
    //   	//QGraphicsTextItem::paint(painter, option, widget);
    //   	EAN13 code(m_text);
    //
    //  		code.draw(QRectF(0,0,(boundingRect().width()),boundingRect().width()*10.93/37.29),*painter,isSelected());
    // 	}
    //   	else
    //   	{
    // 		if((m_text!="")&&(m_flag==1))
    // 		{
    // 			painter->drawRect(0, 0, boundingRect().width(),boundingRect().height());
    // 		}
    // 		QGraphicsTextItem::paint(painter, option, widget);
    //   	}
    if((m_text!="")&&(m_flag==1))
    {
        painter->drawRect(0, 0, boundingRect().width(),boundingRect().height());
    }

    QGraphicsTextItem::paint(painter, option, widget);

}

void QLab1Picture::SetFlagOn()
{
    m_flag=1;
}
void QLab1Picture::SetFlagOff()
{
    m_flag=0;
}
