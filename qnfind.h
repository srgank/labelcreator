#ifndef QNFIND_H
#define QNFIND_H

#include <QWidget>
#include "ui_qnfind.h"

class QNFind : public QWidget
{
	Q_OBJECT

public:
	QNFind(QWidget *parent = 0);
	~QNFind();

private:
	Ui::QNFindClass ui;

private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_lineEdit_returnPressed();
signals:
	void s_returnPressed(QString s);
	void s_next_Pressed();
	void s_previous_Pressed();

};

#endif // QNFIND_H
