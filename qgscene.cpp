#include "qgscene.h"
#include "qlab1picture.h"
#include "plabel.h"
#include <QBuffer>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>






QGScene::QGScene(QObject *parent)
    : QGraphicsScene(parent),
      stat_resize(false)
{
    mdbprint_elementPos.clear();
    mdbprint_elementImagePos.clear();
    m_stat_update=false;
    stat_selected=false;
}

QGScene::~QGScene()
{
}


void QGScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    QGraphicsScene::mousePressEvent(event);
    if(!selectedItems().isEmpty())
    {
        if(qgraphicsitem_cast<QLab1PixmapItem*>(selectedItems().at(0)))
        {
            QRectF rect=((QLab1PixmapItem*)selectedItems().at(0))->sceneBoundingRect();
            int distance=rect.width()*0.01>2?rect.width()*0.01:2;

            QRectF tmouseRect(event->scenePos().rx()-distance,event->scenePos().ry()-distance,2*distance,2*distance);
            QRectF tgraphRect(rect.x()+rect.width()-distance,rect.y()+rect.height()-distance,2*distance,2*distance);
            if (tgraphRect.intersects(tmouseRect))
            {
                stat_resize=true;
                m_Aresize.setX(rect.x());
                m_Aresize.setY(rect.y());
                ((QLab1PixmapItem*)selectedItems().at(0))->setFlag(QGraphicsItem::ItemIsMovable,false);
            }
            else
            {
                stat_resize=false;
            }
        }
    }
    if(selectedItems().isEmpty())
    {
        stat_selected=true;
        m_A= event->scenePos();
    }
    else
    {
        stat_selected=false;
        emit mChangeFont();
    }
}


void QGScene::setRC(int acol,int arow)
{
    e_col=acol;
    e_row=arow;
}


void QGScene::InitilizeItems()
{
    double w=(double)707/(double)e_col;
    double h=(double)1000/(double)e_row;

    QList<QGraphicsItem *> itemList=items();

    double x,y;
    int id;
    for(int xc=0;xc<itemList.size();xc++)
    {
        if(qgraphicsitem_cast<QLab1Picture*>(itemList.at(xc)))
        {
            x=((QLab1Picture*)itemList.at(xc))->pos().rx();
            y=((QLab1Picture*)itemList.at(xc))->pos().ry();
            id=((QLab1Picture*)itemList.at(xc))->GetId();

            QRectF r=((QLab1Picture*)itemList.at(xc))->boundingRect();
            double hdown=(double)r.height();
            double wleft=(double)r.width();
            for(idbprint_elementPos=mdbprint_elementPos.begin();idbprint_elementPos<mdbprint_elementPos.end();idbprint_elementPos++)
            {
                if((*idbprint_elementPos)->id==id)
                {
                    (*idbprint_elementPos)->m_x=(w/2+x)/w;
                    (*idbprint_elementPos)->m_y=(h/2+y+hdown/2)/h;
                    (*idbprint_elementPos)->m_width=wleft/w;
                    (*idbprint_elementPos)->m_height=hdown/h;
                }
            }
        }
        else if(qgraphicsitem_cast<QLab1PixmapItem*>(itemList.at(xc)))
        {
            x=((QLab1PixmapItem*)itemList.at(xc))->pos().rx();
            y=((QLab1PixmapItem*)itemList.at(xc))->pos().ry();
            id=((QLab1PixmapItem*)itemList.at(xc))->GetId();

            QRectF r=((QLab1PixmapItem*)itemList.at(xc))->boundingRect();
            double hdown=(double)r.height();


            for(idbprint_elementImagePos=mdbprint_elementImagePos.begin();idbprint_elementImagePos<mdbprint_elementImagePos.end();idbprint_elementImagePos++)
            {
                if((*idbprint_elementImagePos)->id==id)
                {
                    double scale=(*idbprint_elementImagePos)->m_scale;
                    double scale_w=(*idbprint_elementImagePos)->m_scale_w;

                    hdown=hdown*scale;
                    (*idbprint_elementImagePos)->m_x=(w/2+x)/w;
                    (*idbprint_elementImagePos)->m_y=(h/2+y)/h;
                    hdown=hdown/scale;
                }
            }

        }

    }
}
void QGScene::mouseMoveEvent( QGraphicsSceneMouseEvent * mouseEvent )  
{
    double w=(double)707/(double)e_col;
    double h=(double)1000/(double)e_row;

    if(stat_selected)
    {
        m_B= mouseEvent->scenePos();
        update();
    }
    else
    {
        m_B=m_A;
    }
    if(!selectedItems().isEmpty())
    {
        if(qgraphicsitem_cast<QLab1PixmapItem*>(selectedItems().at(0)))
        {

            QRectF rect=((QLab1PixmapItem*)selectedItems().at(0))->sceneBoundingRect();
            int distance=rect.width()*0.01>2?rect.width()*0.01:2;
            QRectF tmouseRect(mouseEvent->scenePos().rx()-distance,mouseEvent->scenePos().ry()-distance,2*distance,2*distance);
            QRectF tgraphRect(rect.x()+rect.width()-distance,rect.y()+rect.height()-distance,2*distance,2*distance);
            if (tgraphRect.intersects(tmouseRect)||stat_resize)
            {
                ((QLab1PixmapItem*)selectedItems().at(0))->setCursor(Qt::SizeFDiagCursor);
                if((m_Aresize.x()+2<mouseEvent->scenePos().x())&&(m_Aresize.y()+2<mouseEvent->scenePos().y()))
                {
                    m_Bresize.setX(mouseEvent->scenePos().x());
                    m_Bresize.setY(mouseEvent->scenePos().y());
                }
            }
            else
            {
                ((QLab1PixmapItem*)selectedItems().at(0))->setCursor(Qt::SizeAllCursor);
            }
        }
    }
    update();
    QGraphicsScene::mouseMoveEvent(mouseEvent);
}

void QGScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_B= event->scenePos();

    QPainterPath path;
    if(stat_selected)
    {
        path.addRect(m_A.x(),m_A.y(),m_B.x()-m_A.x(),m_B.y()-m_A.y());
        clearSelection();
        setSelectionArea(path);
    }
    stat_selected=false;

    m_A=m_B;

    double w=(double)707/(double)e_col;
    double h=(double)1000/(double)e_row;

    QList<QGraphicsItem *> itemList=items();
    double x,y;
    int id;
    foreach (QGraphicsItem *item, itemList)
    {
        if(qgraphicsitem_cast<QLab1Picture*>(item))
        {

            x=((QLab1Picture*)item)->pos().rx();
            y=((QLab1Picture*)item)->pos().ry();
            id=((QLab1Picture*)item)->GetId();

            QRectF r=((QLab1Picture*)item)->boundingRect();
            double hdown=(double)r.height();
            //item->rotate(90);


            for(idbprint_elementPos=mdbprint_elementPos.begin();idbprint_elementPos<mdbprint_elementPos.end();idbprint_elementPos++)
            {
                if((*idbprint_elementPos)->id==id)
                {
                    (*idbprint_elementPos)->m_x=(w/2+x)/w;
                    (*idbprint_elementPos)->m_y=(h/2+y+hdown/2)/h;
                }
            }
        }
        else if(qgraphicsitem_cast<QLab1PixmapItem*>(item))
        {
            ((QLab1PixmapItem*)item)->setCursor(Qt::ArrowCursor);
            x=((QLab1PixmapItem*)item)->pos().rx();
            y=((QLab1PixmapItem*)item)->pos().ry();
            id=((QLab1PixmapItem*)item)->GetId();

            QRectF r=((QLab1PixmapItem*)item)->boundingRect();
            double hdown=(double)r.height();
            //item->rotate(90);


            for(idbprint_elementImagePos=mdbprint_elementImagePos.begin();idbprint_elementImagePos<mdbprint_elementImagePos.end();idbprint_elementImagePos++)
            {
                double scale=(*idbprint_elementImagePos)->m_scale;
                double scale_w=(*idbprint_elementImagePos)->m_scale_w;
                if((*idbprint_elementImagePos)->id==id)
                {
                    (*idbprint_elementImagePos)->m_x=(w/2+x)/w;
                    (*idbprint_elementImagePos)->m_y=(h/2+y)/h;
                }
            }
        }
    }
    m_stat_update=true;

    if(!selectedItems().isEmpty())
    {
        if(qgraphicsitem_cast<QLab1PixmapItem*>(selectedItems().at(0)))
        {

            QRectF rect=((QLab1PixmapItem*)selectedItems().at(0))->sceneBoundingRect();
            int distance=rect.width()*0.01>2?rect.width()*0.01:2;
            QRectF tmouseRect(event->scenePos().rx()-distance,event->scenePos().ry()-distance,2*distance,2*distance);
            QRectF tgraphRect(rect.x()+rect.width()-distance,rect.y()+rect.height()-distance,2*distance,2*distance);
            if (!tgraphRect.intersects(tmouseRect)||stat_resize)
            {
                //((QLab1PixmapItem*)selectedItems().at(0))->setCursor(Qt::SizeFDiagCursor);

                if(stat_resize)
                {
                    double x1=m_Bresize.x()-m_Aresize.x();
                    double y1=m_Bresize.y()-m_Aresize.y();

                    QPixmap tempPixmap,tempPixmap_1;
                    tempPixmap.loadFromData(GetInfoImageData(((QLab1PixmapItem*)selectedItems().at(0))->GetId()),"PNG");
                    tempPixmap=tempPixmap.scaled(x1,y1,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
                    ((QLab1PixmapItem*)selectedItems().at(0))->setPixmap(tempPixmap);
                    ((QLab1PixmapItem*)selectedItems().at(0))->setCursor(Qt::SizeFDiagCursor);

                    int aid=((QLab1PixmapItem*)selectedItems().at(0))->GetId();
                    QByteArray bytes;
                    QBuffer buffer(&bytes);
                    for(idbprint_elementImagePos=mdbprint_elementImagePos.begin();idbprint_elementImagePos<mdbprint_elementImagePos.end();idbprint_elementImagePos++)
                    {
                        if((*idbprint_elementImagePos)->id==aid)
                        {
                            bytes=(*idbprint_elementImagePos)->m_data;
                            tempPixmap_1.loadFromData(bytes); // writes pixmap into bytes in PNG format
                            double scale=(double)tempPixmap_1.size().height()/(double)y1;
                            double scale_w=(double)tempPixmap_1.size().width()/(double)x1;
                            (*idbprint_elementImagePos)->m_scale=scale;
                            (*idbprint_elementImagePos)->m_scale_w=scale_w;
                            double temp_y=((QLab1PixmapItem*)selectedItems().at(0))->y();
                            double hdown=((QLab1PixmapItem*)selectedItems().at(0))->boundingRect().height();
                            (*idbprint_elementImagePos)->m_y=(temp_y+h/2)/h;
                        }
                    }

                }
            }
            else
            {
                //((QLab1PixmapItem*)selectedItems().at(0))->setCursor(Qt::SizeAllCursor);
            }
        }
    }
    if(stat_resize)
    {
        m_Bresize=m_Aresize;
        stat_resize=false;
        ((QLab1PixmapItem*)selectedItems().at(0))->setFlag(QGraphicsItem::ItemIsMovable,true);

    }
    QGraphicsScene::mouseReleaseEvent(event);
    m_stat_update=true;
    update();
}

