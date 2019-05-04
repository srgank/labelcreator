#include "qarticle.h"


QArticle::QArticle(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
}

QArticle::~QArticle()
{

}
void QArticle::on_pushButton_clicked()
{
    QStringList s;
    s<<ui.lineEdit->text()<<ui.lineEdit_2->text()<<ui.lineEdit_3->text()<<ui.lineEdit_4->text()
    <<ui.lineEdit_5->text()<<ui.lineEdit_6->text()<<ui.lineEdit_7->text()<<ui.lineEdit_8->text()<<"Count";
    emit enter_article(s);
    close();
}

void QArticle::initData(QStringList s)
{
    ui.lineEdit->setText(s.at(0));
    ui.lineEdit_2->setText(s.at(1));
    ui.lineEdit_3->setText(s.at(2));
    ui.lineEdit_4->setText(s.at(3));
    ui.lineEdit_5->setText(s.at(4));
    ui.lineEdit_6->setText(s.at(5));
    ui.lineEdit_7->setText(s.at(6));
    ui.lineEdit_8->setText(s.at(7));
}

void QArticle::setFontLabels(QFont m_font1,QFont m_font2,QFont m_font3,QFont m_font4,
                             QFont m_font5,QFont m_font6,QFont m_font7,QFont m_font8)
{
    ui.lineEdit->setFont(m_font1);
    ui.lineEdit_2->setFont(m_font2);
    ui.lineEdit_3->setFont(m_font3);
    ui.lineEdit_4->setFont(m_font4);
    ui.lineEdit_5->setFont(m_font5);
    ui.lineEdit_6->setFont(m_font6);
    ui.lineEdit_7->setFont(m_font7);
    ui.lineEdit_8->setFont(m_font8);

}
