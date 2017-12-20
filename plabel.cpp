#include "plabel.h"
#include "qdbbase.h"
#include <QStringList>
#include <QStringListModel>
#include <QListView>
#include <QStandardItemModel>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include <QPrintPreviewDialog>
#include <QFontDialog>
#include "qarticle.h"
#include <QSettings>
#include <QClipboard>
#include <QMimeData>
#include "qlabellicence.h" 
#include <QMessageBox>
#include "qabouts.h"
#include <QTableWidgetSelectionRange>
#include <QProgressBar>
#include "qsfind.h"
#include "qspagesettings.h"
#include "ean13.h"
#include <QDate>
#include <QTime>
#include <QFileDialog>
#include <QBuffer>
#include <QColorDialog>
#include <QDesktopServices>
#include <QUrl>
#include <math.h>







#define  ext_srg1 "***This is DEMO VERSION***"
#define  ext_srg2 "***"
#define  ext_srg3 "This "
#define  ext_srg4 "is "
#define  ext_srg5 "DEMO "
#define  ext_srg6 "VERSION"
#define  ext_srg7 ext_srg2+ext_srg3+ext_srg4+ext_srg5+ext_srg6+ext_srg2


PLabel::PLabel(QWidget *parent, Qt::WindowFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);
	e_col=3;
	e_row=7;
	www=0;hhh=0;
	customerList=NULL;
	dock=NULL;
	tableWidget=NULL;
	m_printformat=0;
	sceneInit=false;
	m_backgroundColor=Qt::white;
	m_copyedString="";
	labels<< "Arial1" << "Helvetica" << "Times" << "Courier"<<"Arial1" << "Helvetica" << "Times" << "Courier"<<"Count";
	statPosChanged=false;
	rglprd=false;
	reg_name="";
	saveFlag=0;
	mr_total=0;
	m_acol=0;
	m_bcol=0;
	m_arow=0;
	m_brow=0;
	m_atop=0;
	m_abottom=0;
	m_aleft=0;
	m_aright=0;
	Column_0_Width=80;
	Column_1_Width=80;
	Column_2_Width=80;
	Column_3_Width=80;
	Column_4_Width=80;
	Column_5_Width=80;
	Column_6_Width=80;
	Column_7_Width=80;
	Column_8_Width=50;
	statusFontWrite=false;
	p=new QSTableWidgetDelegate(this);
	for (int i = 0; i < 1; ++i) {
		recentFileActs[i] = new QAction(this);
		recentFileActs[i]->setVisible(false);
		connect(recentFileActs[i], SIGNAL(triggered()),
			this, SLOT(openRecentFile()));
	}
	readSettings();
	setEntryTime();
	m_Font_default=this->font();
}

PLabel::~PLabel()
{
	setExitTime();
	delete p;
	p=NULL;
}


// QDate PLabel::getDate()
// {
// 	QDate m_Date;
// 	QSettings registry("HKEY_CURRENT_USER\\CLSID\\{1AAA8ADB-2C0B-3C99-8363-087C40ED6682}",QSettings::NativeFormat);
// 	return QDate::fromString(registry.value("Date").toString(),"ddMMyyyy");
// }
// 
// void PLabel::setDate(QDate d)
// {
// 	QSettings settings("HKEY_CURRENT_USER\\CLSID\\{0004565-123OI-123689-458797}",QSettings::NativeFormat);
// 	settings.setValue("Date",d.toString("ddMMyyyy"));
// }
// 
void PLabel::createDockWindows()
{
	dock = new QDockWidget(this);
	dock->setWindowTitle(tr("Navigate"));
	dock->setFixedWidth(120);
	dock->setAllowedAreas(Qt::LeftDockWidgetArea|Qt::RightDockWidgetArea);
	m_left=new QMyMenuLeft(dock);

	connect(m_left,SIGNAL(pressbuttonInsertRow()),this,SLOT(insertRowSTableWidget()));  
	connect(m_left,SIGNAL(pressbuttonDeleteRow()),this,SLOT(removeRowSTableWidget()));  
	connect(m_left,SIGNAL(pressbuttonPrint(int,int)),this,SLOT(filePrint(int,int)));  
	connect(m_left,SIGNAL(pressbuttonPreview(int,int)),this,SLOT(filePrintPreview(int,int))); 
	connect(m_left,SIGNAL(showDesigner(int, int)),this,SLOT(LabelPreview(int ,int))); 
	connect(m_left,SIGNAL(showTable()),this,SLOT(showTable())); 
	dock->setWidget(m_left);
	addDockWidget(Qt::LeftDockWidgetArea, dock);
	connect(&fontbox1,SIGNAL(currentFontChanged(const QFont &)),this,SLOT(ComboCurrentFontChanged(const QFont &)));
	connect(&fontbox1,SIGNAL(activated(int)),this,SLOT(ComboCurrentActivated(int)));

	fontbox1.setFixedWidth(150);
	ui.toolBar->addWidget(&fontbox1);
	fontSizeBox1.setFixedWidth(50);
	fontSizeBox1.addItem(tr("4"));
	fontSizeBox1.addItem(tr("5"));
	fontSizeBox1.addItem(tr("6"));
	fontSizeBox1.addItem(tr("7"));
	fontSizeBox1.addItem(tr("8"));
	fontSizeBox1.addItem(tr("9"));
	fontSizeBox1.addItem(tr("10"));
	fontSizeBox1.addItem(tr("11"));
	fontSizeBox1.addItem(tr("12"));
	fontSizeBox1.addItem(tr("13"));
	fontSizeBox1.addItem(tr("14"));
	fontSizeBox1.addItem(tr("15"));
	fontSizeBox1.addItem(tr("16"));
	fontSizeBox1.addItem(tr("17"));
	fontSizeBox1.addItem(tr("18"));
	fontSizeBox1.addItem(tr("19"));
	fontSizeBox1.addItem(tr("20"));
	fontSizeBox1.addItem(tr("21"));
	fontSizeBox1.addItem(tr("22"));
	fontSizeBox1.addItem(tr("23"));
	fontSizeBox1.addItem(tr("24"));
	fontSizeBox1.addItem(tr("25"));
	fontSizeBox1.addItem(tr("26"));
	fontSizeBox1.addItem(tr("27"));
	fontSizeBox1.addItem(tr("28"));
	fontSizeBox1.addItem(tr("29"));
	fontSizeBox1.addItem(tr("30"));
	fontSizeBox1.addItem(tr("31"));
	fontSizeBox1.addItem(tr("32"));
	fontSizeBox1.addItem(tr("33"));
	fontSizeBox1.addItem(tr("34"));
	fontSizeBox1.addItem(tr("35"));
	fontSizeBox1.addItem(tr("36"));
	fontSizeBox1.addItem(tr("37"));
	fontSizeBox1.addItem(tr("38"));
	fontSizeBox1.addItem(tr("39"));
	fontSizeBox1.addItem(tr("40"));
	fontSizeBox1.addItem(tr("41"));
	fontSizeBox1.addItem(tr("42"));
	fontSizeBox1.addItem(tr("43"));
	fontSizeBox1.addItem(tr("44"));
	fontSizeBox1.addItem(tr("45"));
	fontSizeBox1.addItem(tr("46"));
	fontSizeBox1.addItem(tr("47"));
	fontSizeBox1.addItem(tr("48"));
	fontSizeBox1.addItem(tr("49"));
	fontSizeBox1.addItem(tr("50"));
	fontSizeBox1.addItem(tr("51"));
	fontSizeBox1.addItem(tr("52"));
	fontSizeBox1.addItem(tr("53"));
	fontSizeBox1.addItem(tr("54"));
	fontSizeBox1.addItem(tr("55"));
	fontSizeBox1.addItem(tr("56"));
	fontSizeBox1.addItem(tr("57"));
	fontSizeBox1.addItem(tr("58"));
	fontSizeBox1.addItem(tr("59"));
	fontSizeBox1.addItem(tr("60"));
	fontSizeBox1.addItem(tr("61"));
	fontSizeBox1.addItem(tr("62"));
	fontSizeBox1.addItem(tr("63"));
	fontSizeBox1.addItem(tr("64"));
	fontSizeBox1.addItem(tr("65"));
	fontSizeBox1.addItem(tr("66"));
	fontSizeBox1.addItem(tr("67"));
	fontSizeBox1.addItem(tr("68"));
	fontSizeBox1.addItem(tr("69"));
	fontSizeBox1.addItem(tr("70"));
	fontSizeBox1.addItem(tr("71"));
	fontSizeBox1.addItem(tr("72"));
	fontSizeBox1.addItem(tr("73"));
	fontSizeBox1.addItem(tr("74"));
	fontSizeBox1.addItem(tr("75"));
	fontSizeBox1.addItem(tr("76"));
	fontSizeBox1.addItem(tr("77"));
	fontSizeBox1.addItem(tr("78"));
	fontSizeBox1.addItem(tr("79"));
	fontSizeBox1.addItem(tr("80"));
	fontSizeBox1.addItem(tr("81"));
	fontSizeBox1.addItem(tr("82"));
	fontSizeBox1.addItem(tr("83"));
	fontSizeBox1.addItem(tr("84"));
	fontSizeBox1.addItem(tr("85"));
	fontSizeBox1.addItem(tr("86"));
	fontSizeBox1.addItem(tr("87"));
	fontSizeBox1.addItem(tr("88"));
	fontSizeBox1.addItem(tr("89"));
	fontSizeBox1.addItem(tr("90"));
	fontSizeBox1.addItem(tr("91"));
	fontSizeBox1.addItem(tr("92"));
	fontSizeBox1.addItem(tr("93"));
	fontSizeBox1.addItem(tr("94"));
	fontSizeBox1.addItem(tr("95"));
	fontSizeBox1.addItem(tr("96"));
	fontSizeBox1.addItem(tr("97"));
	fontSizeBox1.addItem(tr("98"));
	fontSizeBox1.addItem(tr("99"));







	ui.toolBar->addWidget(&fontSizeBox1);
	connect(&fontSizeBox1,SIGNAL(activated(int)),this,SLOT(ComboCurrentActivated(int)));
	ui.toolBar->addAction(ui.actionFontBold);
	connect(ui.actionFontBold,SIGNAL(activated(int)),this,SLOT(ComboCurrentActivated(int)));
	ui.actionFontBold->setCheckable(true);
	ui.toolBar->addAction(ui.actionItalic);
	connect(ui.actionItalic,SIGNAL(activated(int)),this,SLOT(ComboCurrentActivated(int)));
	ui.actionItalic->setCheckable(true);
	ui.toolBar->addAction(ui.actionUnderline);
	connect(ui.actionUnderline,SIGNAL(activated(int)),this,SLOT(ComboCurrentActivated(int)));
	ui.actionUnderline->setCheckable(true);
	ui.menuFile->addSeparator();
	for (int i = 0; i < 1; ++i)
		ui.menuFile->addAction(recentFileActs[i]);
	

	scene=new QGScene(this);
	connect(scene,SIGNAL(mChangeFont()),this,SLOT(ChangeFontGraphicsFont()));
	view = new QGraphicsView(scene,ui.centralWidget);
	view->setGeometry(0,0,1600,1200);
	view->setSceneRect(-800,-600,1600,1200);
	view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	view->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
	view->setResizeAnchor(QGraphicsView::AnchorViewCenter);
	view->setScene(scene);
	ui.actionZoom_In->setVisible(false);
	ui.actionZoom_Out->setVisible(false);
	ui.actionAdd_GraphicsItem->setVisible(false);
	ui.actionDelete->setVisible(false);
	ui.actionExportImage->setVisible(false);
	ui.toolBar_2->hide();
}