void QGScene::GetNewPosition(Typemdbprint_elementPos *x)
{
    x=&mdbprint_elementPos;
}

void QGScene::deleteSelectedItem()
{
    QList <QGraphicsItem*> itemList=selectedItems();
    if(!itemList.isEmpty())
    {
        if(qgraphicsitem_cast<QLab1PixmapItem*>(itemList.at(0)))
        {
            itemList.at(0);
            int id=((QLab1PixmapItem*)itemList.at(0))->GetId();


            for(idbprint_elementImagePos=mdbprint_elementImagePos.begin();idbprint_elementImagePos<mdbprint_elementImagePos.end();idbprint_elementImagePos++)
            {
                if((*idbprint_elementImagePos)->id==id)
                {
                    mdbprint_elementImagePos.erase(idbprint_elementImagePos);
                }
            }
            delete itemList.at(0);
        }
        // 			if(qgraphicsitem_cast<QMyGraphicsRectItem*>(itemList.at(0)))
        // 			{
        // 				itemList.at(0);
        // 				int id=((QMyGraphicsRectItem*)itemList.at(0))->GetId();
        //
        //
        // 				for(idbprint_elementImagePos=mdbprint_elementImagePos.begin();idbprint_elementImagePos<mdbprint_elementImagePos.end();idbprint_elementImagePos++)
        // 				{
        // 					if((*idbprint_elementImagePos)->id==id)
        // 					{
        // 						mdbprint_elementImagePos.erase(idbprint_elementImagePos);
        // 					}
        // 				}
        // 				delete itemList.at(0);
        // 			}

    }
}
void QGScene::addInfo(int aid,int ax,int ay,QColor m_color,QFont m_graph_Font,double m_rotate)
{
    newprint_elementPos=new dbprint_elementPos;
    newprint_elementPos->id=aid;
    newprint_elementPos->m_x=ax;
    newprint_elementPos->m_y=ay;
    newprint_elementPos->m_color=m_color;
    newprint_elementPos->m_graphic_Font=m_graph_Font;
    newprint_elementPos->m_rotate=m_rotate;
    mdbprint_elementPos.push_back(newprint_elementPos);
}

