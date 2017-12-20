#ifndef QLABELLICENCE_H
#define QLABELLICENCE_H

#include <QDialog>
#include "ui_qlabellicence.h"

class QLabelLicence : public QDialog
{
	Q_OBJECT

public:
	QLabelLicence(QWidget *parent = 0);
	~QLabelLicence();
	void initSS(int i);


private:
	Ui::QLabelLicenceClass ui;

private slots:
	void on_label_6_linkActivated(QString);
	void on_label_6_linkHovered(QString);
//	void on_pushButton_clicked();
	void on_pushButton_2_clicked();
signals:
	void setRegisteredData(QString s1,QString s2,QString s3);
};

#endif // QLABELLICENCE_H
