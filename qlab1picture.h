#ifndef QLAB1PICTURE_H
#define QLAB1PICTURE_H

#include <QGraphicsTextItem>



class QLab1Picture: public QGraphicsTextItem
{
public:
QLab1Picture(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
void SetId(int id);
void Set_m_Text(QString a_text);
void SetFlagOn();
void SetFlagOff();
int GetId();

private:
virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);

int m_id;
int m_flag;
QString m_text;
};

#endif // QLAB1PICTURE_H