void PLabel::LabelPreview(int m_row,int m_col)
{
	e_row=m_row;
	e_col=m_col;
	if(tableWidget)
	{
		scene->clear();
		view->setGeometry(0,0,tableWidget->width(),tableWidget->height());
		double w=(double)707/(double)e_col;
		double h=(double)1000/(double)e_row;
		www=w;hhh=h;
		scene->setRC(e_col,e_row);
		int h_down=(int)(h/tableWidget->columnCount());
        m_center=new QGraphicsRectItem(0);
		QPen pen;
		pen.setColor(Qt::darkBlue);
		m_root=scene->addRect(-w/2+1,-h/2+1,w-2,h-2,pen,m_backgroundColor);
		
		view->fitInView (QRectF(-(w*1.25)/2+1,-(h*1.25)/2+1,w*1.25-2,h*1.25-2) ,Qt::KeepAspectRatio );
		mdbprint_elementImagePos.clear();
		scene->mdbprint_elementImagePos.clear();
		float m_zvalue=0.001;
		m_zvalue_images=m_zvalue;
		for(tableWidget->idb_element_ImageInfo=tableWidget->mdb_element_ImageInfo.begin();tableWidget->idb_element_ImageInfo<tableWidget->mdb_element_ImageInfo.end();tableWidget->idb_element_ImageInfo++)
		{
			newprint_elementImagePos=new dbprint_elementImagePos;
 			newprint_elementImagePos->id=(*(tableWidget->idb_element_ImageInfo))->id;
			newprint_elementImagePos->tip=1;
			newprint_elementImagePos->m_x=(*(tableWidget->idb_element_ImageInfo))->m_x;
			newprint_elementImagePos->m_y=(*(tableWidget->idb_element_ImageInfo))->m_y;
			newprint_elementImagePos->m_data=(*(tableWidget->idb_element_ImageInfo))->m_data;
			newprint_elementImagePos->m_scale=(*(tableWidget->idb_element_ImageInfo))->m_scale;
			newprint_elementImagePos->m_scale_w=(*(tableWidget->idb_element_ImageInfo))->m_scale_w;

			scene->addInfoImage(newprint_elementImagePos->id,
								newprint_elementImagePos->m_x,
								newprint_elementImagePos->m_y,
								newprint_elementImagePos->m_data,
								newprint_elementImagePos->m_scale,
								newprint_elementImagePos->m_scale_w
								);

			lpix1=new QLab1PixmapItem;
			QPixmap pixmap( 20, 20 );
            pixmap.loadFromData(newprint_elementImagePos->m_data,"PNG");//tuka
			QRect r=pixmap.rect();
			double scale=newprint_elementImagePos->m_scale;
			double scale_w=newprint_elementImagePos->m_scale_w;

			lpix1->setPos(  -(double)w/(double)2+newprint_elementImagePos->m_x*w,
							-(double)h/(double)2+newprint_elementImagePos->m_y*h);

			pixmap=pixmap.scaled(pixmap.width()/scale_w,pixmap.height()/scale,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
			lpix1->setPixmap(pixmap);

			lpix1->SetId(newprint_elementImagePos->id);
			lpix1->setZValue(m_zvalue*newprint_elementImagePos->id);
			m_zvalue_images=m_zvalue*newprint_elementImagePos->id;
			scene->addItem(lpix1);
			scene->update();
			mdbprint_elementImagePos.push_back(newprint_elementImagePos);
		}


		max_image_count=scene->mdbprint_elementImagePos.count()+1;
		int r=tableWidget->currentRow();
		int io=0;
		double ax,ay;
		m_zvalue=1000;
			for(idbprint_elementPos=mdbprint_elementPos.begin();idbprint_elementPos<mdbprint_elementPos.end();idbprint_elementPos++)
			{	
				io=(*idbprint_elementPos)->id;
// 				if(tableWidget->item(r,io)->text()!="")
// 				{
					addItemScene((int)io,-(double)w/(double)2+(double)w*(*idbprint_elementPos)->m_x,
						-(double)h/(double)2+h*(*idbprint_elementPos)->m_y,
						tableWidget->item(r,io)->text(),
						//tableWidget->item(r,io)->font(),
						(*idbprint_elementPos)->m_graphic_Font,
						(*idbprint_elementPos)->m_color,
						m_zvalue,
						(*idbprint_elementPos)->m_rotate);
					if(io==0)
					{
						on_actionSendToBack_triggered();
					}
					m_zvalue++;
//				}
			}
		if(ui.actionShowBorder->isChecked())
		{
			scene->itemsShowGridBorderVisible();
		}
		else
		{
			scene->itemsHideGridBorder();

		}
		
	tableWidget->hide();
	ui.actionNew_2->setVisible(false);
	ui.actionAdd_Column->setVisible(false);
	ui.actionAdd_Records->setVisible(false);
	ui.actionClose->setVisible(false);
	ui.actionConcatenate->setVisible(false);
	ui.actionConcatenate_Rows->setVisible(false);
	ui.actionCopy->setVisible(false);
	ui.actionCut->setVisible(false);
	ui.actionDel->setVisible(false);
	ui.actionExpand->setVisible(false);
	ui.actionExpand_in_Rows->setVisible(false);
	ui.actionFind->setVisible(false);
	ui.actionFind_Next->setVisible(false);
	ui.actionFind_Previous->setVisible(false);
	ui.actionFont->setVisible(false);
//	ui.actionFontBold->setVisible(false);
//	ui.actionItalic->setVisible(false);
	ui.actionOpen->setVisible(false);
	ui.actionPaste->setVisible(false);
	ui.actionRemove_Columns->setVisible(false);
	ui.actionRemove_Empty_Rows->setVisible(false);
	ui.actionRemove_Records->setVisible(false);
	ui.actionSave->setVisible(false);
	ui.actionSave_As->setVisible(false);
//	ui.actionUnderline->setVisible(false);
	ui.actionUndo->setVisible(false);
	ui.mainToolBar->setVisible(false);
//	ui.toolBar->setVisible(false);
	recentFileActs[0]->setVisible(false);
	ui.actionZoom_In->setVisible(true);
	ui.actionZoom_Out->setVisible(true);
	ui.actionAdd_GraphicsItem->setVisible(true);
	ui.actionDelete->setVisible(true);
	ui.actionExportImage->setVisible(true);

	ui.toolBar_2->show();

        scene->InitilizeItems();
        m_vectorPrintElementPos=mdbprint_elementPos;

	}
}

void PLabel::showTable()
{
	if(tableWidget)
	{
		//tuka
		if(scene->m_stat_update)
		{
			for(idbprint_elementPos=mdbprint_elementPos.begin();idbprint_elementPos<mdbprint_elementPos.end();idbprint_elementPos++)
			{
			(*idbprint_elementPos)->m_x=scene->GetInfoX((*idbprint_elementPos)->id);
			(*idbprint_elementPos)->m_y=scene->GetInfoY((*idbprint_elementPos)->id);
			(*idbprint_elementPos)->m_color=scene->getColor((*idbprint_elementPos)->id);	
			(*idbprint_elementPos)->m_graphic_Font=scene->getGraphicFont((*idbprint_elementPos)->id);
			(*idbprint_elementPos)->m_rotate=scene->GetRotate((*idbprint_elementPos)->id);
		}
			scene->m_stat_update=false;
		}
		ui.actionNew_2->setVisible(true);
		ui.actionAdd_Column->setVisible(true);
		ui.actionAdd_Records->setVisible(true);	
		ui.actionClose->setVisible(true);	
		ui.actionConcatenate->setVisible(true);	
		ui.actionConcatenate_Rows->setVisible(true);	
		ui.actionCopy->setVisible(true);
		ui.actionCut->setVisible(true);
		ui.actionDel->setVisible(true);
		ui.actionExpand->setVisible(true);
		ui.actionExpand_in_Rows->setVisible(true);
		ui.actionFind->setVisible(true);
		ui.actionFind_Next->setVisible(true);
		ui.actionFind_Previous->setVisible(true);
		ui.actionFont->setVisible(true);
		ui.actionFontBold->setVisible(true);
		ui.actionItalic->setVisible(true);
		ui.actionOpen->setVisible(true);
		ui.actionPaste->setVisible(true);
		ui.actionRemove_Columns->setVisible(true);
		ui.actionRemove_Empty_Rows->setVisible(true);
		ui.actionRemove_Records->setVisible(true);
		ui.actionSave->setVisible(true);
		ui.actionSave_As->setVisible(true);
		ui.actionUnderline->setVisible(true);
		ui.actionUndo->setVisible(true);
		ui.mainToolBar->setVisible(true);
		ui.toolBar->setVisible(true);
		ui.actionZoom_In->setVisible(false);
		ui.actionZoom_Out->setVisible(false);
		ui.actionAdd_GraphicsItem->setVisible(false);
		ui.actionDelete->setVisible(false);
		ui.actionExportImage->setVisible(false);
		ui.toolBar_2->hide();
		recentFileActs[0]->setVisible(true);	
		for(idbprint_elementImagePos=mdbprint_elementImagePos.begin();idbprint_elementImagePos<mdbprint_elementImagePos.end();idbprint_elementImagePos++)
		{
			(*idbprint_elementImagePos)->m_x=scene->GetInfoImageX((*idbprint_elementImagePos)->id);
			(*idbprint_elementImagePos)->m_y=scene->GetInfoImageY((*idbprint_elementImagePos)->id);
		}
		mdbprint_elementImagePos.clear();
		for(scene->idbprint_elementImagePos=scene->mdbprint_elementImagePos.begin();scene->idbprint_elementImagePos<scene->mdbprint_elementImagePos.end();scene->idbprint_elementImagePos++)
		{
			newprint_elementImagePos=new dbprint_elementImagePos;
			newprint_elementImagePos->id=(*(scene->idbprint_elementImagePos))->id;
			newprint_elementImagePos->tip=1;
			newprint_elementImagePos->m_x=(*(scene->idbprint_elementImagePos))->m_x;
			newprint_elementImagePos->m_y=(*(scene->idbprint_elementImagePos))->m_y;
			newprint_elementImagePos->m_data=(*(scene->idbprint_elementImagePos))->m_data;
			newprint_elementImagePos->m_scale=(*(scene->idbprint_elementImagePos))->m_scale;
			newprint_elementImagePos->m_scale_w=(*(scene->idbprint_elementImagePos))->m_scale_w;
			mdbprint_elementImagePos.push_back(newprint_elementImagePos);
		}

		tableWidget->show();

		scene->mdbprint_elementImagePos.clear();
		for(tableWidget->idb_element_ImageInfo=tableWidget->mdb_element_ImageInfo.begin();tableWidget->idb_element_ImageInfo<tableWidget->mdb_element_ImageInfo.end();tableWidget->idb_element_ImageInfo++)
		{
			scene->addInfoImage(newprint_elementImagePos->id,
				newprint_elementImagePos->m_x,
				newprint_elementImagePos->m_y,
				newprint_elementImagePos->m_data,
				newprint_elementImagePos->m_scale,
				newprint_elementImagePos->m_scale_w
				);
		}
		scene->clear();
		tableWidget->mdb_element_ImageInfo.clear();
		for(idbprint_elementImagePos=mdbprint_elementImagePos.begin();idbprint_elementImagePos<mdbprint_elementImagePos.end();idbprint_elementImagePos++)
		{
			tableWidget->addInfoImage((*idbprint_elementImagePos)->id,
				(*idbprint_elementImagePos)->m_x,
				(*idbprint_elementImagePos)->m_y,
				(*idbprint_elementImagePos)->m_data,
				(*idbprint_elementImagePos)->m_scale,
				(*idbprint_elementImagePos)->m_scale_w
				);
		}
	}
}



void PLabel::addItemScene(int id,double bx,double by,QString m_info,QFont m1_font, QColor m_color,qreal m_zvalue,double m_rotate)
{
	lpic1=new QLab1Picture(0,scene);
	QPointF m_initPos;
	lpic1->setFont(m1_font);
	lpic1->setDefaultTextColor(m_color);
	lpic1->setPlainText(m_info);
	lpic1->Set_m_Text(m_info);
	lpic1->SetId(id);

	QRectF r=lpic1->boundingRect();
	double x=(double)r.height();
	m_initPos=QPointF(bx,by-x/2);
	lpic1->setPos(m_initPos);
// 	if(!id)
// 	{
// 		lpic1->setTransform(QTransform().translate(0, 0).rotate((qreal)m_rotate).translate(0, 0));
// 	}
// 	else
// 	{
		lpic1->setTransform(QTransform().translate(0, x/2).rotate((qreal)m_rotate).translate(0, -x/2));
//	}
	lpic1->setZValue(m_zvalue);
	scene->addItem(lpic1);
	backToFront();
	scene->addInfo(id,m_initPos.rx(),m_initPos.ry(),m_color,m1_font,m_rotate);
	scene->clearSelection();
	scene->update();
}

void PLabel::addPixItemScene(int bx,int by,QString m_info)
{
	lpix1=new QLab1PixmapItem(0,scene);
	QPointF m_initPos;
	m_initPos=QPointF(bx,by);
	scene->addItem(lpix1);	
	lpix1->setPos(m_initPos);
	QPixmap pixmap( 20, 20 );
	pixmap.fill( Qt::lightGray );
	lpix1->setPixmap(pixmap);
	scene->addItem(lpix1);
	scene->clearSelection();
	scene->update();
}


void PLabel::openRecentFile()
{
	QAction *action = qobject_cast<QAction *>(sender());
	if (action)
		loadFile(action->data().toString());
}


void PLabel::loadFile(const QString &fileName)
{
showDataFromFileExtended(fileName);
e_col=tableWidget->m_colPreview;
e_row=tableWidget->m_rowPreview;
setWindowTitle("Label Software-"+tableWidget->getFileName());
}



void PLabel::ComboCurrentActivated(int aIndex)
{
if(!tableWidget)
	return;
	if(tableWidget->isVisible())
	{
		m_Font=fontbox1.currentFont();
		bool ok;
		m_Font.setPointSize(fontSizeBox1.currentText().toInt(&ok,10));
		ui.actionFontBold->isChecked()?m_Font.setBold(true):m_Font.setBold(false);
		ui.actionItalic->isChecked()?m_Font.setItalic(true):m_Font.setItalic(false);
		ui.actionUnderline->isChecked()?m_Font.setUnderline(true):m_Font.setUnderline(false);
		p->setAFont(m_Font);

		if(tableWidget)
		{
		int m1_arow=0;
		int m1_brow=0;
		int m1_acol=0;
		int m1_bcol=0;
		QList<QTableWidgetSelectionRange> mx;
		QList<QTableWidgetSelectionRange>::iterator ix;
		mx=tableWidget->selectedRanges();
		if(mx.count()>0)
		{
		ix=mx.begin();
		m1_arow=(*ix).topRow();
		m1_brow=(*ix).bottomRow();
		m1_acol=(*ix).leftColumn();
		m1_bcol=(*ix).rightColumn();
		setUpdatesEnabled(false);
		for(int irow=m1_arow;irow<m1_brow+1;irow++)
		{
		for(int icol=m1_acol;icol<m1_bcol+1;icol++)
		{
		tableWidget->item(irow,icol)->setFont(m_Font);
		}
		}
		setUpdatesEnabled(true);
		}
		}
	}
	else
	{
		bool ok;
		QFont mg_Font=fontbox1.currentFont();
		mg_Font.setPointSize(fontSizeBox1.currentText().toInt(&ok,10));
		ui.actionFontBold->isChecked()?mg_Font.setBold(true):mg_Font.setBold(false);
		ui.actionItalic->isChecked()?mg_Font.setItalic(true):mg_Font.setItalic(false);
		ui.actionUnderline->isChecked()?mg_Font.setUnderline(true):mg_Font.setUnderline(false);
		scene->setTextFont(mg_Font);
	}
}
void PLabel::ComboCurrentFontChanged(const QFont & afont)
{
 if(tableWidget)
 {
	if(tableWidget->isVisible())
	{
		m_Font=afont;
		p->setAFont(m_Font);
		statusFontWrite=false;
	}
	else
	{
		scene->setTextFont(afont);
	}
 }
}

void PLabel::on_actionNavigate_triggered()
{
dock->show();
}

void PLabel::on_actionExit_triggered()
{

	this->close();
}
void PLabel::showDataFromFile()
{
	if(tableWidget)
	{
		if(saveFlag)
		{
			int ret = QMessageBox::warning(this, tr("Label Software"),
				tr("The document has been modified.\n"
				"Do you want to save your changes?"),
				QMessageBox::Save | QMessageBox::Discard,
				QMessageBox::Save);
			switch(ret)
			{
			case QMessageBox::Save:on_actionSave_triggered();break; 
			}
		}
		delete tableWidget;
		tableWidget=NULL;
	}
		tableWidget = new QSTableWidget(ui.centralWidget);
		connect(this,SIGNAL(setProgressS(int,int)),this,SLOT(tableWidgetcellProgresBar(int,int)));
		connect(tableWidget,SIGNAL(currentCellChanged(int,int,int,int)),this,SLOT(tableWidgetcellPressed(int,int,int,int)));
		tableWidget->setGeometry(ui.centralWidget->rect());
		tableWidget->setRowCount(65636);
		tableWidget->setItemDelegate(p);

		setUpdatesEnabled(false);
		tableWidget->showDBD();
		m_backgroundColor=tableWidget->cl_backGroundColor;
		connect(tableWidget,SIGNAL(sendMouseRightClick1(QPoint)),this,SLOT(createPopupTableWidgetMenu(QPoint)));

		setUpdatesEnabled(true);
		connect(reinterpret_cast<const QObject*>(tableWidget),SIGNAL(cellChanged(int,int)),this,SLOT(tableWidgetcellChanged(int,int)));
		connect(tableWidget,SIGNAL(cellActivated(int,int)),this,SLOT(tableWidgetcellActivated(int,int)));
		tableWidget->setCurrentCell(0,0);
		//create empty fields position 
		mdbprint_elementPos.clear();
		QStringList mlistXY=tableWidget->m_xyInfo.split(",");
		for(int io=0;io<tableWidget->columnCount()-1;io++)
		{
			newprint_elementPos=new dbprint_elementPos;
			newprint_elementPos->id=io;
			newprint_elementPos->tip=0;
// 			newprint_elementPos->m_x=((double)1/20)/(double)1;;	
// 			newprint_elementPos->m_y=((double)((io)*1/(double)tableWidget->columnCount())+(double)(1/(double)tableWidget->columnCount()))/(double)1;;
			newprint_elementPos->m_x=mlistXY.at(2*io).toDouble();	
 			newprint_elementPos->m_y=mlistXY.at(2*io+1).toDouble();
			newprint_elementPos->m_color=tableWidget->getColor(io);
			newprint_elementPos->m_graphic_Font=tableWidget->getGraphicFont(io);
			newprint_elementPos->m_rotate=tableWidget->getRotate(io);
			mdbprint_elementPos.push_back(newprint_elementPos);
		}

		e_col=tableWidget->m_colPreview;
		e_row=tableWidget->m_rowPreview;
		m_left->setValue(e_col,e_row);

		m_vectorPrintElementPos=mdbprint_elementPos;
saveFlag=0;
}

void PLabel::SaveDataFromFile()
{
	if(tableWidget)
	{
		saveFlag=0;
		QString temp="";
		for(idbprint_elementPos=mdbprint_elementPos.begin();idbprint_elementPos<mdbprint_elementPos.end();idbprint_elementPos++)
		{
			temp=temp+QString::number(((*idbprint_elementPos)->m_x),'g',10)+",";
			temp=temp+QString::number(((*idbprint_elementPos)->m_y),'g',10)+",";
		}
		tableWidget->m_xy_info1=temp;
		tableWidget->m_colPreview=e_col;
		tableWidget->m_rowPreview=e_row;
		tableWidget->cl_backGroundColor=m_backgroundColor;

		tableWidget->mdb_element_ImageInfo.clear();
		for(idbprint_elementImagePos=mdbprint_elementImagePos.begin();idbprint_elementImagePos<mdbprint_elementImagePos.end();idbprint_elementImagePos++)
		{
			tableWidget->addInfoImage((*idbprint_elementImagePos)->id,
				(*idbprint_elementImagePos)->m_x,
				(*idbprint_elementImagePos)->m_y,
				(*idbprint_elementImagePos)->m_data,
				(*idbprint_elementImagePos)->m_scale,
				(*idbprint_elementImagePos)->m_scale_w
				);
		}

		tableWidget->CopyTableToDBD();
		int ioi=0;
		for(idbprint_elementPos=mdbprint_elementPos.begin();idbprint_elementPos<mdbprint_elementPos.end();idbprint_elementPos++)
		{
			tableWidget->setColor(ioi,(*idbprint_elementPos)->m_color);
			tableWidget->setGraphicFont(ioi,(*idbprint_elementPos)->m_graphic_Font);
			tableWidget->setRotate(ioi,(*idbprint_elementPos)->m_rotate);

			ioi++;
		}
		tableWidget->saveRecordsToFile();

	}
}

void PLabel::SaveAsDataFromFile()
{
	if(tableWidget)
	{
		saveFlag=0;
		QString temp="";
		for(idbprint_elementPos=mdbprint_elementPos.begin();idbprint_elementPos<mdbprint_elementPos.end();idbprint_elementPos++)
		{
			temp=temp+QString::number(((*idbprint_elementPos)->m_x),'g',10)+",";
			temp=temp+QString::number(((*idbprint_elementPos)->m_y),'g',10)+",";
		}
		tableWidget->m_xy_info1=temp;
		tableWidget->m_colPreview=e_col;
		tableWidget->m_rowPreview=e_row;
		tableWidget->cl_backGroundColor=m_backgroundColor;

		tableWidget->mdb_element_ImageInfo.clear();
		for(idbprint_elementImagePos=mdbprint_elementImagePos.begin();idbprint_elementImagePos<mdbprint_elementImagePos.end();idbprint_elementImagePos++)
		{
			tableWidget->addInfoImage((*idbprint_elementImagePos)->id,
				(*idbprint_elementImagePos)->m_x,
				(*idbprint_elementImagePos)->m_y,
				(*idbprint_elementImagePos)->m_data,
				(*idbprint_elementImagePos)->m_scale,
				(*idbprint_elementImagePos)->m_scale_w
				);
		}

		tableWidget->CopySaveAsTableToDBD();
		int ioi=0;
		for(idbprint_elementPos=mdbprint_elementPos.begin();idbprint_elementPos<mdbprint_elementPos.end();idbprint_elementPos++)
		{
			tableWidget->setColor(ioi,(*idbprint_elementPos)->m_color);
			tableWidget->setGraphicFont(ioi,(*idbprint_elementPos)->m_graphic_Font);
			tableWidget->setRotate(ioi,(*idbprint_elementPos)->m_rotate);

			ioi++;
		}

		tableWidget->saveAsRecordsToFile();
	}
}

void PLabel::PressedItem(int x,int y)
{
	int ax,ay;
	ay=0;
	ax=ay++;
}
void PLabel::resizeEvent(QResizeEvent * event)
{
	if(tableWidget)
	{
		tableWidget->setGeometry(ui.centralWidget->rect());
	}
}

void PLabel::filePrintPreview(int x_row,int x_col)
{
	e_col=x_col;
	e_row=x_row;
	if(tableWidget)
	{
	QPrinter printer(QPrinter::HighResolution);
	printer.setPageMargins(m_aleft,m_atop,m_aright,m_abottom,QPrinter::Millimeter);
	QPrintPreviewDialog preview(&printer, this);
	preview.setWindowFlags( Qt::Window);
	connect(&preview, SIGNAL(paintRequested(QPrinter *)), SLOT(printPreview(QPrinter *)));
	preview.resize(width(),height());
	preview.exec();
	}
}





void PLabel::printPreview(QPrinter *printer)
{
	EAN13 code("1208964450087");
	mdbprint_element.clear();
	for(int row_i=0;row_i<tableWidget->rowCount();row_i++)
	{
     for(int i=0;i<tableWidget->item(row_i,tableWidget->columnCount()-1)->text().toInt(0,10);i++)
	  {
		for(int col_i=0;col_i<tableWidget->columnCount();col_i++)
		{
		newprint_element=new dbprint_element;
		newprint_element->m_element_font=tableWidget->item(row_i,col_i)->font();	
		newprint_element->m_element=tableWidget->item(row_i,col_i)->text();	
		mdbprint_element.push_back(newprint_element);
		}
	  }
	}
	int maxpage=(int)mdbprint_element.count()/(e_col*e_row*tableWidget->columnCount()); 
	float x=(float)mdbprint_element.count()/(float)(e_col*e_row*tableWidget->columnCount());
	if((x-maxpage)!=0)
	{
		maxpage++;
	}

	QPainter painter( printer );
		painter.setPen( Qt::black );
		int h_down;
		x=0;
		int y=0;
		int w=printer->pageRect().width()/e_col;
		int h=printer->pageRect().height()/e_row;
		double gwscale=(double)printer->pageRect().width()/(double)707;
		double ghscale=(double)printer->pageRect().width()/(double)1000;

		h_down=h/tableWidget->columnCount();				
		
			int io=0;
			double w1=(double)707/(double)e_col;
			double h1=(double)1000/(double)e_row;
// 			double w1=(double)860/(double)e_col;
// 			double h1=((double)h/(double)w)*w1;
			ghscale=gwscale;

//		mdbprint_elementPos=m_vectorPrintElementPos;
 		if(scene->m_stat_update)
 		{
 			for(idbprint_elementPos=mdbprint_elementPos.begin();idbprint_elementPos<mdbprint_elementPos.end();idbprint_elementPos++)
 			{
//  				if(scene->GetInfoX((*idbprint_elementPos)->id)<2)
// 				{
 					(*idbprint_elementPos)->m_x=scene->GetInfoX((*idbprint_elementPos)->id);
// 				}
// 				else
// 				{
// 					(*idbprint_elementPos)->m_x=0;
// 				}
// 				
// 				if(scene->GetInfoY((*idbprint_elementPos)->id)<2)
// 				{
  					(*idbprint_elementPos)->m_y=scene->GetInfoY((*idbprint_elementPos)->id);
// 				}
// 				else
// 				{
// 					(*idbprint_elementPos)->m_y=0;
// 				}
				
				(*idbprint_elementPos)->m_graphic_Font=scene->getGraphicFont((*idbprint_elementPos)->id);
				(*idbprint_elementPos)->m_rotate=scene->GetRotate((*idbprint_elementPos)->id);
				(*idbprint_elementPos)->m_color=scene->getColor((*idbprint_elementPos)->id);
				(*idbprint_elementPos)->m_width=scene->getWidth((*idbprint_elementPos)->id);
				(*idbprint_elementPos)->m_height=scene->getHeight((*idbprint_elementPos)->id);
 			}
			for(idbprint_elementImagePos=mdbprint_elementImagePos.begin();idbprint_elementImagePos<mdbprint_elementImagePos.end();idbprint_elementImagePos++)
			{
				(*idbprint_elementImagePos)->m_x=scene->GetInfoImageX((*idbprint_elementImagePos)->id);
				(*idbprint_elementImagePos)->m_y=scene->GetInfoImageY((*idbprint_elementImagePos)->id);
				(*idbprint_elementImagePos)->m_scale=scene->getScale((*idbprint_elementImagePos)->id);
				(*idbprint_elementImagePos)->m_scale_w=scene->getScaleW((*idbprint_elementImagePos)->id);
			}

		scene->m_stat_update=false;
		}
		for( int page=0; page<maxpage; page++)
		{
			for(int c=0;c<e_col;c++)
			{
				for(int r=0;r<e_row;r++)
				{
				painter.drawRect((x+c)*w,(y+r)*h,w,h);	
					painter.fillRect((x+c)*w+1,(y+r)*h+1,w-2,h-2,m_backgroundColor);
				QPixmap imag;
				scene->idbprint_elementImagePos=scene->mdbprint_elementImagePos.begin();
				for(scene->idbprint_elementImagePos=scene->mdbprint_elementImagePos.begin();scene->idbprint_elementImagePos<scene->mdbprint_elementImagePos.end();scene->idbprint_elementImagePos++)
				{
									
                    imag.loadFromData((*scene->idbprint_elementImagePos)->m_data,"PNG",Qt::AutoColor);
// 					QRect rect =imag.rect();
// 					imag=imag.scaled(rect.width()*gwscale/((*scene->idbprint_elementImagePos)->m_scale_w)
// 						,rect.height()*ghscale/((*scene->idbprint_elementImagePos)->m_scale)
// 						,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
// 					painter.drawPixmap((x+c)*w+((*scene->idbprint_elementImagePos)->m_x)*w,(y+r)*h+((*scene->idbprint_elementImagePos)->m_y)*h-imag.rect().height()*ghscale/2,imag.rect().width()*gwscale,imag.rect().height()*ghscale,imag);
					painter.drawPixmap(
						(x+c)*w+((*scene->idbprint_elementImagePos)->m_x)*w,
						(y+r)*h+((*scene->idbprint_elementImagePos)->m_y)*h,//-imag.rect().height()*ghscale/2,
						imag.rect().width()*gwscale/((*scene->idbprint_elementImagePos)->m_scale_w),
						imag.rect().height()*ghscale/((*scene->idbprint_elementImagePos)->m_scale),
						imag
						);

				}
				idbprint_elementPos=mdbprint_elementPos.begin();
					for(int io=1;io<tableWidget->columnCount();io++)
					{
						if((((page)*(e_col*e_row)+(r*e_col+c))*tableWidget->columnCount()+io-1)<mdbprint_element.count())
						{
// 							if(io==1)
// 							{
// 								if(mdbprint_element.at(((page)*(e_col*e_row)+(r*e_col+c))*tableWidget->columnCount()+io-1)->m_element!="")
// 								{
// 								code.setBarcode(mdbprint_element.at(((page)*(e_col*e_row)+(r*e_col+c))*tableWidget->columnCount()+io-1)->m_element);
// 								double z=scene->getWidth((*idbprint_elementPos)->id)*w;
// 								double zh=scene->getHeight((*idbprint_elementPos)->id)*h;
// 								painter.save();
// 								painter.translate((x+c)*w+((*idbprint_elementPos)->m_x)*w,
// 									(y+r)*h+((*idbprint_elementPos)->m_y)*h);
// 								painter.rotate(scene->GetRotate((*idbprint_elementPos)->id));
// 								painter.translate(0,-zh/2);
// 							
// 								if(z>zh)
// 								{
// 									code.draw(QRectF(0	/*QRectF((x+c)*w+((*idbprint_elementPos)->m_x)*w*/,
// 										0/*(y+r)*h+((*idbprint_elementPos)->m_y)*h-zh/2*/,
// 										z, 
// 										z*10.93/37.29),
// 										painter,false);
// 								}
// 								else
// 								{
// 									code.draw(QRectF(0/*QRectF((x+c)*w+((*idbprint_elementPos)->m_x)*w*/,
// 										0	/*(y+r)*h+((*idbprint_elementPos)->m_y)*h-zh/2*/,
// 										zh*37.29/10.93, 
// 										zh),
// 										painter,false);
// 								}
// 								painter.restore();
// 							}
// 							} 
// 							else
// 							{
								painter.setFont((*idbprint_elementPos)->m_graphic_Font);
								int z=scene->getHeight((*idbprint_elementPos)->id)*h;
								int zw=scene->getWidth((*idbprint_elementPos)->id)*w;
								painter.setPen((*idbprint_elementPos)->m_color);
								painter.save();
								painter.translate((x+c)*w+((*idbprint_elementPos)->m_x)*w,
									(y+r)*h+((*idbprint_elementPos)->m_y)*h);
								painter.rotate(scene->GetRotate((*idbprint_elementPos)->id));
								painter.drawText(
								(double)z/(double)6,
								(double)z/(double)6,
								mdbprint_element.at(((page)*(e_col*e_row)+(r*e_col+c))*tableWidget->columnCount()+io-1)->m_element
								);
								painter.rotate(-scene->GetRotate((*idbprint_elementPos)->id));
								painter.restore();
								painter.setPen(Qt::black);
// 							}
							idbprint_elementPos++;							
						}
					}
					//////
					if(!rglprd)
					{
						painter.setPen(Qt::red);
						painter.save();
						painter.translate((qreal)((x+c)*w),(qreal)((y+r)*h));
						painter.rotate(45);
						QFont tempFont=m_Font;
						int ps=m_Font.pointSize()+2;
						ps=14;
						m_Font.setPointSize(ps);
						painter.setFont(m_Font);
						painter.drawText(10,10,QString(ext_srg2)+
							QString(ext_srg3)+QString(ext_srg4)+
							QString(ext_srg5)+QString(ext_srg6)+
							QString(ext_srg2));
						painter.setPen( Qt::black );
						m_Font=tempFont;
						painter.setFont(m_Font);
						painter.restore();
						painter.setPen( Qt::black );

					}
					////////////
				}
			}
			if( page < maxpage-1 )
				printer->newPage();
		}
		io=0;
}



void PLabel::filePrint(int x_row,int x_col)
{
}

void PLabel::on_actionOpen_triggered()
{
			showDataFromFile();
			setWindowTitle("Label Software"+tableWidget->getFileName());
			if(tableWidget->getFileName()!="")
			{
				recentFileActs[0]->setText(tableWidget->getFileName());
				recentFileActs[0]->setData(tableWidget->getFileName());
				recentFileActs[0]->setVisible(true);
			}
			statusBar()->showMessage(tr("Open File"));
}

void PLabel::on_actionSave_triggered()
{
saveFlag=0;
if(tableWidget)
{
statusBar()->showMessage(tr("Save File"));

if(tableWidget->fExistFileName())
{
 SaveDataFromFile();
}
else
{
 SaveAsDataFromFile();
}
statusBar()->showMessage(tr("File is saved"));
if(tableWidget->getFileName()!="")
 {
	setWindowTitle("Label Software"+tableWidget->getFileName());
 }
}
}

void PLabel::on_actionSave_As_triggered()
{
saveFlag=0;
if(tableWidget)
{

SaveAsDataFromFile();
statusBar()->showMessage(tr("Save As..."));
setWindowTitle("Label Software"+tableWidget->getFileName());
if(tableWidget->getFileName()!="")
{
	recentFileActs[0]->setText(tableWidget->getFileName());
	recentFileActs[0]->setData(tableWidget->getFileName());
	recentFileActs[0]->setVisible(true);
}
}
}

void PLabel::on_actionClose_triggered()
{
	setUpdatesEnabled(false);
	if(tableWidget)
	{
		disconnect(reinterpret_cast<const QObject*>(tableWidget),SIGNAL(cellChanged(int,int)),this,SLOT(tableWidgetcellChanged(int,int)));
		if(saveFlag)
	{
			int ret = QMessageBox::warning(this, tr("Label Software"),
				tr("The document has been modified.\n"
				"Do you want to save your changes?"),
				QMessageBox::Save | QMessageBox::Discard,
				QMessageBox::Save);
			switch(ret)
			{
			case QMessageBox::Save:on_actionSave_triggered();break; 
			}

	}
	delete tableWidget;
		tableWidget=NULL;
		setWindowTitle("Label Software");
		statusBar()->showMessage(tr("Close File"));
		connect(reinterpret_cast<const QObject*>(tableWidget),SIGNAL(cellChanged(int,int)),this,SLOT(tableWidgetcellChanged(int,int)));
	}
	setUpdatesEnabled(true);
	saveFlag=0;
}

void PLabel::on_actionNew_triggered()
{
}

void PLabel::on_actionNew_2_triggered()
{
	if(tableWidget)
	{
		if(saveFlag)
		{
			int ret = QMessageBox::warning(this, tr("Label Software"),
				tr("The document has been modified.\n"
				"Do you want to save your changes?"),
				QMessageBox::Save | QMessageBox::Discard,
				QMessageBox::Save);
			switch(ret)
			{
			case QMessageBox::Save:on_actionSave_triggered();break; 
			}
		}
		delete tableWidget;
		tableWidget=NULL;
	}
	m_Font=m_Font_default;
	tableWidget = new QSTableWidget(ui.centralWidget);
	connect(reinterpret_cast<const QObject*>(tableWidget),SIGNAL(cellChanged(int,int)),this,SLOT(tableWidgetcellChanged(int,int)));
 	connect(tableWidget,SIGNAL(sendMouseRightClick1(QPoint)),this,SLOT(createPopupTableWidgetMenu(QPoint)));
	connect(tableWidget,SIGNAL(currentCellChanged(int,int,int,int)),this,SLOT(tableWidgetcellPressed(int,int,int,int)));

	tableWidget->setItemDelegate(p); 
	tableWidget->setGeometry(ui.centralWidget->rect());
	tableWidget->setRowCount(65636);
	tableWidget->setColumnCount(12);
	tableWidget->setRowCount(1);
	tableWidget->setRowHeight(0,18);




	tableWidget->setFont(m_Font);
	QString m_empty="";
	for(int i=0;i<12;i++)
	{
		if(i==0)
		{
		tableWidget->setItem(0, i,new QTableWidgetItem(""));
		tableWidget->item(0,i)->setFont(m_Font);
		}
		else
		{
			tableWidget->setItem(0, i,new QTableWidgetItem(m_empty));
			tableWidget->item(0,i)->setFont(m_Font);
		}
	}
//	tableWidget->setItem(0, 0,new QTableWidgetItem("0000000000000"));
	tableWidget->setItem(0, 0,new QTableWidgetItem(""));

	tableWidget->setItem(0, 12,new QTableWidgetItem("2"));
	tableWidget->setCurrentCell(0,0);
	setWindowTitle("Label Software-New File");

	statusBar()->showMessage(tr("Create New File"));
	tableWidget->show();
	//create empty fields position 
	mdbprint_elementPos.clear();
	m_backgroundColor=Qt::white;
	for(int io=0;io<tableWidget->columnCount()-1;io++)
	{
		newprint_elementPos=new dbprint_elementPos;
		newprint_elementPos->id=io;
		newprint_elementPos->tip=0;
		newprint_elementPos->m_x=((double)1/20)/(double)1;;	
		newprint_elementPos->m_y=((double)((io)*1/(double)tableWidget->columnCount())+(double)(1/(double)tableWidget->columnCount()))/(double)1;;
		newprint_elementPos->m_rotate=0.0f;
		mdbprint_elementPos.push_back(newprint_elementPos);
	}
	m_vectorPrintElementPos=mdbprint_elementPos;

	saveFlag=0;
}

void PLabel::removeRowSTableWidget()
{
on_actionRemove_Records_triggered();
}


void PLabel::insertRowSTableWidget()
{
	if(tableWidget)
	{
		tableWidget->save_to_undo();
		tableWidget->insertRow(tableWidget->rowCount()); 
		tableWidget->setRowHeight(tableWidget->rowCount()-1,18);
		QString m_empty="";
		for(int i=0;i<tableWidget->columnCount()-1;i++)
		{
			if(i==0)
			{
				tableWidget->setItem(tableWidget->rowCount()-1, i,new QTableWidgetItem(""));
				tableWidget->item(tableWidget->rowCount()-1,i)->setFont(m_Font);
			}
			else
			{
				tableWidget->setItem(tableWidget->rowCount()-1, i,new QTableWidgetItem(m_empty));
				tableWidget->item(tableWidget->rowCount()-1,i)->setFont(m_Font);
			}
		}
		tableWidget->setItem(tableWidget->rowCount()-1, tableWidget->columnCount()-1,new QTableWidgetItem("1"));
		tableWidget->setCurrentCell(tableWidget->rowCount()-1,0);
	}
}


void PLabel::on_actionFont_triggered()
{
	if(tableWidget->isVisible())
	{
	bool ok;
		if(tableWidget)
		{
			int m1_arow=0;
			int m1_brow=0;
			int m1_acol=0;
			int m1_bcol=0;
			QList<QTableWidgetSelectionRange> mx;
			QList<QTableWidgetSelectionRange>::iterator ix;
			mx=tableWidget->selectedRanges();
		if(mx.count()>0)
		{
			ix=mx.begin();
			m1_arow=(*ix).topRow();
			m1_brow=(*ix).bottomRow();
			m1_acol=(*ix).leftColumn();
			m1_bcol=(*ix).rightColumn();
			QFont c_Font=tableWidget->item(m1_arow,m1_acol)->font();
				QFont font = QFontDialog::getFont(&ok,c_Font,this);
				if (ok) {
				m_Font=font;
				setUpdatesEnabled(false);
				for(int irow=m1_arow;irow<m1_brow+1;irow++)
				{
					for(int icol=m1_acol;icol<m1_bcol+1;icol++)
					{
						tableWidget->item(irow,icol)->setFont(m_Font);
					}
				}
				setUpdatesEnabled(true);
				}
		}
		}
	}
	else
	{
		int uu=0;
	}
}

void PLabel::on_actionCopy_triggered()
{
if(tableWidget)
 {
	 tableWidget->save_to_undo();
	 if(tableWidget->rowCount()>0)
	 {
	 disconnect(reinterpret_cast<const QObject*>(tableWidget),SIGNAL(cellChanged(int,int)),this,SLOT(tableWidgetcellChanged(int,int)));
	 m_copyedString="";

	 QList<QTableWidgetSelectionRange> mx;
	 QList<QTableWidgetSelectionRange>::iterator ix;
	 mx=tableWidget->selectedRanges();
	 if(mx.count()>0)
	 {
	 ix=mx.begin();
	 m_arow=(*ix).topRow();
	 m_brow=(*ix).bottomRow();
	 m_acol=(*ix).leftColumn();
	 m_bcol=(*ix).rightColumn();

		setUpdatesEnabled(false);	
		for(int c_row=m_arow;c_row<m_brow+1;c_row++)
		{
			QStringList c;
			c.clear();
			for(int c_col=m_acol;c_col<m_bcol+1;c_col++)
			{
				QString temp = tableWidget->item(c_row,c_col)->text().trimmed();
				if(temp.contains('\n'))
				{
					int stop = 0;
				}
				c << temp;
			}
			m_copyedString=m_copyedString+c.join("\t");
			c.clear();
			m_copyedString=m_copyedString+"\n";
		}
	    setUpdatesEnabled(true);

		QClipboard *clipboard = QApplication::clipboard();
		clipboard->setText(m_copyedString);
	 }
	 }
	 
	 statusBar()->showMessage(tr("Finished"));
	 connect(reinterpret_cast<const QObject*>(tableWidget),SIGNAL(cellChanged(int,int)),this,SLOT(tableWidgetcellChanged(int,int)));
}
}

void PLabel::on_actionPaste_triggered()
{
disconnect(reinterpret_cast<const QObject*>(tableWidget),SIGNAL(cellChanged(int,int)),this,SLOT(tableWidgetcellChanged(int,int)));
setUpdatesEnabled(false);
if(tableWidget)
{
	tableWidget->save_to_undo();
	if(tableWidget->rowCount()==0)
	{
	insertRowSTableWidget();
	}
	QStringList s,s1;
	int x,x1;
	const QClipboard *clipboard = QApplication::clipboard();
	const QMimeData *mimeData = clipboard->mimeData();
	statusBar()->showMessage(tr("Create Clipboard"));
	if (mimeData->hasText()) 
	{
		QString ss=mimeData->text();
		s=ss.split("\n");
		x=s.count();
		s1=s.at(0).split("\t");
		x1=s1.count();
		m_copyedString=mimeData->text();
	}

if(tableWidget&&(x==2)&&(x1==1))
{

	QList<QTableWidgetSelectionRange> mx;
	QList<QTableWidgetSelectionRange>::iterator ix;
	mx=tableWidget->selectedRanges();
	if(mx.count()>0)
	{
	ix=mx.begin();
	m_arow=(*ix).topRow();
	m_brow=(*ix).bottomRow();
	m_acol=(*ix).leftColumn();
	m_bcol=(*ix).rightColumn();
	m_copyedString=m_copyedString.trimmed();
	for(int icol=m_acol;icol<m_bcol+1;icol++)
	{
		for(int irow=m_arow;irow<m_brow+1;irow++)
		{
						if((icol)<(tableWidget->columnCount()-1))
						{
							tableWidget->item(irow,icol)->setText(m_copyedString);
						}
						if((icol)==(tableWidget->columnCount()-1))
						{
							connect(reinterpret_cast<const QObject*>(tableWidget),SIGNAL(cellChanged(int,int)),this,SLOT(tableWidgetcellChanged(int,int)));
							tableWidget->item(irow,icol)->setText(m_copyedString);
							disconnect(reinterpret_cast<const QObject*>(tableWidget),SIGNAL(cellChanged(int,int)),this,SLOT(tableWidgetcellChanged(int,int)));
						}

		}
	}
	}
}

if(tableWidget&&(x>1)&&(x1>0))
{
	QList<QTableWidgetSelectionRange> mx;
	QList<QTableWidgetSelectionRange>::iterator ix;
	mx=tableWidget->selectedRanges();
	if(mx.count()>0)
	{
	ix=mx.begin();
	int m_dx,m_dy;
	int k=0;
	m_arow=(*ix).topRow();
	m_brow=(*ix).bottomRow();
	m_acol=(*ix).leftColumn();
	m_bcol=(*ix).rightColumn();
	m_dx=m_arow;
	m_dy=m_acol;

	int rc=tableWidget->rowCount();
	statusBar()->showMessage(tr("Start create new rows"));
	int row=rc;
		m_arow=m_dx;
		m_acol=m_dy;
		m_brow=m_dx+x-1;
		m_bcol=m_dy;
	int total=((m_brow-m_arow)-(rc-m_dx));
	if(total>0)
	{
		tableWidget->setRowCount(rc+total);
	}
	else
	{
		tableWidget->setRowCount(rc);
	}
	if(total>0)
	{
		tableWidget->addItemsDBD(rc,total,tableWidget->columnCount());
	}

	statusBar()->showMessage(tr("Start Paste procedure"));
	k=0;
	for(int icol=0;icol<(tableWidget->columnCount()-1);icol++)
	{
			for(int irow=0;irow<rc+total;irow++)
		{
			if(((m_dx-1<irow)&&(irow<m_dx+m_brow-m_arow+1))&&
			   ((m_dy-1<icol)&&(icol<m_dy+m_bcol-m_acol+1)))
			{
				if(k<s.count())
				{
					QStringList s1;
					s1.clear();
					int x1;
					s1=s.at(k).split("\t");
					x1=s1.count();
					for(int u=0;u<x1;u++)
					{
						if((icol+u)<(tableWidget->columnCount()-1))
						{
							tableWidget->item(irow,icol+u)->setText(s1.at(u));
						}
					}
					s1.clear();
					k++;
				}
			}
		}
	}
	saveFlag=1;
	k=0;
	statusBar()->showMessage(tr("Finished copy text in row"));
	}
}
}
m_acol=0;
m_bcol=0;
m_arow=0;
m_brow=0;
setUpdatesEnabled(true);
connect(reinterpret_cast<const QObject*>(tableWidget),SIGNAL(cellChanged(int,int)),this,SLOT(tableWidgetcellChanged(int,int)));
}
void PLabel::on_actionDel_triggered()
{
	disconnect(reinterpret_cast<const QObject*>(tableWidget),SIGNAL(cellChanged(int,int)),this,SLOT(tableWidgetcellChanged(int,int)));
	if(tableWidget)
	{
	tableWidget->save_to_undo();
	setUpdatesEnabled(false);
	QList<QTableWidgetSelectionRange> mx;
	QList<QTableWidgetSelectionRange>::iterator ix;
	mx=tableWidget->selectedRanges();
	if(mx.count()>0)
	{
	ix=mx.begin();
	m_arow=(*ix).topRow();
	m_brow=(*ix).bottomRow();
	m_acol=(*ix).leftColumn();
	m_bcol=(*ix).rightColumn();

	for(int icol=m_acol;icol<m_bcol+1;icol++)
	{
		for(int irow=m_arow;irow<m_brow+1;irow++)
		{
			if((icol)<tableWidget->columnCount()-1)
			{
				tableWidget->item(irow,icol)->setText("");
			}
		}
	}
	}
	setUpdatesEnabled(true);
	}
	connect(reinterpret_cast<const QObject*>(tableWidget),SIGNAL(cellChanged(int,int)),this,SLOT(tableWidgetcellChanged(int,int)));
}

void PLabel::on_actionAdd_Records_triggered()
{
	insertRowSTableWidget();
}

void PLabel::on_actionRemove_Records_triggered()
{
if(tableWidget)
	{
		tableWidget->save_to_undo();
	int ret = QMessageBox::warning(this, tr("Label Software"),
		tr("Selected rows will be removed from table.\n"
		"Do you want to removed selected rows?"),
		QMessageBox::Yes | QMessageBox::No,
		QMessageBox::No);
	switch(ret)
	{
	case QMessageBox::Yes:
		disconnect(reinterpret_cast<const QObject*>(tableWidget),SIGNAL(cellChanged(int,int)),this,SLOT(tableWidgetcellChanged(int,int)));
		setUpdatesEnabled(false);
		if(tableWidget)
		{
			tableWidget->removeSelectedSItems();
		}
		setUpdatesEnabled(true);
		connect(reinterpret_cast<const QObject*>(tableWidget),SIGNAL(cellChanged(int,int)),this,SLOT(tableWidgetcellChanged(int,int)));
		break; 
	}
	}
saveFlag=1;
}

void PLabel::tableWidgetcellPressed(int arow,int acol,int prow,int pcol)
{
	if((tableWidget)&&(arow>-1)&&(acol>-1))
	{
		if(!statusFontWrite)
		{
		fontbox1.setCurrentFont(tableWidget->item(arow,acol)->font());
		m_Font=tableWidget->item(arow,acol)->font();
		p->setAFont(m_Font);
		m_Font.bold()?ui.actionFontBold->setChecked(true):ui.actionFontBold->setChecked(false);
		m_Font.italic()?ui.actionItalic->setChecked(true):ui.actionItalic->setChecked(false);
		m_Font.underline()?ui.actionUnderline->setChecked(true):ui.actionUnderline->setChecked(false);
		switch(m_Font.pointSize())
		{
		case 4:fontSizeBox1.setCurrentIndex(0);break;
		case 5:fontSizeBox1.setCurrentIndex(1);break;
		case 6:fontSizeBox1.setCurrentIndex(2);break;
		case 7:fontSizeBox1.setCurrentIndex(3);break;
		case 8:fontSizeBox1.setCurrentIndex(4);break;
		case 9:fontSizeBox1.setCurrentIndex(5);break;
		case 10:fontSizeBox1.setCurrentIndex(6);break;
		case 11:fontSizeBox1.setCurrentIndex(7);break;
		case 12:fontSizeBox1.setCurrentIndex(8);break;
		case 13:fontSizeBox1.setCurrentIndex(9);break;
		case 14:fontSizeBox1.setCurrentIndex(10);break;
		case 15:fontSizeBox1.setCurrentIndex(11);break;
		case 16:fontSizeBox1.setCurrentIndex(12);break;
		case 17:fontSizeBox1.setCurrentIndex(13);break;
		case 18:fontSizeBox1.setCurrentIndex(14);break;
		case 19:fontSizeBox1.setCurrentIndex(15);break;
		case 20:fontSizeBox1.setCurrentIndex(16);break;
		case 21:fontSizeBox1.setCurrentIndex(17);break;
		case 22:fontSizeBox1.setCurrentIndex(18);break;
		case 23:fontSizeBox1.setCurrentIndex(19);break;
		case 24:fontSizeBox1.setCurrentIndex(20);break;
		case 25:fontSizeBox1.setCurrentIndex(21);break;
		case 26:fontSizeBox1.setCurrentIndex(22);break;
		case 27:fontSizeBox1.setCurrentIndex(23);break;
		case 28:fontSizeBox1.setCurrentIndex(24);break;
		case 29:fontSizeBox1.setCurrentIndex(25);break;
		case 30:fontSizeBox1.setCurrentIndex(26);break;
		case 31:fontSizeBox1.setCurrentIndex(27);break;
		case 32:fontSizeBox1.setCurrentIndex(28);break;
		case 33:fontSizeBox1.setCurrentIndex(29);break;
		case 34:fontSizeBox1.setCurrentIndex(30);break;
		case 35:fontSizeBox1.setCurrentIndex(31);break;
		case 36:fontSizeBox1.setCurrentIndex(32);break;
		case 37:fontSizeBox1.setCurrentIndex(33);break;
		case 38:fontSizeBox1.setCurrentIndex(34);break;
		case 39:fontSizeBox1.setCurrentIndex(35);break;
		case 40:fontSizeBox1.setCurrentIndex(36);break;
		case 41:fontSizeBox1.setCurrentIndex(37);break;
		case 42:fontSizeBox1.setCurrentIndex(38);break;
		case 43:fontSizeBox1.setCurrentIndex(39);break;
		case 44:fontSizeBox1.setCurrentIndex(40);break;
		case 45:fontSizeBox1.setCurrentIndex(41);break;
		case 46:fontSizeBox1.setCurrentIndex(42);break;
		case 47:fontSizeBox1.setCurrentIndex(43);break;
		case 48:fontSizeBox1.setCurrentIndex(44);break;
		case 49:fontSizeBox1.setCurrentIndex(45);break;
		case 50:fontSizeBox1.setCurrentIndex(46);break;
		case 51:fontSizeBox1.setCurrentIndex(47);break;
		case 52:fontSizeBox1.setCurrentIndex(48);break;
		case 53:fontSizeBox1.setCurrentIndex(49);break;
		case 54:fontSizeBox1.setCurrentIndex(50);break;
		case 55:fontSizeBox1.setCurrentIndex(51);break;
		case 56:fontSizeBox1.setCurrentIndex(52);break;
		case 57:fontSizeBox1.setCurrentIndex(53);break;
		case 58:fontSizeBox1.setCurrentIndex(54);break;
		case 59:fontSizeBox1.setCurrentIndex(55);break;
		case 60:fontSizeBox1.setCurrentIndex(56);break;
		case 61:fontSizeBox1.setCurrentIndex(57);break;
		case 62:fontSizeBox1.setCurrentIndex(58);break;
		case 63:fontSizeBox1.setCurrentIndex(59);break;
		case 64:fontSizeBox1.setCurrentIndex(60);break;
		case 65:fontSizeBox1.setCurrentIndex(61);break;
		case 66:fontSizeBox1.setCurrentIndex(62);break;
		case 67:fontSizeBox1.setCurrentIndex(63);break;
		case 68:fontSizeBox1.setCurrentIndex(64);break;
		case 69:fontSizeBox1.setCurrentIndex(65);break;
		case 70:fontSizeBox1.setCurrentIndex(66);break;
		case 71:fontSizeBox1.setCurrentIndex(67);break;
		case 72:fontSizeBox1.setCurrentIndex(68);break;
		case 73:fontSizeBox1.setCurrentIndex(69);break;
		case 74:fontSizeBox1.setCurrentIndex(70);break;
		case 75:fontSizeBox1.setCurrentIndex(71);break;
		case 76:fontSizeBox1.setCurrentIndex(72);break;
		case 77:fontSizeBox1.setCurrentIndex(73);break;
		case 78:fontSizeBox1.setCurrentIndex(74);break;
		case 79:fontSizeBox1.setCurrentIndex(75);break;
		case 80:fontSizeBox1.setCurrentIndex(76);break;
		case 81:fontSizeBox1.setCurrentIndex(77);break;
		case 82:fontSizeBox1.setCurrentIndex(78);break;
		case 83:fontSizeBox1.setCurrentIndex(79);break;
		case 84:fontSizeBox1.setCurrentIndex(80);break;
		case 85:fontSizeBox1.setCurrentIndex(81);break;
		case 86:fontSizeBox1.setCurrentIndex(82);break;
		case 87:fontSizeBox1.setCurrentIndex(83);break;
		case 88:fontSizeBox1.setCurrentIndex(84);break;
		case 89:fontSizeBox1.setCurrentIndex(85);break;
		case 90:fontSizeBox1.setCurrentIndex(86);break;
		case 91:fontSizeBox1.setCurrentIndex(87);break;
		case 92:fontSizeBox1.setCurrentIndex(88);break;
		case 93:fontSizeBox1.setCurrentIndex(89);break;
		case 94:fontSizeBox1.setCurrentIndex(90);break;
		case 95:fontSizeBox1.setCurrentIndex(91);break;
		case 96:fontSizeBox1.setCurrentIndex(92);break;
		case 97:fontSizeBox1.setCurrentIndex(93);break;
		case 98:fontSizeBox1.setCurrentIndex(94);break;
		case 99:fontSizeBox1.setCurrentIndex(95);break;
		}
		}
		else
		{
		 statusFontWrite=false;
		}
	}
}

void PLabel::tableWidgetcellChanged(int arow,int acol)
{
bool ok;
if(tableWidget)
{

	if(acol==tableWidget->columnCount()-1)
	{
		int dec = tableWidget->item(arow,acol)->text().toInt(&ok, 10);
		if(!ok)
		{
			tableWidget->item(arow,acol)->setText("21");
		}
	}
	statusBar()->showMessage(tr("Table is edited"));
	if(!statusFontWrite)
	{
	tableWidget->item(arow,acol)->setFont(m_Font);
	}
	else
	{
		m_Font=fontbox1.currentFont();
		bool ok;
		m_Font.setPointSize(fontSizeBox1.currentText().toInt(&ok,10));
		ui.actionFontBold->isChecked()?m_Font.setBold(true):m_Font.setBold(false);
		ui.actionItalic->isChecked()?m_Font.setItalic(true):m_Font.setItalic(false);
		ui.actionUnderline->isChecked()?m_Font.setUnderline(true):m_Font.setUnderline(false);
		p->setAFont(m_Font);
	tableWidget->item(arow,acol)->setFont(m_Font);
	statusFontWrite=false;
	}
	saveFlag=1;
}
}

void PLabel::on_actionLabel_Settings_triggered()
{
QArticle a(this);
connect(&a,SIGNAL(enter_article(QStringList)),this,SLOT(setLabelSettings(QStringList)));
a.initData(labels);
a.setFontLabels(tableWidget->item(0,0)->font(),
				tableWidget->item(0,1)->font(),
				tableWidget->item(0,2)->font(),
				tableWidget->item(0,3)->font(),
				tableWidget->item(0,4)->font(),
				tableWidget->item(0,5)->font(),
				tableWidget->item(0,6)->font(),
				tableWidget->item(0,7)->font()
				);
a.exec();
}

void PLabel::setLabelSettings(QStringList s)
{
labels=s;

if(tableWidget)
{
tableWidget->setHorizontalHeaderLabels(labels);
}
writeSettings();
saveFlag=1;
}

void PLabel::writeSettings()
{
	QSettings settings("HSG", "PL");

	settings.beginGroup("MainWindow");
	settings.setValue("Label1", labels.at(0));
	settings.setValue("Label2", labels.at(1));
	settings.setValue("Label3", labels.at(2));
	settings.setValue("Label4", labels.at(3));
	settings.setValue("Label5", labels.at(4));
	settings.setValue("Label6", labels.at(5));
	settings.setValue("Label7", labels.at(6));
	settings.setValue("Label8", labels.at(7));

	settings.setValue("top",m_atop);
	settings.setValue("bottom",m_abottom);
	settings.setValue("left",m_aleft);
	settings.setValue("right",m_aright);

	settings.setValue("Column_0_Width",Column_0_Width);
	settings.setValue("Column_1_Width",Column_1_Width);
	settings.setValue("Column_2_Width",Column_2_Width);
	settings.setValue("Column_3_Width",Column_3_Width);
	settings.setValue("Column_4_Width",Column_4_Width);
	settings.setValue("Column_5_Width",Column_5_Width);
	settings.setValue("Column_6_Width",Column_6_Width);
	settings.setValue("Column_7_Width",Column_7_Width);
	settings.setValue("Column_8_Width",Column_8_Width);
	if(recentFileActs[0])
	{
			settings.setValue("File1",recentFileActs[0]->text());
	}

	settings.endGroup();
}

void PLabel::readSettings()
{
	QSettings settings("HSG", "PL");
	QStringList s;
	QString m_value,m_File1;
	settings.beginGroup("MainWindow");
	s<<settings.value("Label1").toString()<<settings.value("Label2").toString()<<
		settings.value("Label3").toString()<<settings.value("Label4").toString()<<
		settings.value("Label5").toString()<<settings.value("Label6").toString()<<
		settings.value("Label7").toString()<<settings.value("Label8").toString()<<"Count";
	m_atop=settings.value("top").toInt();
	m_abottom=settings.value("bottom").toInt();
	m_aleft=settings.value("left").toInt();
	m_aright=settings.value("right").toInt();
	m_File1=settings.value("File1").toString();
if(recentFileActs[0])
{
	if(m_File1!="")
	{
		recentFileActs[0]->setText(m_File1);
		recentFileActs[0]->setData(m_File1);
		recentFileActs[0]->setVisible(true);
	}
}
	Column_0_Width=settings.value("Column_0_Width").toInt();
	Column_1_Width=settings.value("Column_1_Width").toInt();
	Column_2_Width=settings.value("Column_2_Width").toInt();
	Column_3_Width=settings.value("Column_3_Width").toInt();
	Column_4_Width=settings.value("Column_4_Width").toInt();
	Column_5_Width=settings.value("Column_5_Width").toInt();
	Column_6_Width=settings.value("Column_6_Width").toInt();
	Column_7_Width=settings.value("Column_7_Width").toInt();
	Column_8_Width=settings.value("Column_8_Width").toInt();
	settings.endGroup();
	labels=s;
}

QString PLabel::generateSSIDNumber()
{
	QString m_name;
	QSettings settings("HSG", "PL");
	QStringList s;
	QString m_value;
	settings.beginGroup("MainWindow");
	m_name=settings.value("companyName").toString();
	settings.endGroup();
	char v;
	int c=m_name.count();
	int sum=0;

	for(int i=0;i<m_name.count();i++)
	{
        v=(m_name.at(i).unicode());
		int s;
		s=(int)v;
		s=s*(256*i+1);
		sum=sum+s;
	}
	sum++;
	if(m_name=="")
	{
		sum=0;
	}
return QString::number(sum,10);
}

bool PLabel::generateSSID2Number(QString m_name)
{
	char v;
	int c=m_name.count();
	int sum=0;

	QSettings settings("HSG", "PL");
	QStringList s;
	QString m_value;
	settings.beginGroup("MainWindow");
	QString m_lic;
	m_lic=settings.value("licenceNumber").toString();
	settings.endGroup();
	for(int i=0;i<m_name.count();i++)
	{
        v=(m_name.at(i).unicode());
		int s;
		s=(int)v;
		s=s*(257*i+7);
		sum=sum+s;
	}
	sum++;
	if(m_lic.toInt()==sum)
	{
		rglprd=true;
		setWindowTitle("Label Software");
		QSettings settings("HSG", "PL");
		QStringList s;
		QString m_value;
		settings.beginGroup("MainWindow");
		reg_name=settings.value("companyName").toString();
		settings.endGroup();
		on_actionNew_2_triggered();
		lic_name="Licensed to: "+reg_name;
		return true;
	}
	else
	{
		rglprd=false;
		setWindowTitle("Label Software-trial version");
		on_actionNew_2_triggered();
		lic_name="This is TRIAL VERSION.";
		return false;
	}
}

void PLabel::checkRegisteredData(QString s1,QString s2,QString s3)
{
	QMessageBox mb;

	QSettings settings("HSG", "PL");
	settings.beginGroup("MainWindow");
	settings.setValue("companyName", s1);
	settings.setValue("companyNumber", s2);
	settings.setValue("licenceNumber", s3);
	settings.endGroup();

	if(generateSSID2Number(generateSSIDNumber()))
	{
		mb.about(this,"Information","Product is successful registered");
	}
	else
	{
		if(!trialLogin())
		{
			QMessageBox::warning(this,
				"",
				"Your trial period expired.<br />"
				"<a href=\"http://www.prolabelcreator.com\">http://www.prolabelcreator.com</a><br>"
				"Purchase Pro Label Creator ver.3.01 Online Now<br />"
				"Price: 29.95 USD<br />"
				,QMessageBox::Ok);
			exit(0);
		}
		else
		{
			mb.about(this,"Information","Product is unsuccessful registered,continue with trial version");
		}
	}
}

void PLabel::createLicenceDialog()
{
// 	if(!trialLogin())
// 	{
// 		QMessageBox::warning(this,
// 			"",
// 			"Your trial period expired.<br />"
// 			"<a href=\"http://www.prolabelcreator.com\">http://www.prolabelcreator.com</a><br>"
// 			"Purchase Pro Label Creator ver.3.01 Online Now<br />"
// 			"Price: 29.95 USD<br />"
// 			,QMessageBox::Ok);
// 		exit(0);
// 	}

	QLabelLicence l(this);
	l.initSS(getTrialDay());
	connect(&l,SIGNAL(setRegisteredData(QString,QString,QString)),this,SLOT(checkRegisteredData(QString,QString,QString)));
	l.exec();
}

void PLabel::on_actionAbout_2_triggered()
{
 QAboutS a(this);
 QStringList s;
 s<<"Label Software"<<lic_name<<"All rights reserved by Hardware-Software Group";
 a.setInfo(s);
 a.exec();
}

void PLabel::tableWidgetcellProgresBar(int arow,int atotal)
{
int vv=((int)((100*arow)/(atotal)));
statusBar()->showMessage("Progress... "+QString::number(vv,10)+" %");
}


void PLabel::on_actionFind_triggered()
{
QSFind m_find;
connect(&m_find,SIGNAL(s_returnPressed(QString)),this,SLOT(findStringInTable(QString)));
connect(&m_find,SIGNAL(s_next_Pressed()),this,SLOT(findStringNextInTable()));
connect(&m_find,SIGNAL(s_previous_Pressed()),this,SLOT(findStringPreviousInTable()));
statusBar()->showMessage("");
m_find.exec();
}
void PLabel::findStringInTable(QString s)
{
if(tableWidget)
	{
	int mr=tableWidget->findSTableItems(s);
	mr_total=mr;
	if(mr>0)
	{
		statusBar()->showMessage("Records found : "+QString::number(mr,10));
	}
	else
	{
		statusBar()->showMessage("No records found!");
	}
	}
}

void PLabel::findStringNextInTable()
{
	if(tableWidget)
	{
		tableWidget->setFocus(); 
		int mr=tableWidget->findNextSTableItems();
		if(mr>0)
		{
			statusBar()->showMessage("Record found : "+QString::number(mr,10)+" / "+QString::number(mr_total,10));
		}

	}
}
void PLabel::findStringPreviousInTable()
{
	if(tableWidget)
	{
		tableWidget->setFocus(); 
		int mr=tableWidget->findPreviousSTableItems();
		if(mr>0)
		{
			statusBar()->showMessage("Record found : "+QString::number(mr,10)+" / "+QString::number(mr_total,10));
		}
	}
}

void PLabel::showDataFromFileExtended(QString filename)
{
	if(tableWidget)
	{
		if(saveFlag)
		{
			int ret = QMessageBox::warning(this, tr("Label Software"),
				tr("The document has been modified.\n"
				"Do you want to save your changes?"),
				QMessageBox::Save | QMessageBox::Discard,
				QMessageBox::Save);
			switch(ret)
			{
			case QMessageBox::Save:on_actionSave_triggered();break; 
			}
		}
		delete tableWidget;
		tableWidget=NULL;
	}
	tableWidget = new QSTableWidget(ui.centralWidget);
	connect(this,SIGNAL(setProgressS(int,int)),this,SLOT(tableWidgetcellProgresBar(int,int)));
	connect(tableWidget,SIGNAL(currentCellChanged(int,int,int,int)),this,SLOT(tableWidgetcellPressed(int,int,int,int)));
	tableWidget->setGeometry(ui.centralWidget->rect());
	tableWidget->setRowCount(65636);
	tableWidget->setItemDelegate(p);

	setUpdatesEnabled(false);
	tableWidget->showDBDExtended(filename);
	m_backgroundColor=tableWidget->cl_backGroundColor;
	setWindowTitle("Label Software"+tableWidget->getFileName());
	if(tableWidget->getFileName()!="")
	{
		recentFileActs[0]->setText(tableWidget->getFileName());
		recentFileActs[0]->setData(tableWidget->getFileName());
		recentFileActs[0]->setVisible(true);
	}

	connect(tableWidget,SIGNAL(sendMouseRightClick1(QPoint)),this,SLOT(createPopupTableWidgetMenu(QPoint)));

	setUpdatesEnabled(true);
	connect(reinterpret_cast<const QObject*>(tableWidget),SIGNAL(cellChanged(int,int)),this,SLOT(tableWidgetcellChanged(int,int)));
	connect(tableWidget,SIGNAL(cellActivated(int,int)),this,SLOT(tableWidgetcellActivated(int,int)));
	tableWidget->setCurrentCell(0,0);
	//create empty fields position 
	mdbprint_elementPos.clear();
	QStringList mlistXY=tableWidget->m_xyInfo.split(",");

	for(int io=0;io<tableWidget->columnCount()-1;io++)
	{
		newprint_elementPos=new dbprint_elementPos;
		newprint_elementPos->id=io;
		newprint_elementPos->tip=0;
		// 			newprint_elementPos->m_x=((double)1/20)/(double)1;;	
		// 			newprint_elementPos->m_y=((double)((io)*1/(double)tableWidget->columnCount())+(double)(1/(double)tableWidget->columnCount()))/(double)1;;
		newprint_elementPos->m_x=mlistXY.at(2*io).toDouble();	
		newprint_elementPos->m_y=mlistXY.at(2*io+1).toDouble();
		newprint_elementPos->m_color=tableWidget->getColor(io);
		newprint_elementPos->m_graphic_Font=tableWidget->getGraphicFont(io);
		newprint_elementPos->m_rotate=tableWidget->getRotate(io);
		mdbprint_elementPos.push_back(newprint_elementPos);
	}
	e_col=tableWidget->m_colPreview;
	e_row=tableWidget->m_rowPreview;
	m_left->setValue(e_col,e_row);	
	m_vectorPrintElementPos=mdbprint_elementPos;
	saveFlag=0;
}


void PLabel::on_actionCut_triggered()
{
 on_actionCopy_triggered();
 on_actionDel_triggered();
}

void PLabel::on_action_triggered()
{

}

void PLabel::createPopupTableWidgetMenu(QPoint s)
{
	QMenu m_popupMenu;
	
	m_popupMenu.addAction(ui.actionCopy);
	m_popupMenu.addAction(ui.actionPaste);
	m_popupMenu.addAction(ui.actionCut);
	m_popupMenu.addAction(ui.actionDel);
	m_popupMenu.addSeparator();
	m_popupMenu.addAction(ui.actionFind);
	m_popupMenu.addSeparator();
	m_popupMenu.addAction(ui.actionAdd_Records);
	m_popupMenu.addAction(ui.actionRemove_Records);
	m_popupMenu.addSeparator();
	m_popupMenu.addAction(ui.actionConcatenate_Rows);
	m_popupMenu.addAction(ui.actionExpand_in_Rows);
	m_popupMenu.addSeparator();
	m_popupMenu.addAction(ui.actionRemove_Empty_Rows);
	m_popupMenu.addSeparator();
	m_popupMenu.addAction(ui.actionAdd_Column);
	m_popupMenu.addAction(ui.actionRemove_Columns);
	m_popupMenu.addSeparator();
	m_popupMenu.addAction(ui.actionConcatenate);
	m_popupMenu.addAction(ui.actionExpand);
	m_popupMenu.addSeparator();
	m_popupMenu.exec(QCursor::pos());
}

void PLabel::closeEvent(QCloseEvent *event)
{
	if(tableWidget)
	{
		if(saveFlag)
		{
			int ret = QMessageBox::warning(this, tr("Label Software"),
				tr("The document has been modified.\n"
				"Do you want to save your changes?"),
				QMessageBox::Save | QMessageBox::Discard,
				QMessageBox::Save);
			switch(ret)
			{
			case QMessageBox::Save:on_actionSave_triggered();break; 
			}
		}
		delete tableWidget;
		tableWidget=NULL;
	}
	writeSettings();    
}



void PLabel::on_actionPage_Settings_triggered()
{
	QSPageSettings b(this);
	connect(&b,SIGNAL(sendValuesPageMargin(int,int,int,int)),this,SLOT(writeValuesPageMargin(int,int,int,int)));
	b.initData(m_atop,m_abottom,m_aleft,m_aright);
	b.exec();
}

void PLabel::writeValuesPageMargin(int a,int b,int c,int d)
{
 m_atop=a;
 m_abottom=b;
 m_aleft=c;
 m_aright=d;
}

void PLabel::on_actionFind_Next_triggered()
{
	findStringNextInTable();
}

void PLabel::on_actionFind_Previous_triggered()
{
	findStringPreviousInTable();
}
void PLabel::tableWidgetcellClicked(int arow,int acol)
{
   fontbox1.setCurrentFont(tableWidget->item(arow,acol)->font());
   p->setAFont(tableWidget->item(arow,acol)->font());
}

void PLabel::on_actionAdd_Column_triggered()
{
	if(tableWidget)
	{
		tableWidget->save_to_undo();
		setUpdatesEnabled(false);
		QList<QTableWidgetSelectionRange> mx;
		QList<QTableWidgetSelectionRange>::iterator ix;
		int m_arow,m_brow,m_acol,m_bcol;

		mx=tableWidget->selectedRanges();
		if(mx.count()>0)
		{
			ix=mx.begin();
			m_arow=(*ix).topRow();
			m_brow=(*ix).bottomRow();
			m_acol=(*ix).leftColumn();
			m_bcol=(*ix).rightColumn();
			if(m_bcol<tableWidget->columnCount()-1)
			{
				tableWidget->insertColumn(m_bcol+1); 
				tableWidget->setRowHeight(tableWidget->rowCount()-1,18);
				QString m_empty="";
				for(int i=0;i<tableWidget->rowCount();i++)
				{
					tableWidget->setItem(i, m_bcol+1,new QTableWidgetItem(m_empty));
					tableWidget->item(i, m_bcol+1)->setFont(m_Font);
				}
			}
			if(m_bcol==tableWidget->columnCount()-1)
			{
				tableWidget->insertColumn(tableWidget->columnCount()-1); 
				tableWidget->setRowHeight(tableWidget->rowCount()-1,18);
				QString m_empty="";
				for(int i=0;i<tableWidget->rowCount();i++)
				{
					tableWidget->setItem(i, tableWidget->columnCount()-2,new QTableWidgetItem(m_empty));
					tableWidget->item(i, tableWidget->columnCount()-2)->setFont(m_Font);
				}
			}
			//create empty fields position 
			if(m_bcol<tableWidget->columnCount()-1)
			{
 				int id_max=0;
				for(idbprint_elementPos=mdbprint_elementPos.begin();idbprint_elementPos<mdbprint_elementPos.end();idbprint_elementPos++)
 				{
					id_max=id_max>(*idbprint_elementPos)->id?id_max:(*idbprint_elementPos)->id;
 				}
				newprint_elementPos=new dbprint_elementPos;
				newprint_elementPos->id=++id_max;
				newprint_elementPos->tip=0;
				newprint_elementPos->m_x=0;
				newprint_elementPos->m_y=0;
				newprint_elementPos->m_rotate=0;
				mdbprint_elementPos.push_back(newprint_elementPos);
			}
// 			mdbprint_elementPos.clear();
// 			for(int io=0;io<tableWidget->columnCount()-1;io++)
// 			{
// 				newprint_elementPos=new dbprint_elementPos;
// 				newprint_elementPos->id=io;
// 				newprint_elementPos->tip=0;
// 				newprint_elementPos->m_x=((double)1/20)/(double)1;;	
// 				newprint_elementPos->m_y=((double)((io)*1/(double)tableWidget->columnCount())+(double)(1/(double)tableWidget->columnCount()))/(double)1;;
// 				newprint_elementPos->m_rotate=0;
// 				mdbprint_elementPos.push_back(newprint_elementPos);
// 			}
			m_vectorPrintElementPos=mdbprint_elementPos;
		}
		setUpdatesEnabled(true);
	}
}
void PLabel::on_actionRemove_Columns_triggered()
{
	if(tableWidget)
	{
		tableWidget->save_to_undo();
		int ret = QMessageBox::warning(this, tr("Label Software"),
			tr("Selected columns will be removed from table.\n"
			"Do you want to removed selected columns?"),
			QMessageBox::Yes | QMessageBox::No,
			QMessageBox::Yes);
		switch(ret)
		{
		case QMessageBox::Yes:
			disconnect(reinterpret_cast<const QObject*>(tableWidget),SIGNAL(cellChanged(int,int)),this,SLOT(tableWidgetcellChanged(int,int)));
			setUpdatesEnabled(false);
			if(tableWidget)
			{
				int leftcol,rightcol;
				tableWidget->removeSelectedSColumn(leftcol,rightcol);

				//add code here
				//create empty fields position 


				for(int icol=rightcol;icol>leftcol-1;icol--)
				{
					for(idbprint_elementPos=mdbprint_elementPos.begin();idbprint_elementPos<mdbprint_elementPos.end();idbprint_elementPos++)
					{
						if((*idbprint_elementPos)->id==icol)
						{
							mdbprint_elementPos.erase(idbprint_elementPos);
						}
					}
				}
				int new_id=0;
				for(idbprint_elementPos=mdbprint_elementPos.begin();idbprint_elementPos<mdbprint_elementPos.end();idbprint_elementPos++)
				{
				 (*idbprint_elementPos)->id=new_id;
					new_id++;
				}
// 				mdbprint_elementPos.clear();
//				m_vectorPrintElementPos=mdbprint_elementPos;
			}
			setUpdatesEnabled(true);
			connect(reinterpret_cast<const QObject*>(tableWidget),SIGNAL(cellChanged(int,int)),this,SLOT(tableWidgetcellChanged(int,int)));
			break; 
		}
	}
	saveFlag=1;

}

void PLabel::on_actionConcatenate_triggered()
{

	if(tableWidget)
	{
		tableWidget->save_to_undo();
		int ret = QMessageBox::warning(this, tr("Label Software"),
			tr("Selected cells will be concatenated.\n"
			"Do you want to concatenated selected cells?"),
			QMessageBox::Yes | QMessageBox::No,
			QMessageBox::No);
		switch(ret)
		{
		case QMessageBox::Yes:
			disconnect(reinterpret_cast<const QObject*>(tableWidget),SIGNAL(cellChanged(int,int)),this,SLOT(tableWidgetcellChanged(int,int)));
			setUpdatesEnabled(false);
			if(tableWidget)
			{
				tableWidget->concatenateSelectedSColumn();				//tuka//
			}
			setUpdatesEnabled(true);
			connect(reinterpret_cast<const QObject*>(tableWidget),SIGNAL(cellChanged(int,int)),this,SLOT(tableWidgetcellChanged(int,int)));
			break; 
		}
	}
	saveFlag=1;
}

void PLabel::on_actionExpand_triggered()
{
	if(tableWidget)
	{
		tableWidget->save_to_undo();
		int ret = QMessageBox::warning(this, tr("Label Software"),
			tr("Text will be expanded in selected cells.\n"
			"Do you want to expand text in selected cells?"),
			QMessageBox::Yes | QMessageBox::No,
			QMessageBox::No);
		switch(ret)
		{
		case QMessageBox::Yes:
			disconnect(reinterpret_cast<const QObject*>(tableWidget),SIGNAL(cellChanged(int,int)),this,SLOT(tableWidgetcellChanged(int,int)));
			setUpdatesEnabled(false);
			if(tableWidget)
			{
				tableWidget->expandSelectedSColumn();			
			}
			setUpdatesEnabled(true);
			connect(reinterpret_cast<const QObject*>(tableWidget),SIGNAL(cellChanged(int,int)),this,SLOT(tableWidgetcellChanged(int,int)));
			break; 
		}
	}
	saveFlag=1;
}

void PLabel::on_actionUndo_triggered()
{
	if(tableWidget)
	{
		tableWidget->undo();
	}
}

void PLabel::on_actionRemove_Empty_Rows_triggered()
{
	tableWidget->save_to_undo();
	int ret = QMessageBox::warning(this, tr("Label Software"),
		tr("Empty rows will be removed.\n"
		"Do you want to remove empty rows?"),
		QMessageBox::Yes | QMessageBox::No,
		QMessageBox::No);
	switch(ret)
	{
	case QMessageBox::Yes:
		disconnect(reinterpret_cast<const QObject*>(tableWidget),SIGNAL(cellChanged(int,int)),this,SLOT(tableWidgetcellChanged(int,int)));
		setUpdatesEnabled(false);
		if(tableWidget)
		{
			tableWidget->removeSelectedEmptyRows();			
		}
		setUpdatesEnabled(true);
		connect(reinterpret_cast<const QObject*>(tableWidget),SIGNAL(cellChanged(int,int)),this,SLOT(tableWidgetcellChanged(int,int)));
		break; 
	}
saveFlag=1;
}

void PLabel::on_actionConcatenate_Rows_triggered()
{
	if(tableWidget)
	{
		tableWidget->save_to_undo();
		int ret = QMessageBox::warning(this, tr("Label Software"),
			tr("Selected cells will be concatenated.\n"
			"Do you want to concatenated selected cells?"),
			QMessageBox::Yes | QMessageBox::No,
			QMessageBox::No);
		switch(ret)
		{
		case QMessageBox::Yes:
			disconnect(reinterpret_cast<const QObject*>(tableWidget),SIGNAL(cellChanged(int,int)),this,SLOT(tableWidgetcellChanged(int,int)));
			setUpdatesEnabled(false);
			if(tableWidget)
			{
				tableWidget->concatenateSelectedSRows();				//tuka//
			}
			setUpdatesEnabled(true);
			connect(reinterpret_cast<const QObject*>(tableWidget),SIGNAL(cellChanged(int,int)),this,SLOT(tableWidgetcellChanged(int,int)));
			break; 
		}
	}
	saveFlag=1;
}

void PLabel::on_actionExpand_in_Rows_triggered()
{
	if(tableWidget)
	{
		tableWidget->save_to_undo();
		int ret = QMessageBox::warning(this, tr("Label Software"),
			tr("Selected cells will be expanded in bellow rows.\n"
			"Do you want to expanded selected cells?"),
			QMessageBox::Yes | QMessageBox::No,
			QMessageBox::No);
		switch(ret)
		{
		case QMessageBox::Yes:
			disconnect(reinterpret_cast<const QObject*>(tableWidget),SIGNAL(cellChanged(int,int)),this,SLOT(tableWidgetcellChanged(int,int)));
			setUpdatesEnabled(false);
			if(tableWidget)
			{
				tableWidget->expandSelectedSRows();				//tuka//
			}
			setUpdatesEnabled(true);
			connect(reinterpret_cast<const QObject*>(tableWidget),SIGNAL(cellChanged(int,int)),this,SLOT(tableWidgetcellChanged(int,int)));
			break; 
		}
	}
	saveFlag=1;
}

void PLabel::on_actionZoom_In_triggered()
{
view->scale(1.1,1.1);
view->centerOn(m_center);
}

void PLabel::on_actionZoom_Out_triggered()
{
view->scale(1/1.1,1/1.1);
view->centerOn(m_center);
}

void PLabel::on_actionAdd_GraphicsItem_triggered()
{
   QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"/home/",tr("Images (*.png *.jpg *.gif *.bmp *.tif)"));
   double scale=1.0f;  
   double scale_w=1.0f;
   if(fileName!="")
       {
        lpix1=new QLab1PixmapItem(0,scene);
		QPointF m_initPos;
		m_initPos=QPointF(-150,0);
		lpix1->setPos(m_initPos);
		QPixmap pixmap( 20, 20 );
		double w=(double)707/(double)e_col;
		double h=(double)1000/(double)e_row;
		pixmap.load(fileName);
		if(w>h)
		{
			scale=(pixmap.height()/h);
			if(scale>1)
			{
				pixmap=pixmap.scaled(pixmap.width()/scale-4,pixmap.height()/scale-4,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
			}
		}
		else
		{
			scale=(pixmap.width()/w);
			if(scale>1)
			{
				pixmap=pixmap.scaled(pixmap.width()/scale-4,pixmap.height()/scale-4,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
			}

		}
		scale_w=scale;
		QRect r=pixmap.rect();
		lpix1->setPixmap(pixmap);
		m_zvalue_images+=0.01;
		lpix1->setZValue(m_zvalue_images);
		scene->addItem(lpix1);
		scale_w=scale=1;
		QByteArray bytes;
		QBuffer buffer(&bytes);
		buffer.open(QIODevice::WriteOnly);
        pixmap.save(&buffer, "PNG"); // writes pixmap into bytes in PNG format
		max_image_count=0;
		for(idbprint_elementImagePos=mdbprint_elementImagePos.begin();idbprint_elementImagePos<mdbprint_elementImagePos.end();idbprint_elementImagePos++)
		{
			(*idbprint_elementImagePos)->id>max_image_count?max_image_count=(*idbprint_elementImagePos)->id:max_image_count;
		}
		max_image_count++;

		newprint_elementImagePos=new dbprint_elementImagePos;
		newprint_elementImagePos->id=max_image_count;
		newprint_elementImagePos->tip=1;
		newprint_elementImagePos->m_data=bytes;
		newprint_elementImagePos->m_scale=scale;
		newprint_elementImagePos->m_scale_w=scale_w;
		newprint_elementImagePos->m_x=0;	
		newprint_elementImagePos->m_y=0;
		mdbprint_elementImagePos.push_back(newprint_elementImagePos);
		lpix1->SetId(max_image_count);
		scene->addInfoImage(max_image_count,m_initPos.rx(),m_initPos.ry(),bytes,scale,scale_w);
		scene->clearSelection();
		scene->update();
        }
}


void PLabel::on_actionAdd_GraphicsObject()
{
	double scale=1.0f;  
	double scale_w=1.0f;

		lpix1=new QLab1PixmapItem(0,scene);
		QPointF m_initPos;
		m_initPos=QPointF(-150,0);
		lpix1->setPos(m_initPos);
		QPixmap pixmap( 20, 20 );
		//pixmap.fill(Qt::transparent);

		double w=(double)707/(double)e_col;
		double h=(double)1000/(double)e_row;
		
		QPainter painter(&pixmap);
		painter.fillRect(0, 0,20, 20,Qt::gray);
		if(w>h)
		{
			scale=(pixmap.height()/h);
			if(scale>1)
			{
				pixmap=pixmap.scaled(pixmap.width()/scale-4,pixmap.height()/scale-4,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
			}
		}
		else
		{
			scale=(pixmap.width()/w);
			if(scale>1)
			{
				pixmap=pixmap.scaled(pixmap.width()/scale-4,pixmap.height()/scale-4,Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
			}

		}
		scale_w=scale;
		QRect r=pixmap.rect();
		lpix1->setPixmap(pixmap);
		m_zvalue_images+=0.01;
		lpix1->setZValue(m_zvalue_images);
		scene->addItem(lpix1);
		scale_w=scale=1;
		QByteArray bytes;
		QBuffer buffer(&bytes);
		buffer.open(QIODevice::WriteOnly);
		pixmap.save(&buffer, "PNG"); // writes pixmap into bytes in PNG format
		max_image_count=0;
		for(idbprint_elementImagePos=mdbprint_elementImagePos.begin();idbprint_elementImagePos<mdbprint_elementImagePos.end();idbprint_elementImagePos++)
		{
			(*idbprint_elementImagePos)->id>max_image_count?max_image_count=(*idbprint_elementImagePos)->id:max_image_count;
		}
		max_image_count++;

		newprint_elementImagePos=new dbprint_elementImagePos;
		newprint_elementImagePos->id=max_image_count;
		newprint_elementImagePos->tip=1;
		newprint_elementImagePos->m_data=bytes;
		newprint_elementImagePos->m_scale=scale;
		newprint_elementImagePos->m_scale_w=scale_w;
		newprint_elementImagePos->m_x=0;	
		newprint_elementImagePos->m_y=0;
		mdbprint_elementImagePos.push_back(newprint_elementImagePos);
		lpix1->SetId(max_image_count);
		scene->addInfoImage(max_image_count,m_initPos.rx(),m_initPos.ry(),bytes,scale,scale_w);
		scene->clearSelection();
		scene->update();
}

void PLabel::on_actionDelete_triggered()
{
	scene->deleteSelectedItem();
}

QDate PLabel::getDate()
{
	QDate m_Date;
	QSettings settings("HKEY_CURRENT_USER\\CLSID\\{10004565-123OI-123689-458797}",QSettings::NativeFormat);
	return	QDate::fromString(settings.value("Date").toString(),"ddMMyyyy");
}
void PLabel::setDate(QDate d)
{
	QDate m_Date;
	QSettings settings("HKEY_CURRENT_USER\\CLSID\\{10004565-123OI-123689-458797}",QSettings::NativeFormat);
	settings.setValue("Date",d.toString("ddMMyyyy"));
}

void PLabel::setInitialDate(QDate d,QTime t)
{
	QSettings settings("HKEY_CURRENT_USER\\CLSID\\{10004565-123OI-123689-458797}",QSettings::NativeFormat);
	if(!settings.value("a").isValid())
	{
		settings.setValue("a",1);
		settings.setValue("Date",d.toString("ddMMyyyy"));
		settings.setValue("Trdy",14);
		settings.setValue("EntryTime",t.toString("hh:mm:ss"));
		settings.setValue("ExitTime",t.toString("hh:mm:ss"));
	}
	else
	{
		int ii=0;
	}
}

QTime PLabel::getEntryTime()
{
	QTime m_Date;
	QSettings settings("HKEY_CURRENT_USER\\CLSID\\{10004565-123OI-123689-458797}",QSettings::NativeFormat);
	return	QTime::fromString(settings.value("EntryTime").toString(),"ddMMyyyy");
}
QTime PLabel::getExitTime()
{
	QTime m_Date;
	QSettings settings("HKEY_CURRENT_USER\\CLSID\\{10004565-123OI-123689-458797}",QSettings::NativeFormat);
	return	QTime::fromString(settings.value("ExitTime").toString(),"ddMMyyyy");
}
void PLabel::setEntryTime()
{
	QTime m_Date;
	QSettings settings("HKEY_CURRENT_USER\\CLSID\\{10004565-123OI-123689-458797}",QSettings::NativeFormat);
	settings.setValue("EntryTime",QTime::currentTime().toString("hh:mm:ss"));
}
void PLabel::setExitTime()
{
	QTime m_Date;
	QSettings settings("HKEY_CURRENT_USER\\CLSID\\{10004565-123OI-123689-458797}",QSettings::NativeFormat);
	settings.setValue("ExitTime",QTime::currentTime().toString("hh:mm:ss"));
}

int PLabel::getTrialDay()
{
	QSettings settings("HKEY_CURRENT_USER\\CLSID\\{10004565-123OI-123689-458797}",QSettings::NativeFormat);
	return	settings.value("Trdy").toInt();
}
void PLabel::setTrialDay(int days)
{
	QSettings settings("HKEY_CURRENT_USER\\CLSID\\{10004565-123OI-123689-458797}",QSettings::NativeFormat);
	settings.setValue("Trdy",days);
}
bool PLabel::trialLogin()
{
	bool m_stat=true;
	if(getTrialDay()>0)
	{
		if(getDate()==QDate::currentDate())
		{
			if(QTime::currentTime()<getExitTime())
			{
				setTrialDay(getTrialDay()-1);
			}
		}
		else 
		{
			int rest_days=getDate().daysTo(QDate::currentDate());
			if(rest_days>0)
			{
				setTrialDay(getTrialDay()-rest_days);
			}
			else
			{
				setTrialDay(0);
			}
			setDate(QDate::currentDate());
		}
		m_stat=true;
	}
	else
	{
		m_stat=false;
	}
	return m_stat;
}	


void PLabel::sendToBack()
{
	if (scene->selectedItems().isEmpty())
		return;

	QGraphicsItem *selectedItem = scene->selectedItems().first();
	QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

	qreal zValue = 0;
	foreach (QGraphicsItem *item, overlapItems) {
		if (item->zValue() <= zValue)
			zValue = item->zValue() - 0.1;
	}
	selectedItem->setZValue(zValue);
}

void PLabel::on_actionSendToBack_triggered()
{
sendToBack();
}
void PLabel::backToFront()
{
	if (scene->selectedItems().isEmpty())
		return;

	QGraphicsItem *selectedItem = scene->selectedItems().first();
	QList<QGraphicsItem *> overlapItems = selectedItem->collidingItems();

	qreal zValue = 0;
	foreach (QGraphicsItem *item, overlapItems) {
		if (item->zValue() >= zValue )
			zValue = item->zValue() + 0.1;
	}
	selectedItem->setZValue(zValue);
}


void PLabel::on_actionBringToFront_triggered()
{
backToFront();
}

void PLabel::on_actionScaled_triggered()
{
scene->scaleSelectedItem(5);
scene->update();
}

void PLabel::on_actionScaled1_triggered()
{
	scene->scaleSelectedItem(-5);
	scene->update();
}

void PLabel::on_actionFontBold_triggered()
{

}

void PLabel::on_actioncolor_triggered()
{
		QColor color = scene->GetColorText();
		color=QColorDialog::getColor(color, this);
	if (color.isValid()) {
		scene->setColorText(color);
		scene->update();
	}
}

void PLabel::on_actionExportImage_triggered()
{
	QString filename = QFileDialog::getSaveFileName(
                this,tr("Save As...Document"),QDir::currentPath(),tr("png files (*.png )"),0,QFileDialog::DontUseNativeDialog);
 if(!filename.endsWith(".png"))
	{
		if(filename!="")
		{
            filename=filename+".png";
		}
		else
		{
			filename="";
		}
	}

	if( !filename.isNull())
	{
		QImage *image=new QImage(QSize(www,hhh),QImage::Format_ARGB32);
		QPainter *painter=new QPainter(image);


		scene->render(painter,QRectF(0,0,www+10,hhh+10),QRectF(-www/2,-hhh/2,www+10,hhh+10),Qt::KeepAspectRatio);
		image->save(filename);
		delete painter;
		delete image;
	}
}


void PLabel::on_actionAutoPos_triggered()
{
scene->autoSelectedItem();
}

void PLabel::on_actionTopAligment_triggered()
{
scene->autoBottomSelectedItem();
}

void PLabel::on_actionBackGroundColor_triggered()
{
	QColor color = QColorDialog::getColor(m_backgroundColor, this);
		if (color.isValid()) {
			m_root->setBrush(color);
			m_backgroundColor=color;
			scene->update();
		}
}

void PLabel::on_actionShowBorder_triggered()
{
 if(ui.actionShowBorder->isChecked())
 {
     scene->itemsShowGridBorderVisible();
 }
 else
 {
	 scene->itemsHideGridBorder();

 }
 scene->update();
}

void PLabel::on_actionItalic_triggered()
{

}

void PLabel::ChangeFontGraphicsFont()
{
	
	QFont m_sFont=scene->GetGpahicsFont();
	
	disconnect(&fontbox1,SIGNAL(currentFontChanged(const QFont &)),this,SLOT(ComboCurrentFontChanged(const QFont &)));
	fontbox1.setCurrentFont(m_sFont);
	connect(&fontbox1,SIGNAL(currentFontChanged(const QFont &)),this,SLOT(ComboCurrentFontChanged(const QFont &)));

	m_sFont.bold()?ui.actionFontBold->setChecked(true):ui.actionFontBold->setChecked(false);
	m_sFont.italic()?ui.actionItalic->setChecked(true):ui.actionItalic->setChecked(false);
	m_sFont.underline()?ui.actionUnderline->setChecked(true):ui.actionUnderline->setChecked(false);
	switch(m_sFont.pointSize())
	{
	case 4:fontSizeBox1.setCurrentIndex(0);break;
	case 5:fontSizeBox1.setCurrentIndex(1);break;
	case 6:fontSizeBox1.setCurrentIndex(2);break;
	case 7:fontSizeBox1.setCurrentIndex(3);break;
	case 8:fontSizeBox1.setCurrentIndex(4);break;
	case 9:fontSizeBox1.setCurrentIndex(5);break;
	case 10:fontSizeBox1.setCurrentIndex(6);break;
	case 11:fontSizeBox1.setCurrentIndex(7);break;
	case 12:fontSizeBox1.setCurrentIndex(8);break;
	case 13:fontSizeBox1.setCurrentIndex(9);break;
	case 14:fontSizeBox1.setCurrentIndex(10);break;
	case 15:fontSizeBox1.setCurrentIndex(11);break;
	case 16:fontSizeBox1.setCurrentIndex(12);break;
	case 17:fontSizeBox1.setCurrentIndex(13);break;
	case 18:fontSizeBox1.setCurrentIndex(14);break;
	case 19:fontSizeBox1.setCurrentIndex(15);break;
	case 20:fontSizeBox1.setCurrentIndex(16);break;
	case 21:fontSizeBox1.setCurrentIndex(17);break;
	case 22:fontSizeBox1.setCurrentIndex(18);break;
	case 23:fontSizeBox1.setCurrentIndex(19);break;
	case 24:fontSizeBox1.setCurrentIndex(20);break;
	case 25:fontSizeBox1.setCurrentIndex(21);break;
	case 26:fontSizeBox1.setCurrentIndex(22);break;
	case 27:fontSizeBox1.setCurrentIndex(23);break;
	case 28:fontSizeBox1.setCurrentIndex(24);break;
	case 29:fontSizeBox1.setCurrentIndex(25);break;
	case 30:fontSizeBox1.setCurrentIndex(26);break;
	case 31:fontSizeBox1.setCurrentIndex(27);break;
	case 32:fontSizeBox1.setCurrentIndex(28);break;
	case 33:fontSizeBox1.setCurrentIndex(29);break;
	case 34:fontSizeBox1.setCurrentIndex(30);break;
	case 35:fontSizeBox1.setCurrentIndex(31);break;
	case 36:fontSizeBox1.setCurrentIndex(32);break;
	case 37:fontSizeBox1.setCurrentIndex(33);break;
	case 38:fontSizeBox1.setCurrentIndex(34);break;
	case 39:fontSizeBox1.setCurrentIndex(35);break;
	case 40:fontSizeBox1.setCurrentIndex(36);break;
	case 41:fontSizeBox1.setCurrentIndex(37);break;
	case 42:fontSizeBox1.setCurrentIndex(38);break;
	case 43:fontSizeBox1.setCurrentIndex(39);break;
	case 44:fontSizeBox1.setCurrentIndex(40);break;
	case 45:fontSizeBox1.setCurrentIndex(41);break;
	case 46:fontSizeBox1.setCurrentIndex(42);break;
	case 47:fontSizeBox1.setCurrentIndex(43);break;
	case 48:fontSizeBox1.setCurrentIndex(44);break;
	case 49:fontSizeBox1.setCurrentIndex(45);break;
	case 50:fontSizeBox1.setCurrentIndex(46);break;
	case 51:fontSizeBox1.setCurrentIndex(47);break;
	case 52:fontSizeBox1.setCurrentIndex(48);break;
	case 53:fontSizeBox1.setCurrentIndex(49);break;
	case 54:fontSizeBox1.setCurrentIndex(50);break;
	case 55:fontSizeBox1.setCurrentIndex(51);break;
	case 56:fontSizeBox1.setCurrentIndex(52);break;
	case 57:fontSizeBox1.setCurrentIndex(53);break;
	case 58:fontSizeBox1.setCurrentIndex(54);break;
	case 59:fontSizeBox1.setCurrentIndex(55);break;
	case 60:fontSizeBox1.setCurrentIndex(56);break;
	case 61:fontSizeBox1.setCurrentIndex(57);break;
	case 62:fontSizeBox1.setCurrentIndex(58);break;
	case 63:fontSizeBox1.setCurrentIndex(59);break;
	case 64:fontSizeBox1.setCurrentIndex(60);break;
	case 65:fontSizeBox1.setCurrentIndex(61);break;
	case 66:fontSizeBox1.setCurrentIndex(62);break;
	case 67:fontSizeBox1.setCurrentIndex(63);break;
	case 68:fontSizeBox1.setCurrentIndex(64);break;
	case 69:fontSizeBox1.setCurrentIndex(65);break;
	case 70:fontSizeBox1.setCurrentIndex(66);break;
	case 71:fontSizeBox1.setCurrentIndex(67);break;
	case 72:fontSizeBox1.setCurrentIndex(68);break;
	case 73:fontSizeBox1.setCurrentIndex(69);break;
	case 74:fontSizeBox1.setCurrentIndex(70);break;
	case 75:fontSizeBox1.setCurrentIndex(71);break;
	case 76:fontSizeBox1.setCurrentIndex(72);break;
	case 77:fontSizeBox1.setCurrentIndex(73);break;
	case 78:fontSizeBox1.setCurrentIndex(74);break;
	case 79:fontSizeBox1.setCurrentIndex(75);break;
	case 80:fontSizeBox1.setCurrentIndex(76);break;
	case 81:fontSizeBox1.setCurrentIndex(77);break;
	case 82:fontSizeBox1.setCurrentIndex(78);break;
	case 83:fontSizeBox1.setCurrentIndex(79);break;
	case 84:fontSizeBox1.setCurrentIndex(80);break;
	case 85:fontSizeBox1.setCurrentIndex(81);break;
	case 86:fontSizeBox1.setCurrentIndex(82);break;
	case 87:fontSizeBox1.setCurrentIndex(83);break;
	case 88:fontSizeBox1.setCurrentIndex(84);break;
	case 89:fontSizeBox1.setCurrentIndex(85);break;
	case 90:fontSizeBox1.setCurrentIndex(86);break;
	case 91:fontSizeBox1.setCurrentIndex(87);break;
	case 92:fontSizeBox1.setCurrentIndex(88);break;
	case 93:fontSizeBox1.setCurrentIndex(89);break;
	case 94:fontSizeBox1.setCurrentIndex(90);break;
	case 95:fontSizeBox1.setCurrentIndex(91);break;
	case 96:fontSizeBox1.setCurrentIndex(92);break;
	case 97:fontSizeBox1.setCurrentIndex(93);break;
	case 98:fontSizeBox1.setCurrentIndex(94);break;
	case 99:fontSizeBox1.setCurrentIndex(95);break;
	}

}

void PLabel::on_actionHelp_2_triggered()
{
	QDesktopServices::openUrl(QUrl("http://www.prolabelcreator.com/doc/index.htm"));
}


void PLabel::on_actionAddShapeItem_triggered()
{
//        lrectItem=new QMyGraphicsRectItem(0);
//		QPointF m_initPos;
//		lrectItem->setRect(0,0,100,30);
//		m_initPos=QPointF(-150,0);
//		lrectItem->setPos(m_initPos);
//		scene->addItem(lrectItem);
}

void PLabel::on_actionadd_object_triggered()
{
	
}

void PLabel::on_actionaaa_triggered()
{
	on_actionAdd_GraphicsObject();
}
