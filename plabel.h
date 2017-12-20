#ifndef PLABEL_H
#define PLABEL_H

#include <QMainWindow>
#include "ui_plabel.h"
#include <QListWidget>
#include <QDockWidget>
#include "qmymenuleft.h"
#include <QTableWidget>
#include "qstablewidget.h"
#include <QVector>
#include <QFontComboBox>
#include "qstablewidgetdelegate.h"
#include <QPrinter>
#include "qlab1picture.h"
#include "qgscene.h"
#include "qlab1pixmapitem.h"
#include <QGraphicsView>
#include "qmygraphicsrectitem.h"






#define  CR_2X6    0
#define  CR_3X7    1
#define  CR_4X9    2

class PLabel : public QMainWindow
{
	Q_OBJECT

private:
	typedef struct dbprint_element{
			QString m_element;
			QFont m_element_font;
	} *pdbprint_element;

	pdbprint_element newprint_element;

	QVector <pdbprint_element> mdbprint_element;
	QVector <pdbprint_element>::iterator idbprint_element;



	typedef struct dbprint_elementPos{
		int id;
		int tip;
		double m_x;
		double m_y;
		double m_width;
		double m_height;
		QColor m_color;
		QFont m_graphic_Font;
		double m_rotate;
	} *pdbprint_elementPos;

	pdbprint_elementPos newprint_elementPos;

	QVector <pdbprint_elementPos> mdbprint_elementPos;
	QVector <pdbprint_elementPos>::iterator idbprint_elementPos;
	bool statPosChanged;
	typedef QVector<pdbprint_elementPos> Typemdbprint_elementPos;
	Typemdbprint_elementPos  xx;


	typedef QVector<pdbprint_elementPos> tmdbprint_elementPos;



	typedef struct dbprint_elementImagePos{
		int id;
		int tip;
		double m_x;
		double m_y;
		QByteArray m_data;
		double m_scale;
		double m_scale_w;
	} *pdbprint_elementImagePos;

	pdbprint_elementImagePos newprint_elementImagePos;

	QVector <pdbprint_elementImagePos> mdbprint_elementImagePos;
	QVector <pdbprint_elementImagePos>::iterator idbprint_elementImagePos;

