#ifndef QABOUTS_H
#define QABOUTS_H

#include <QDialog>
#include "ui_qabouts.h"

class QAboutS : public QDialog
{
	Q_OBJECT

public:
	QAboutS(QWidget *parent = 0);
	~QAboutS();
	void setInfo(QStringList s);

private:
	Ui::QAboutSClass ui;
	virtual void paintEvent(QPaintEvent *event);
	QStringList m_ss;
};

#endif // QABOUTS_H
