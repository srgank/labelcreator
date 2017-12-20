#ifndef QARTICLE_H
#define QARTICLE_H

#include <QDialog>
#include "ui_qarticle.h"

class QArticle : public QDialog
{
	Q_OBJECT

public:
	QArticle(QWidget *parent = 0);
	~QArticle();
	void initData(QStringList s);
	void setFontLabels(QFont m_font1,QFont m_font2,QFont m_font3,QFont m_font4,
		QFont m_font5,QFont m_font6,QFont m_font7,QFont m_font8);

private:
	Ui::QArticleClass ui;

private slots:
	void on_pushButton_clicked();
signals:
	void enter_article(QStringList s);

};

#endif // QARTICLE_H
