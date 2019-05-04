#include "qabouts.h"
#include <QPainter>

QAboutS::QAboutS(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
}

QAboutS::~QAboutS()
{

}
void QAboutS::setInfo(QStringList s)
{
    m_ss.clear();
    m_ss=s;
}

void QAboutS::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawText(50,40,m_ss.at(0));
    p.drawText(50,60,m_ss.at(1));
    p.drawText(50,80,m_ss.at(2));
}
