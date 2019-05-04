#include "qspagesettings.h"

QSPageSettings::QSPageSettings(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
}

QSPageSettings::~QSPageSettings()
{

}


void QSPageSettings::on_pushButton_clicked()
{
    int m_top=ui.spinBox->value();
    int m_bottom=ui.spinBox_4->value();
    int m_left=ui.spinBox_3->value();
    int m_right=ui.spinBox_2->value();
    emit sendValuesPageMargin(m_top,m_bottom,m_left,m_right);
    close();
}

void QSPageSettings::initData(int m_atop,int m_abottom,int m_aleft,int m_aright)
{
    ui.spinBox->setValue(m_atop);
    ui.spinBox_4->setValue(m_abottom);
    ui.spinBox_3->setValue(m_aleft);
    ui.spinBox_2->setValue(m_aright);
}