double QGScene::GetInfoX(int aid)
{
    double x=0;
    for(idbprint_elementPos=mdbprint_elementPos.begin();idbprint_elementPos<mdbprint_elementPos.end();idbprint_elementPos++)
    {
        if((*idbprint_elementPos)->id==aid)
        {
            x=(*idbprint_elementPos)->m_x;
        }
    }
    return x;
}

QColor QGScene::getColor(int aid)
{
    QColor x;
    for(idbprint_elementPos=mdbprint_elementPos.begin();idbprint_elementPos<mdbprint_elementPos.end();idbprint_elementPos++)
    {
        if((*idbprint_elementPos)->id==aid)
        {
            x=(*idbprint_elementPos)->m_color;
        }
    }
    return x;
}


QFont QGScene::getGraphicFont(int aid)
{
    QFont x;
    for(idbprint_elementPos=mdbprint_elementPos.begin();idbprint_elementPos<mdbprint_elementPos.end();idbprint_elementPos++)
    {
        if((*idbprint_elementPos)->id==aid)
        {
            x=(*idbprint_elementPos)->m_graphic_Font;
        }
    }
    return x;
}

double QGScene::GetInfoY(int aid)
{
    double y=0;
    double h=(double)1000/(double)e_row;
    for(idbprint_elementPos=mdbprint_elementPos.begin();idbprint_elementPos<mdbprint_elementPos.end();idbprint_elementPos++)
    {
        if((*idbprint_elementPos)->id==aid)
        {
            y=(*idbprint_elementPos)->m_y;
        }
    }
    return y;
}


void QGScene::addInfoImage(int aid,double ax,double ay,QByteArray m_data,double m_scale,double m_scale_w)
{
    newprint_elementImagePos=new dbprint_elementImagePos;
    newprint_elementImagePos->id=aid;
    newprint_elementImagePos->m_x=ax;
    newprint_elementImagePos->m_y=ay;
    newprint_elementImagePos->m_data=m_data;
    newprint_elementImagePos->m_scale=m_scale;
    newprint_elementImagePos->m_scale_w=m_scale_w;
    mdbprint_elementImagePos.push_back(newprint_elementImagePos);
}

double QGScene::GetInfoImageX(int aid)
{
    double x=0;
    for(idbprint_elementImagePos=mdbprint_elementImagePos.begin();idbprint_elementImagePos<mdbprint_elementImagePos.end();idbprint_elementImagePos++)
    {
        if((*idbprint_elementImagePos)->id==aid)
        {
            x=(*idbprint_elementImagePos)->m_x;
        }
    }
    return x;
}

