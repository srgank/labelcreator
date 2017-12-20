#ifndef QSTABLEWIDGET_H
#define QSTABLEWIDGET_H

#include <QTableWidget>

class QSTableWidget : public QTableWidget
{
	Q_OBJECT

public:
	QSTableWidget(QWidget *parent);
	~QSTableWidget();
	virtual void setGeometry(const QRect &r); 
	virtual void show(); 
	virtual QWidget * focusWidget();
	virtual void setFont( const QFont &f);
	void showDBD();
	void showDBDExtended(QString filename);
	void addItemsDBD(int maxrow,int m_cnt,int m_column);
	void CopyTableToDBD();
	void CopySaveAsTableToDBD();
	QString getCurrentA1();
	QString getCurrentB1();
	QString getCurrentC1();
	QString getCurrentD1();
	QString getCurrentA2();
	QString getCurrentB2();
	QString getCurrentC2();
	QString getCurrentD2();
	bool isSTableChanged();
	int findSTableItems(QString m_findString);
	int findNextSTableItems();
	int findPreviousSTableItems();
	void removeSelectedSItems();
	void removeSelectedSColumn(int&,int&);
	void concatenateSelectedSColumn();
	void expandSelectedSColumn();
	void save_to_undo();
	void undo();
	void removeSelectedEmptyRows();
	void concatenateSelectedSRows();
	void expandSelectedSRows();
protected:
//	bool eventFilter( QObject *obj, QEvent *ev );

	private slots:
		void treeContextMenu(const QPoint& aPosition );

private:
	bool m_tablechanged;
	int m_find_item_count;
	int copyundo_status;
	QList<QTableWidgetItem *> m_find;
	QList<QTableWidgetItem *>::iterator i_find;
	virtual void contextMenuEvent(QContextMenuEvent *event);

signals:
	void sendMouseRightClick1(QPoint s);



////////////////////////////////////////////////////////////////////////////////////////////////////////

public:

	typedef struct db_header{
		int magic_id;
		int m_rows_count;
		int m_cols_count;
		int m_preview_rows;
		int m_preview_cols;
		QString rowHeightInfo;
		QString colWidthInfo;
		QString lxyInfo;
		QColor lbackGroundColor;
	} *pdb_header;

/*
	typedef struct db_element_hdr{
		QString m_cell_desc;
		QFont m_cell_font;
	} *pdb_element_hdr;
*/

	typedef struct db_element_new{
		QString m_cell_desc;
		QFont m_cell_font;
		QColor m_color;
		QFont m_graph_font;
		double m_rotate;

	} *pdb_element_new;

	typedef struct db_element_expand{
		int erow;
		int ecol;
		int epos;
		QString e_description;
	}*pdb_element_expand;


	typedef struct db_ImageInfo{
		int id;
		int tip;
		double m_x;
		double m_y;
		QByteArray m_data;
		double m_scale;
		double m_scale_w;
	} *pdbImageInfo;


public:


	pdb_header element_hdr;
	QVector <pdb_header> mdb_hdr;
	QVector <pdb_header>::iterator idb_hdr;

	pdb_element_new element_new;
	QVector <pdb_element_new> mdb_element_new;
	QVector <pdb_element_new>::iterator idb_element_new;


	pdb_header element_hdr_undo;
	QVector <pdb_header> mdb_hdr_undo;
	QVector <pdb_header>::iterator idb_hdr_undo;

	pdb_element_new element_new_undo;
	QVector <pdb_element_new> mdb_element_new_undo;
	QVector <pdb_element_new>::iterator idb_element_new_undo;


	pdb_element_expand element_expand;
	QVector <pdb_element_expand> mdb_element_expand;
	QVector <pdb_element_expand>::iterator idb_element_expand;

	pdbImageInfo element_ImageInfo;
	QVector <pdbImageInfo> mdb_element_ImageInfo;
	QVector <pdbImageInfo>::iterator idb_element_ImageInfo;


	
////////////////////////////////////////////////////////////////////////////////////////////////////////

	void loadRecordsFromFile();
	void saveRecordsToFile();
	void saveAsRecordsToFile();
	bool fExistFileName();
	QString getFileName();
	QString m_filename;

	void loadRecordsFromFileExtended(QString filename);
	void ccsignal(QPoint s);
	void addInfoImage(int aid,double ax,double ay,QByteArray m_data,double m_scale,double m_scale_w);
	QColor getColor(int col);
	void setColor(int col, QColor m_color);
	QFont getGraphicFont(int col);
	void setGraphicFont(int col, QFont m_graphicFont);
	void setRotate(int col, double m_rotate);
    double getRotate(int col);

	QString m_xyInfo;
	QString m_xy_info1;
	int m_rowPreview;
	int m_colPreview;
	QColor cl_backGroundColor;
private:
	QString m_label_cell;
	QFont m_font_cell;
	QColor m_color;
	QFont m_graph_font;
	double m_rotate;
	int  m_image_id;
	int  m_image_tip;
	double  m_image_x;
	double  m_image_y; 
	QByteArray  m_image_data;
	double m_scale;
	double m_scale_w;


};

#endif 
