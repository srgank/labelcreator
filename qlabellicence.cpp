#include "qlabellicence.h"
#include <QDesktopServices>
#include <QUrl>


QLabelLicence::QLabelLicence(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
}

QLabelLicence::~QLabelLicence()
{
    emit setRegisteredData(ui.lineEdit->text(),ui.lineEdit_2->text(),ui.lineEdit_3->text());
}


void QLabelLicence::on_pushButton_2_clicked()
{
    //emit setRegisteredData(ui.lineEdit->text(),ui.lineEdit_2->text(),ui.lineEdit_3->text());
    close();
}

// void QLabelLicence::on_pushButton_clicked()
// {
// 
// }

void QLabelLicence::on_label_6_linkHovered(QString)
{

}

void QLabelLicence::on_label_6_linkActivated(QString)
{
    QDesktopServices::openUrl(QUrl(
                                  "http://www.prolabelcreator.com"
                                  , QUrl::TolerantMode));
}

void QLabelLicence::initSS(int i)
{
    QFont f;
    f.setBold(true);
    ui.label_5->setFont(f);
    switch(i)
    {
    case 1:ui.label_5->setText("You have 1-days left.");break;
    case 2:ui.label_5->setText("You have 2-days left.");break;
    case 3:ui.label_5->setText("You have 3-days left.");break;
    case 4:ui.label_5->setText("You have 4-days left.");break;
    case 5:ui.label_5->setText("You have 5-days left.");break;
    case 6:ui.label_5->setText("You have 6-days left.");break;
    case 7:ui.label_5->setText("You have 7-days left.");break;
    case 8:ui.label_5->setText("You have 8-days left.");break;
    case 9:ui.label_5->setText("You have 9-days left.");break;
    case 10:ui.label_5->setText("You have 10-days left.");break;
    case 11:ui.label_5->setText("You have 11-days left.");break;
    case 12:ui.label_5->setText("You have 12-days left.");break;
    case 13:ui.label_5->setText("You have 13-days left.");break;
    case 14:ui.label_5->setText("You have 14-days left.");break;
    default:
        ui.label_5->setText("You have 0-days left.");break;
    }

}
