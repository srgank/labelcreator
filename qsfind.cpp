#include "qsfind.h"

QSFind::QSFind(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
}

QSFind::~QSFind()
{

}


void QSFind::on_lineEdit_returnPressed()
{
    emit s_returnPressed(ui.lineEdit->text());
    ui.pushButton_2->setFocus();
}

void QSFind::on_pushButton_2_clicked()
{
    emit s_next_Pressed();
}

void QSFind::on_pushButton_clicked()
{
    emit s_previous_Pressed();
}