QByteArray QGScene::GetInfoImageData(int aid)
{
    QByteArray x=QByteArray(0);
    for(idbprint_elementImagePos=mdbprint_elementImagePos.begin();idbprint_elementImagePos<mdbprint_elementImagePos.end();idbprint_elementImagePos++)
    {
        if((*idbprint_elementImagePos)->id==aid)
        {
            x=(*idbprint_elementImagePos)->m_data;
        }
    }
    return x;
}

double QGScene::GetInfoImageY(int aid)
{
    double y=0;
    for(idbprint_elementImagePos=mdbprint_elementImagePos.begin();idbprint_elementImagePos<mdbprint_elementImagePos.end();idbprint_elementImagePos++)
    {
        if((*idbprint_elementImagePos)->id==aid)
        {
            y=(*idbprint_elementImagePos)->m_y;
        }
    }
    return y;
}



void QGScene::scaleSelectedItem(double scale)
{
    double w=(double)707/(double)e_col;
    double h=(double)1000/(double)e_row;

    QList <QGraphicsItem*> itemList=selectedItems();
    if(!itemList.isEmpty())
    {
        if(qgraphicsitem_cast<QLab1Picture*>(itemList.at(0)))
        {
            qreal x2=0;
            qreal y2=(((QLab1Picture*)itemList.at(0))->boundingRect().height()/2);
            int id=((QLab1Picture*)itemList.at(0))->GetId();
            for(idbprint_elementPos=mdbprint_elementPos.begin();idbprint_elementPos<mdbprint_elementPos.end();idbprint_elementPos++)
            {
                if((*idbprint_elementPos)->id==id)
                {
                    (*idbprint_elementPos)->m_rotate>360-scale?(*idbprint_elementPos)->m_rotate+=scale-360:(*idbprint_elementPos)->m_rotate+=scale;
                    ((QLab1Picture*)itemList.at(0))->setTransform(QTransform().translate(x2, y2).rotate((*idbprint_elementPos)->m_rotate).translate(-x2,-y2));
                }
            }
        }
    }
    update();
    m_stat_update=true;
}


QColor QGScene::GetColorText()
{
    QColor ecolor;
    QList <QGraphicsItem*> itemList=selectedItems();
    if(!itemList.isEmpty())
    {
        if(qgraphicsitem_cast<QLab1Picture*>(itemList.at(0)))
        {
            itemList.at(0);
            int id=((QLab1Picture*)itemList.at(0))->GetId();
            ecolor=((QLab1Picture*)itemList.at(0))->defaultTextColor();
        }
    }
    else
    {
        ecolor=Qt::white;
    }
    return ecolor;
}

void QGScene::setColorText(QColor m_color)
{
    QList<QGraphicsItem *> itemList=selectedItems();
    double x,y;
    int id;
    foreach (QGraphicsItem *item, itemList)
    {
        if(item->type() == QLab1Picture::Type)
        {
            id=((QLab1Picture*)item)->GetId();
            ((QLab1Picture*)item)->setDefaultTextColor(m_color);
            for(idbprint_elementPos=mdbprint_elementPos.begin();idbprint_elementPos<mdbprint_elementPos.end();idbprint_elementPos++)
            {
                if((*idbprint_elementPos)->id==id)
                {
                    (*idbprint_elementPos)->m_color=m_color;
                }
            }
        }
        if(item->type() == QLab1PixmapItem::Type)
        {
            double m_scale_temp=0.0f;
            double m_scale_w_temp=0.0f;
            id=((QLab1PixmapItem*)item)->GetId();
            for(idbprint_elementImagePos=mdbprint_elementImagePos.begin();idbprint_elementImagePos<mdbprint_elementImagePos.end();idbprint_elementImagePos++)
            {
                if((*idbprint_elementImagePos)->id==id)
                {
                    m_scale_temp=(*idbprint_elementImagePos)->m_scale;
                    m_scale_w_temp=(*idbprint_elementImagePos)->m_scale_w;
                }
            }

            QRect r=((QLab1PixmapItem*)item)->pixmap().rect();
            ((QLab1PixmapItem*)item)->setColor1(m_color,r,m_scale_temp,m_scale_w_temp);

            QByteArray bytesA;
            QBuffer bufferA(&bytesA);
            bufferA.open(QIODevice::WriteOnly);
            ((QLab1PixmapItem*)item)->pixmap().save(&bufferA, "PNG"); // writes pixmap into bytes in PNG format
            for(idbprint_elementImagePos=mdbprint_elementImagePos.begin();idbprint_elementImagePos<mdbprint_elementImagePos.end();idbprint_elementImagePos++)
            {
                if((*idbprint_elementImagePos)->id==id)
                {
                    (*idbprint_elementImagePos)->m_data=bytesA;
                    (*idbprint_elementImagePos)->m_scale=1.0f;
                    (*idbprint_elementImagePos)->m_scale_w=1.0f;
                }
            }
        }

    }
}

