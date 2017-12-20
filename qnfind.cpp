#include "qnfind.h"

QNFind::QNFind(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

QNFind::~QNFind()
{

}


void QNFind::on_lineEdit_returnPressed()
{
	emit s_returnPressed(ui.lineEdit->text());
	ui.pushButton_2->setFocus();
}

void QNFind::on_pushButton_2_clicked()
{
emit s_next_Pressed();
}

void QNFind::on_pushButton_clicked()
{
emit s_previous_Pressed();
}