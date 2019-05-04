#include "qmymenuleft.h"

QMyMenuLeft::QMyMenuLeft(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    ui.pushButton_7->hide();
    stat=1;
}

QMyMenuLeft::~QMyMenuLeft()
{

}


// void QMyMenuLeft::on_pushButton_4_clicked()
// {
// emit pressbuttonInsertRow();
// }

// void QMyMenuLeft::on_pushButton_2_clicked()
// {
// emit pressbuttonDeleteRow();
// }

// void QMyMenuLeft::on_pushButton_5_clicked()
// {
// 
// 	if(ui.radioButton_2->isChecked()==TRUE) //3X7
// 	{
// 		emit pressbuttonPrint(7,3);
// 	}
// 	if(ui.radioButton->isChecked()==TRUE)
// 	{
// 		emit pressbuttonPrint(6,2);   //2X6
// 	}
// 
// 	if(ui.radioButton_3->isChecked()==TRUE)
// 	{
// 		emit pressbuttonPrint(9,4);   //4X9
// 	}
// 	if(ui.radioButton_4->isChecked()==TRUE)
// 	{
// 		emit pressbuttonPrint(ui.spinBox_2->value(),ui.spinBox->value());   //4X9
// 	}
// }

void QMyMenuLeft::on_pushButton_7_clicked()
{
    if(ui.radioButton_2->isChecked()==true) //3X7
    {
        emit pressbuttonPreview(7,3);
    }
    if(ui.radioButton->isChecked()==true)
    {
        emit pressbuttonPreview(6,2);   //2X6
    }

    if(ui.radioButton_3->isChecked()==true)
    {
        emit pressbuttonPreview(9,4);   //4X9
    }
    if(ui.radioButton_4->isChecked()==true)
    {
        emit pressbuttonPreview(ui.spinBox_2->value(),ui.spinBox->value());   //4X9
    }
}



void QMyMenuLeft::on_pushButton_clicked()
{
    if(stat==1)
    {
        if(ui.radioButton_2->isChecked()==true) //3X7
        {
            emit showDesigner(7,3);
        }
        if(ui.radioButton->isChecked()==true)
        {
            emit showDesigner(6,2);   //2X6
        }

        if(ui.radioButton_3->isChecked()==true)
        {
            emit showDesigner(9,4);   //4X9
        }
        if(ui.radioButton_4->isChecked()==true)
        {
            emit showDesigner(ui.spinBox_2->value(),ui.spinBox->value());   //4X9
        }
        ui.pushButton->setText("Show Table");
        ui.pushButton_7->show();
        ui.radioButton->hide();
        ui.radioButton_2->hide();
        ui.radioButton_3->hide();
        ui.radioButton_4->hide();
        ui.label->hide();
        ui.label_2->hide();
        ui.spinBox->hide();
        ui.spinBox_2->hide();

        stat=2;
    }
    else
    {
        emit showTable();
        ui.pushButton->setText("Show Designer");
        ui.radioButton->show();
        ui.radioButton_2->show();
        ui.radioButton_3->show();
        ui.radioButton_4->show();
        ui.spinBox->show();
        ui.spinBox_2->show();
        ui.pushButton_7->hide();
        ui.label->show();
        ui.label_2->show();
        stat=1;
    }
}

// void QMyMenuLeft::on_pushButton_3_clicked()
// {
// 	
// }

void QMyMenuLeft::setValue(int col,int row)
{
    ui.radioButton_4->setChecked(true);
    ui.spinBox->setValue(col);
    ui.spinBox_2->setValue(row);
}