	QColor m_backgroundColor;

public:
    PLabel(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	QGraphicsRectItem *m_root;
	void createDockWindows();
	QString generateSSIDNumber();
	bool generateSSID2Number(QString m_name);
	void createLicenceDialog();
	void showDataFromFileExtended(QString filename);
	QDate getDate();
	void setDate(QDate d);

	void setInitialDate(QDate d,QTime t);
	QTime getEntryTime();
	QTime getExitTime();
	void setEntryTime();
	void setExitTime();
	int getTrialDay();
	void setTrialDay(int days);
	bool trialLogin();


	~PLabel();

private:
	qreal m_zvalue_images;
	int max_image_count;
	tmdbprint_elementPos m_vectorPrintElementPos;
	bool sceneInit;
	QGraphicsRectItem * m_center;
	double www;
	double hhh;
	QGScene *scene;
	QGraphicsView *view;
	QLab1Picture *lpic1;
	QLab1PixmapItem *lpix1;
	QMyGraphicsRectItem *lrectItem;
    void addItemScene(int id,double bx,double by,QString m_info,QFont m1_font, QColor m_color,qreal m_zvalue, double m_rotate);
	void addPixItemScene(int bx,int by,QString m_info);
	bool rglprd;
	QAction *recentFileActs[4];
	QString lic_name;
	int mr_total;
	QListWidget	*customerList;
	QListWidget	*paragraphsList;
	QDockWidget *dock,*dock1;
	QDockWidget *dock_graphics;
	Ui::PLabelClass ui;
	QMyMenuLeft *m_left;
	QSTableWidget *tableWidget;
	virtual void resizeEvent(QResizeEvent * event);
	virtual void closeEvent(QCloseEvent *event);
	int m_printformat;
	int e_row;
	int e_col;
	QFont m_Font;
	QFont m_Font_default;
	QFont m_Font_fontbox1;
	int saveFlag;
	bool statusFontWrite;
	int m_arow,m_acol,m_brow,m_bcol;
	int m_atop,m_abottom,m_aleft,m_aright;
	int Column_0_Width;
    int Column_1_Width;
	int Column_2_Width;
	int Column_3_Width;
	int Column_4_Width;
	int Column_5_Width;
	int Column_6_Width;
	int Column_7_Width;
	int Column_8_Width;

	QFontComboBox  fontbox1;
	QComboBox fontSizeBox1;
	QSTableWidgetDelegate *p;

	QString m_copyedString;
	QStringList labels;
	QVector<QFont*> msrg_fonts;
	QString reg_name;
	void writeSettings();
	void readSettings();
signals:
	void setProgressS(int arow,int acount);

public:
	void loadFile(const QString &fileName);
private slots:
	void on_actionaaa_triggered();
	void on_actionadd_object_triggered();
	void on_actionAddShapeItem_triggered();
	void on_actionHelp_2_triggered();
	void on_actionItalic_triggered();
	void on_actionShowBorder_triggered();
	void on_actionBackGroundColor_triggered();
	void on_actionTopAligment_triggered();
	void on_actionAutoPos_triggered();
	void on_actionExportImage_triggered();
	void on_actioncolor_triggered();
	void on_actionFontBold_triggered();
	void on_actionScaled1_triggered();
	void on_actionScaled_triggered();
	void on_actionBringToFront_triggered();
	void on_actionSendToBack_triggered();
	void on_actionDelete_triggered();
	void on_actionDel_triggered();
	void on_actionAdd_GraphicsItem_triggered();
	void on_actionAdd_GraphicsObject();
	void LabelPreview(int m_row,int m_col);
	void showTable();
	void on_actionZoom_Out_triggered();
	void on_actionZoom_In_triggered();
	void openRecentFile();
	void on_actionExpand_in_Rows_triggered();
	void on_actionConcatenate_Rows_triggered();
	void on_actionRemove_Empty_Rows_triggered();
	void on_actionUndo_triggered();
	void on_actionExpand_triggered();
	void on_actionConcatenate_triggered();
	void on_actionRemove_Columns_triggered();

	void on_actionAdd_Column_triggered();
	void on_actionFind_Previous_triggered();
	void on_actionFind_Next_triggered();
	void on_actionPage_Settings_triggered();
	void on_action_triggered();
	void on_actionCut_triggered();
	void on_actionFind_triggered();
	void on_actionAbout_2_triggered();
	void on_actionLabel_Settings_triggered();
	void on_actionRemove_Records_triggered();
	void on_actionAdd_Records_triggered();
	void on_actionPaste_triggered();
	void on_actionCopy_triggered();
	void on_actionFont_triggered();
	void on_actionNew_2_triggered();
	void on_actionNew_triggered();
	void on_actionClose_triggered();
	void on_actionSave_As_triggered();
	void on_actionSave_triggered();
	void on_actionOpen_triggered();
	void on_actionExit_triggered();
	void on_actionNavigate_triggered();
	void showDataFromFile();
	void SaveDataFromFile();
	void SaveAsDataFromFile();
	void PressedItem(int x,int y);
	void filePrintPreview(int x_row,int x_col);
	void printPreview(QPrinter *printer);
	void filePrint(int x_row,int x_col);
	void removeRowSTableWidget();
	void insertRowSTableWidget();
	void tableWidgetcellChanged(int arow,int acol);
	void setLabelSettings(QStringList s);
	void checkRegisteredData(QString s1,QString s2,QString s3);
	void tableWidgetcellProgresBar(int arow,int atotal);
	void findStringInTable(QString s);
	void findStringNextInTable();
	void findStringPreviousInTable();
	void createPopupTableWidgetMenu(QPoint s);
	void writeValuesPageMargin(int a,int b,int c,int d);
	void ComboCurrentFontChanged(const QFont & afont);
	void tableWidgetcellPressed(int arow,int acol,int prow,int pcol);
	void tableWidgetcellClicked(int arow,int acol);
	void ComboCurrentActivated(int aIndex);
	void sendToBack();
	void backToFront();
	void ChangeFontGraphicsFont();
	};

#endif // PLABEL_H
