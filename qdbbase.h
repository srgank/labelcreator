#ifndef QDBBASE_H
#define QDBBASE_H

#include <QWidget>
#include <QVector>
#include <QStringList>
#include <QTableWidget>





class QDBBase : public QWidget
{
//	Q_OBJECT
public:
	typedef struct db_element{
		QString m_A1;
		QString m_B1;
		QString m_C1;
		QString m_D1;
		QString m_A2;
		QString m_B2;
		QString m_C2;
		QString m_D2;
		QString m_Count;
		QFont m_f1;
		QFont m_f2;
		QFont m_f3;
		QFont m_f4;
		QFont m_f5;
		QFont m_f6;
		QFont m_f7;
		QFont m_f8;
	} *pdb_element;


public:
	pdb_element new_element;
	QDBBase(QWidget *parent);
	~QDBBase();

	QVector <pdb_element> mdb_element;
	QVector <pdb_element>::iterator idb_element;

	int addRecord(QString x_a1,QString x_b1,QString x_c1,QString x_d1,
		QString x_a2,QString x_b2,QString x_c2,QString x_d2,QString x_count);
	void removeRecord(QString m_searchString);
	void loadRecordsFromFile();
	void saveRecordsToFile();
	void saveAsRecordsToFile();
	bool fExistFileName();
	QString getFileName();
	QString m_filename;
	void setLabel(QStringList sl);
	QStringList getLabel();
	void setFonts(QVector<QFont*> sl);
	QVector<QFont*> getFonts();

	void loadRecordsFromFileExtended(QString filename);
	void ccsignal(QPoint s);


private:
	QString m_label1;
	QString m_label2;
	QString m_label3;
	QString m_label4;
	QString m_label5;
	QString m_label6;
	QString m_label7;
	QString m_label8;

	QFont m_font1;
	QFont m_font2;
	QFont m_font3;
	QFont m_font4;
	QFont m_font5;
	QFont m_font6;
	QFont m_font7;
	QFont m_font8;


	QVector<QFont *> m_fonts;
	QVector<QFont *>::iterator i_fonts;

Q_SIGNALS:
	void sendMouseRightClick1(QPoint s);

};

#endif // QDBBASE_H