void QGScene::setTextFont(QFont m_graph_font)
{
    QList<QGraphicsItem *> itemList=selectedItems();
    double x,y;
    int id;
    foreach (QGraphicsItem *item, itemList)
    {
        if(item->type() == QLab1Picture::Type)
        {
            id=((QLab1Picture*)item)->GetId();
            ((QLab1Picture*)item)->setFont(m_graph_font);
            for(idbprint_elementPos=mdbprint_elementPos.begin();idbprint_elementPos<mdbprint_elementPos.end();idbprint_elementPos++)
            {
                if((*idbprint_elementPos)->id==id)
                {
                    (*idbprint_elementPos)->m_graphic_Font=m_graph_font;
                }
            }
        }
    }
}

double QGScene::getWidth(int aid)
{
    double x=0;
    InitilizeItems();
    for(idbprint_elementPos=mdbprint_elementPos.begin();idbprint_elementPos<mdbprint_elementPos.end();idbprint_elementPos++)
    {
        if((*idbprint_elementPos)->id==aid)
        {
            x=(*idbprint_elementPos)->m_width;
        }
    }
    return x;
}

double QGScene::getScale(int aid)
{
    double x=0;
    InitilizeItems();
    for(idbprint_elementPos=mdbprint_elementPos.begin();idbprint_elementPos<mdbprint_elementPos.end();idbprint_elementPos++)
    {
        if((*idbprint_elementPos)->id==aid)
        {
            x=(*idbprint_elementPos)->m_scale;
        }
    }
    return x;
}

double QGScene::getScaleW(int aid)
{
    double x=0;
    InitilizeItems();
    for(idbprint_elementPos=mdbprint_elementPos.begin();idbprint_elementPos<mdbprint_elementPos.end();idbprint_elementPos++)
    {
        if((*idbprint_elementPos)->id==aid)
        {
            x=(*idbprint_elementPos)->m_scalew;
        }
    }
    return x;
}

double QGScene::getHeight(int aid)
{
    double x=0;
    InitilizeItems();
    for(idbprint_elementPos=mdbprint_elementPos.begin();idbprint_elementPos<mdbprint_elementPos.end();idbprint_elementPos++)
    {
        if((*idbprint_elementPos)->id==aid)
        {
            x=(*idbprint_elementPos)->m_height;
        }
    }
    return x;
}

void QGScene::autoSelectedItem()
{
    QList <QGraphicsItem*> itemList=selectedItems();
    QList <QGraphicsItem*>::iterator iter;
    if(!itemList.isEmpty())
    {
        // 		if(qgraphicsitem_cast<QLab1Picture*>(itemList.at(0)))
        {
            qreal x =((QLab1Picture*)itemList.at(0))->pos().x();
            qreal y =((QLab1Picture*)itemList.at(0))->pos().y();
            //			foreach (QGraphicsItem *item, itemList)
            for(iter=itemList.begin();iter<itemList.end();iter++)
            {
                // 				if(qgraphicsitem_cast<QLab1Picture*>(*iter))
                {

                    (*iter)->setPos(x,(*iter)->pos().y());
                    //y+=(*iter)->boundingRect().height()*3/4;
                }
            }
        }
    }

}

