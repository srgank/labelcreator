#ifndef QSPAGESETTINGS_H
#define QSPAGESETTINGS_H

#include <QDialog>
#include "ui_qspagesettings.h"

class QSPageSettings : public QDialog
{
	Q_OBJECT

public:
	QSPageSettings(QWidget *parent = 0);
	~QSPageSettings();
	void initData(int m_atop,int m_abottom,int m_aleft,int m_aright);

private:
	Ui::QSPageSettingsClass ui;

private slots:
	void on_pushButton_clicked();

signals:
	void sendValuesPageMargin(int a,int b,int c,int d);
};

#endif // QSPAGESETTINGS_H
