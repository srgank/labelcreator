#ifndef QMYMENULEFT_H
#define QMYMENULEFT_H

#include <QWidget>
#include "ui_qmymenuleft.h"
#include "qarticle.h"

class QMyMenuLeft : public QWidget
{
	Q_OBJECT

public:
	QMyMenuLeft(QWidget *parent = 0);
	~QMyMenuLeft();

private:
	int stat;
	Ui::QMyMenuLeftClass ui;
	QArticle *m_article;
private slots:
// 	void on_pushButton_3_clicked();
	void on_pushButton_clicked();
	void on_pushButton_7_clicked();
// 	void on_pushButton_5_clicked();
// 	void on_pushButton_2_clicked();
// 	void on_pushButton_4_clicked();
signals:
	void pressbuttonDeleteRow();
	void pressbuttonInsertRow();
	void pressbuttonPreview(int m_row,int m_col);
	void pressbuttonPrint(int m_row,int m_col);
	void showDesigner(int m_row,int m_col);
	void showTable();
public:
	void setValue(int col,int row);
};

#endif // QMYMENULEFT_H