void QGScene::autoBottomSelectedItem()
{
    QList <QGraphicsItem*> itemList=selectedItems();
    QList <QGraphicsItem*>::iterator iter;
    if(!itemList.isEmpty())
    {
        // 		if(qgraphicsitem_cast<QLab1Picture*>(itemList.at(0)))
        {
            qreal x =((QLab1Picture*)itemList.at(0))->pos().x();
            qreal y =((QLab1Picture*)itemList.at(0))->pos().y();
            //			foreach (QGraphicsItem *item, itemList)
            for(iter=itemList.begin();iter<itemList.end();iter++)
            {
                // 				if(qgraphicsitem_cast<QLab1Picture*>(*iter))
                {

                    (*iter)->setPos((*iter)->pos().x(),y);
                    //y+=(*iter)->boundingRect().height()*3/4;
                }
            }
        }
    }

}
void QGScene::itemsShowGridBorderVisible()
{
    QList<QGraphicsItem *> itemList=items();
    foreach (QGraphicsItem *item, itemList)
    {
        if(item->type() == QLab1Picture::Type)
        {
            ((QLab1Picture*)item)->SetFlagOn();
        }
    }
}

void QGScene::itemsHideGridBorder()
{
    QList<QGraphicsItem *> itemList=items();
    foreach (QGraphicsItem *item, itemList)
    {
        if(item->type() == QLab1Picture::Type)
        {
            ((QLab1Picture*)item)->SetFlagOff();
        }
    }
}


QFont QGScene::GetGpahicsFont()
{
    QFont vFont;
    QList<QGraphicsItem *> itemList=selectedItems();
    foreach (QGraphicsItem *item, itemList)
    {
        if(item->type() == QLab1Picture::Type)
        {
            int id=-1;
            id=((QLab1Picture*)item)->GetId();
            for(idbprint_elementPos=mdbprint_elementPos.begin();idbprint_elementPos<mdbprint_elementPos.end();idbprint_elementPos++)
            {
                if((*idbprint_elementPos)->id==id)
                {
                    vFont=((*idbprint_elementPos)->m_graphic_Font);
                }
            }
        }
    }
    return vFont;
}

void QGScene::drawForeground(QPainter * painter, const QRectF & rect)
{
    if(stat_selected)
    {
        painter->setPen(Qt::DashDotLine);
        painter->drawRect(m_A.x(),m_A.y(),m_B.x()-m_A.x(),m_B.y()-m_A.y());
    }
    if(stat_resize)
    {
        painter->setPen(Qt::DashDotLine);
        painter->setPen( Qt::red );
        painter->drawRect(m_Aresize.x(),m_Aresize.y(),m_Bresize.x()-m_Aresize.x(),m_Bresize.y()-m_Aresize.y());
        painter->setPen( Qt::black );
    }
}

double QGScene::GetRotate(int aid)
{
    double x;
    for(idbprint_elementPos=mdbprint_elementPos.begin();idbprint_elementPos<mdbprint_elementPos.end();idbprint_elementPos++)
    {
        if((*idbprint_elementPos)->id==aid)
        {
            x=(*idbprint_elementPos)->m_rotate;
        }
    }
    return x;
}
void QGScene::setRotate(double m_rotate)
{
    QList<QGraphicsItem *> itemList=selectedItems();
    double x,y;
    int id;
    foreach (QGraphicsItem *item, itemList)
    {
        if(item->type() == QLab1Picture::Type)
        {
            id=((QLab1Picture*)item)->GetId();
            qreal x=0;
            qreal y=(((QLab1Picture*)item)->boundingRect().height()/2);
            ((QLab1Picture*)item)->setTransform(QTransform().translate(x, y).rotate(m_rotate).translate(-x, -y));
            for(idbprint_elementPos=mdbprint_elementPos.begin();idbprint_elementPos<mdbprint_elementPos.end();idbprint_elementPos++)
            {
                if((*idbprint_elementPos)->id==id)
                {
                    (*idbprint_elementPos)->m_rotate=m_rotate;
                }
            }
        }
    }
}
