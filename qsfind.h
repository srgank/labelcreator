#ifndef QSFIND_H
#define QSFIND_H

#include <QDialog>
#include "ui_qsfind.h"

class QSFind : public QDialog
{
	Q_OBJECT

public:
	QSFind(QWidget *parent = 0);
	~QSFind();

private:
	Ui::QSFindClass ui;

private slots:
	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
	void on_lineEdit_returnPressed();
signals:
	void s_returnPressed(QString s);
	void s_next_Pressed();
	void s_previous_Pressed();
};

#endif // QSFIND_H
