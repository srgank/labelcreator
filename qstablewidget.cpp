#include "qstablewidget.h"
#include <QFileDialog>
#include <QDir>
#include <QStandardItem>
#include <QAbstractTableModel>
#include <QVector>
#include <QMouseEvent>
#include <QHeaderView>
#include <QMessageBox>

QSTableWidget::QSTableWidget(QWidget *parent)
: QTableWidget(parent)
{
	 m_tablechanged=false;
	 m_filename="";
	 this->horizontalHeader()->installEventFilter(this);
	 this->verticalHeader()->installEventFilter(this);

// 	 connect(reinterpret_cast<const QObject*>(horizontalHeader()),SIGNAL(sectionClicked(int )()),this,SLOT(proba(int)));
// 	 horizontalHeader()->setContextMenuPolicy(Qt::CustomContextMenu);
// 	 connect((QObject*) this->horizontalHeader(),SIGNAL(customContextMenuRequested(const QPoint& aPosition)),
// 		 this, SLOT(treeContextMenu(const QPoint& aPosition)));

// 	 connect ( (QObject*) this->horizontalHeader(), SIGNAL( sectionClicked(int) ), this, SLOT(proba(int)));
	 setMouseTracking(true); 
}

QSTableWidget::~QSTableWidget()
{

}

//bool QSTableWidget::eventFilter( QObject *obj, QEvent *ev )
//{
//	if ( obj == this->horizontalHeader() ) {
//		if ( ev->type() == QEvent::ContextMenu )
//		{
//			QPoint s;
//			pos();
//			emit sendMouseRightClick1(s);

//            return true;
//		} else {
//            return false;
//		}
//	}
//	else if ( obj == this->verticalHeader() ) {
//		if ( ev->type() == QEvent::ContextMenu )
//		{
//			QPoint s;
//			pos();
//			emit sendMouseRightClick1(s);

//            return true;
//		} else {
//            return false;
//		}
//	}
//	else
//	{
//		return QSTableWidget::eventFilter( obj, ev );
//	}
//}



void QSTableWidget::setGeometry ( const QRect &r)
{
	QTableWidget::setGeometry(r);
}
void QSTableWidget::show()
{
	QTableWidget::show();
}

void QSTableWidget::setFont( const QFont & f)
{
	QTableWidget::setFont(f);
}
void QSTableWidget::showDBD()
{
	int row=0;
	loadRecordsFromFile();
	QTableWidget::setUpdatesEnabled(false);
	int wrows=1;
	int wcols=12;
	QString m_rowHeightInfo;
	QString m_colWidthInfo;
	
	
	if(mdb_element_new.count()!=0)
	{
	for(idb_hdr=mdb_hdr.begin();idb_hdr<mdb_hdr.end();idb_hdr++)
	{
		wcols=((*idb_hdr)->m_cols_count);
		wrows=((*idb_hdr)->m_rows_count);
		m_rowPreview=((*idb_hdr)->m_preview_rows);
		m_colPreview=((*idb_hdr)->m_preview_cols);
		m_rowHeightInfo=((*idb_hdr)->rowHeightInfo);
		m_colWidthInfo=((*idb_hdr)->colWidthInfo);
		m_xyInfo=((*idb_hdr)->lxyInfo); //here
		cl_backGroundColor=((*idb_hdr)->lbackGroundColor);
	}
	setColumnCount(wcols);
	setRowCount(wrows);
	QStringList m_rowHeightInfoList=m_rowHeightInfo.split(",");
	QStringList m_colWidthInfoList=m_colWidthInfo.split(",");
	
	int rh=0;
	int cw=0;
	if(mdb_element_new.count()!=0)
	{
	
	for(int r=0;r<wrows;r++)
	{
		for(int c=0;c<wcols;c++)
		{
			setItem(r,c,new QTableWidgetItem(mdb_element_new.at(r*wcols+c)->m_cell_desc));
			item(r,c)->setFont(mdb_element_new.at(r*wcols+c)->m_cell_font);
			cw=m_colWidthInfoList.at(c).toInt(0,10);
			if(cw==0)
			{
				setColumnWidth(c,100);
			}
			else
			{
				setColumnWidth(c,m_colWidthInfoList.at(c).toInt(0,10));
			}
		}
		rh=m_rowHeightInfoList.at(r).toInt(0,10);
		if(rh==0)
		{
			setRowHeight(r,18);
		}
		else
		{
			setRowHeight(r,m_rowHeightInfoList.at(r).toInt(0,10));
		}

	}
	}
	else
	{
		for(int r=0;r<wrows;r++)
		{
			for(int c=0;c<wcols;c++)
			{
				if(c==(wcols-1))
				{
					setItem(r,c,new QTableWidgetItem("1"));
				}
				else
				{
					setItem(r,c,new QTableWidgetItem(""));
				}
				cw=m_colWidthInfoList.at(c).toInt(0,10);
				if(cw==0)
				{
					setColumnWidth(c,100);
				}
				else
				{
					setColumnWidth(c,m_colWidthInfoList.at(c).toInt(0,10));
				}
			}
			rh=m_rowHeightInfoList.at(r).toInt(0,10);
			if(rh==0)
			{
				setRowHeight(r,18);
			}
			else
			{
				setRowHeight(r,m_rowHeightInfoList.at(r).toInt(0,10));
			}
		}
	}
	QTableWidget::setUpdatesEnabled(true);
	show();
	}
}

void QSTableWidget::showDBDExtended(QString filename)
{
	int row=0;
	loadRecordsFromFileExtended(filename);
	QTableWidget::setUpdatesEnabled(false);
	int wrows=1;
	int wcols=12;
	QString m_rowHeightInfo;
	QString m_colWidthInfo;
	
	if(mdb_element_new.count()!=0)
	{
		for(idb_hdr=mdb_hdr.begin();idb_hdr<mdb_hdr.end();idb_hdr++)
		{
			wcols=((*idb_hdr)->m_cols_count);
			wrows=((*idb_hdr)->m_rows_count);
			m_rowPreview=((*idb_hdr)->m_preview_rows);
			m_colPreview=((*idb_hdr)->m_preview_cols);
			m_rowHeightInfo=((*idb_hdr)->rowHeightInfo);
			m_colWidthInfo=((*idb_hdr)->colWidthInfo);
			m_xyInfo=((*idb_hdr)->lxyInfo);
			cl_backGroundColor=((*idb_hdr)->lbackGroundColor);
		}
		setColumnCount(wcols);
		setRowCount(wrows);
		QStringList m_rowHeightInfoList=m_rowHeightInfo.split(",");
		QStringList m_colWidthInfoList=m_colWidthInfo.split(",");
		int rh=0;
		int cw=0;
		if(mdb_element_new.count()!=0)
		{

			for(int r=0;r<wrows;r++)
			{
				for(int c=0;c<wcols;c++)
				{
					setItem(r,c,new QTableWidgetItem(mdb_element_new.at(r*wcols+c)->m_cell_desc));
					item(r,c)->setFont(mdb_element_new.at(r*wcols+c)->m_cell_font);
					cw=m_colWidthInfoList.at(c).toInt(0,10);
					if(cw==0)
					{
						setColumnWidth(c,100);
					}
					else
					{
						setColumnWidth(c,m_colWidthInfoList.at(c).toInt(0,10));
					}
				}
				rh=m_rowHeightInfoList.at(r).toInt(0,10);
				if(rh==0)
				{
					setRowHeight(r,18);
				}
				else
				{
					setRowHeight(r,m_rowHeightInfoList.at(r).toInt(0,10));
				}

			}
		}
		else
		{
			for(int r=0;r<wrows;r++)
			{
				for(int c=0;c<wcols;c++)
				{
					if(c==(wcols-1))
					{
						setItem(r,c,new QTableWidgetItem("1"));
					}
					else
					{
						setItem(r,c,new QTableWidgetItem(""));
					}
					cw=m_colWidthInfoList.at(c).toInt(0,10);
					if(cw==0)
					{
						setColumnWidth(c,100);
					}
					else
					{
						setColumnWidth(c,m_colWidthInfoList.at(c).toInt(0,10));
					}
				}
				rh=m_rowHeightInfoList.at(r).toInt(0,10);
				if(rh==0)
				{
					setRowHeight(r,18);
				}
				else
				{
					setRowHeight(r,m_rowHeightInfoList.at(r).toInt(0,10));
				}
			}
		}
		QTableWidget::setUpdatesEnabled(true);
		show();
	}
}

void QSTableWidget::addItemsDBD(int maxrow,int m_cnt,int m_column)
{
int row=maxrow;
QTableWidget::setUpdatesEnabled(false);
setRowCount(row+m_cnt);
	for(int e=0;e<m_cnt;e++)
	{
		for(int ccc=0;ccc<m_column;ccc++)
		{
			if(ccc==(m_column-1))
			{
			 setItem(row, ccc,new QTableWidgetItem("1"));
			}
			else
			{
			 setItem(row, ccc,new QTableWidgetItem(""));
			}
			
		}
		setRowHeight(row,18);
		row++;
	}
	QTableWidget::setUpdatesEnabled(true);
	setRowCount(row);
}


void QSTableWidget::CopyTableToDBD()
{

    mdb_hdr.clear();
    QTableWidget::setUpdatesEnabled(false);
	QStringList m_columnInfos;
	m_columnInfos.clear();
	QString aaa3="";
	for(int m_col=0;m_col<columnCount();m_col++)
	{
		aaa3=QString::number(columnWidth(m_col), 10);
		m_columnInfos<<aaa3;
	}
	QStringList m_rowInfos;
	m_rowInfos.clear();
	for(int m_row=0;m_row<rowCount();m_row++)
	{
		m_rowInfos<<QString::number(rowHeight(m_row), 10);
	}


	element_hdr=new db_header;
	element_hdr->magic_id=0;	
	element_hdr->m_rows_count=rowCount();
	element_hdr->m_cols_count=columnCount();
	element_hdr->m_preview_rows=m_rowPreview;
	element_hdr->m_preview_cols=m_colPreview;
	element_hdr->colWidthInfo=m_columnInfos.join(",");
	element_hdr->rowHeightInfo=m_rowInfos.join(",");

	element_hdr->lxyInfo=m_xy_info1;
	element_hdr->lbackGroundColor=cl_backGroundColor;

	mdb_hdr.push_back(element_hdr);
	mdb_element_new.clear();
	for(int row_i=0;row_i<rowCount();row_i++)
	{
		for(int col_i=0;col_i<columnCount();col_i++)
		{
		 element_new=new db_element_new;
		 element_new->m_cell_desc=item(row_i,col_i)->text();	
		 element_new->m_cell_font=item(row_i,col_i)->font();
		 mdb_element_new.push_back(element_new);
        }
	}
	QTableWidget::setUpdatesEnabled(true);
// 	saveRecordsToFile();
}

QString QSTableWidget::getCurrentA1()
{
	return item(currentRow(),0)->text();
}

QString QSTableWidget::getCurrentB1()
{
	return item(currentRow(),1)->text();
}

QString QSTableWidget::getCurrentC1()
{
	return item(currentRow(),2)->text();
}

QString QSTableWidget::getCurrentD1()
{
	return item(currentRow(),3)->text();
}
QString QSTableWidget::getCurrentA2()
{
	return item(currentRow(),4)->text();
}
QString QSTableWidget::getCurrentB2()
{
	return item(currentRow(),5)->text();
}
QString QSTableWidget::getCurrentC2()
{
	return item(currentRow(),6)->text();
}
QString QSTableWidget::getCurrentD2()
{
	return item(currentRow(),7)->text();
}

void QSTableWidget::CopySaveAsTableToDBD()
{
	mdb_hdr.clear();
	QTableWidget::setUpdatesEnabled(false);

	QStringList m_columnInfos;
	m_columnInfos.clear();
	for(int m_col=0;m_col<columnCount();m_col++)
	{
		m_columnInfos<<QString::number(columnWidth(m_col), 10);
	}
	QStringList m_rowInfos;
	m_rowInfos.clear();
	for(int m_row=0;m_row<rowCount();m_row++)
	{
		m_rowInfos<<QString::number(rowHeight(m_row), 10);
	}


	element_hdr=new db_header;
	element_hdr->magic_id=0;	
	element_hdr->m_rows_count=rowCount();
	element_hdr->m_cols_count=columnCount();
	element_hdr->m_preview_rows=m_rowPreview;
	element_hdr->m_preview_cols=m_colPreview;
	element_hdr->colWidthInfo=m_columnInfos.join(",");
	element_hdr->rowHeightInfo=m_rowInfos.join(",");
	element_hdr->lxyInfo=m_xy_info1;
	element_hdr->lbackGroundColor=cl_backGroundColor;

	mdb_hdr.push_back(element_hdr);
	mdb_element_new.clear();
	for(int row_i=0;row_i<rowCount();row_i++)
	{
	  for(int col_i=0;col_i<columnCount();col_i++)
	  {
		element_new=new db_element_new;
		element_new->m_cell_desc=item(row_i,col_i)->text();	
		element_new->m_cell_font=item(row_i,col_i)->font();
		mdb_element_new.push_back(element_new);
	  } 
   }
	QTableWidget::setUpdatesEnabled(true);
/*	saveAsRecordsToFile();*/
}

QWidget * QSTableWidget::focusWidget()
{
	return QTableWidget::focusWidget();
}

bool QSTableWidget::isSTableChanged()
{
	if(rowCount()!=1)
	{
		m_tablechanged=true;
	}
	else
	{
		m_tablechanged=false;
	}
	return m_tablechanged;
}

int QSTableWidget::findSTableItems(QString m_findString)
{
	m_find_item_count=0;
	m_find=selectedItems();
	for(i_find=m_find.begin();i_find<m_find.end();i_find++)
	{
		(*i_find)->setSelected(false);
	}
	m_find=findItems(m_findString,Qt::MatchContains);
	return m_find.count();
}

int QSTableWidget::findNextSTableItems()
{
	int k_found=-1;
	int stat_found=0;
	if(!0)
	{
		m_find_item_count++;
		int k=1;	
		for(i_find=m_find.begin();i_find<m_find.end();i_find++)
		{
			if(m_find_item_count==k)
			{
				(*i_find)->setSelected(true);
				setCurrentCell((*i_find)->row(),(*i_find)->column());
				stat_found=1;
				k_found=k;
				break;
			}
			k++;
		}
	}
	if(!stat_found)
	{
	m_find_item_count--;
	}
	return k_found;
}

int QSTableWidget::findPreviousSTableItems()
{
	int k_found=-1;
	int stat_found=0;
	if(!(0))
	{
		m_find_item_count--;
		int k=1;	
		for(i_find=m_find.begin();i_find<m_find.end();i_find++)
		{
			if(m_find_item_count==k)
			{
				(*i_find)->setSelected(true);
				setCurrentCell((*i_find)->row(),(*i_find)->column());
				stat_found=1;
				k_found=k;
				break;
			}
			k++;
		}
	}
	if(!stat_found)
	{
		m_find_item_count++;
	}
	return k_found;
}

void QSTableWidget::removeSelectedSItems()
{
	setUpdatesEnabled(false);
	QList<QTableWidgetSelectionRange> mx;
	QList<QTableWidgetSelectionRange>::iterator ix;
	int m_arow,m_brow,m_acol,m_bcol;

	mx=selectedRanges();
	if(mx.count()>0)
	{
		ix=mx.begin();
		m_arow=(*ix).topRow();
		m_brow=(*ix).bottomRow();
		m_acol=(*ix).leftColumn();
		m_bcol=(*ix).rightColumn();
		for(int irow=m_brow;irow>m_arow-1;irow--)
		{
			removeRow(irow);
		}
	}
	setUpdatesEnabled(true);
}

/*
void QSTableWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::RightButton) 
	{
		QPoint s;
		s=event->pos();
		emit sendMouseRightClick1(s);
	}
	QTableWidget::mousePressEvent(event);
}
*/
void QSTableWidget::treeContextMenu(const QPoint& aPosition)
{
	int iii=0;
	iii++;
}

void QSTableWidget::contextMenuEvent(QContextMenuEvent *event)
{
	QPoint s;
	s=event->pos();
	emit sendMouseRightClick1(s);
	QTableWidget::contextMenuEvent(event);
}
//////////////////////////////////////////////////////////////////


void QSTableWidget::loadRecordsFromFile()
{
	QString filename = QFileDialog::getOpenFileName(
		this,tr("Open Document"),QDir::currentPath(),tr("Lsw files (*.lsw)"),0,QFileDialog::DontUseNativeDialog);
	if(!filename.endsWith(".lsw"))
	{
	filename=filename+".lsw";
	}
	if(filename!=".lsw")
	{	
		QFile file( filename);
		m_filename=filename;
		if( !file.open( QIODevice::ReadOnly ) )
			return;
		QDataStream stream( &file );
		stream.setVersion( QDataStream::Qt_4_2 );
		int lmagic_id;
		int lm_rows_count;
		int lm_cols_count;
		int lm_preview_rows;
		int lm_preview_cols;
		QString lrowHeightInfo;
		QString lcolWidthInfo;
		QString lxyInfo;
		QColor lbackGroundColor;
		


		stream >> lmagic_id;
		if(lmagic_id!=12084691)
		{
			QMessageBox::warning(this,
				"",
				"File is not valid.<br />"
				,QMessageBox::Ok);
			return;
		}
		stream >> lm_rows_count;
		stream >> lm_cols_count;
		stream >> lm_preview_rows;
		stream >> lm_preview_cols;

		stream >> lrowHeightInfo;
		stream >> lcolWidthInfo;
		stream >> lxyInfo;
		stream >> lbackGroundColor;

		mdb_hdr.clear();
		element_hdr=new db_header;
		element_hdr->magic_id=lmagic_id;
		element_hdr->m_rows_count=lm_rows_count;
		element_hdr->m_cols_count=lm_cols_count;

		element_hdr->m_preview_rows=lm_preview_rows;
		element_hdr->m_preview_cols=lm_preview_cols;

		element_hdr->rowHeightInfo=lrowHeightInfo;
		element_hdr->colWidthInfo=lcolWidthInfo;
		element_hdr->lxyInfo=lxyInfo;
		element_hdr->lbackGroundColor=lbackGroundColor;

		mdb_hdr.push_back(element_hdr);

		mdb_element_new.clear(); 

//		while(!stream.atEnd())
		for(int i=0;i<lm_rows_count*lm_cols_count;i++)
		{
			stream >>m_label_cell;
			stream >>m_font_cell;
			stream >>m_color;
			stream >>m_graph_font;
			stream >>m_rotate;

			element_new=new db_element_new;
			element_new->m_rotate=0.0f;
			element_new->m_cell_desc=m_label_cell;
			element_new->m_cell_font=m_font_cell;
			element_new->m_color=m_color;
			element_new->m_graph_font=m_graph_font;
			element_new->m_rotate=m_rotate;
			mdb_element_new.push_back(element_new);
		}

		mdb_element_ImageInfo.clear(); 
		while(!stream.atEnd())
		{
			stream >> m_image_id;
			stream >> m_image_tip;
			stream >> m_image_x;
			stream >> m_image_y; 
			stream >> m_image_data;
			stream >> m_scale;
			stream >> m_scale_w;
			element_ImageInfo=new db_ImageInfo;
			element_ImageInfo->id=m_image_id;
			element_ImageInfo->tip=m_image_tip;
			element_ImageInfo->m_x=m_image_x;
			element_ImageInfo->m_y=m_image_y;
			element_ImageInfo->m_data=m_image_data;
			element_ImageInfo->m_scale=m_scale;
			element_ImageInfo->m_scale_w=m_scale_w;
			mdb_element_ImageInfo.push_back(element_ImageInfo);
		}		


		file.close();
	}
	else
	{
		
	}
}

void QSTableWidget::saveRecordsToFile()
{
	QFile file( m_filename);
	if( !file.open( QIODevice::WriteOnly ) )
		return;
	QDataStream stream( &file );
	stream.setVersion(QDataStream::Qt_4_2);
	element_hdr->magic_id=12084691;
	stream << element_hdr->magic_id;
	stream << element_hdr->m_rows_count;
	stream << element_hdr->m_cols_count;
	stream << element_hdr->m_preview_rows;
	stream << element_hdr->m_preview_cols;
	stream << element_hdr->rowHeightInfo;
	stream << element_hdr->colWidthInfo;
	stream << element_hdr->lxyInfo;
	stream << element_hdr->lbackGroundColor;


	for(idb_element_new=mdb_element_new.begin();idb_element_new<mdb_element_new.end();idb_element_new++)
	{
		stream <<(*idb_element_new)->m_cell_desc;
		stream <<(*idb_element_new)->m_cell_font;
		stream <<(*idb_element_new)->m_color;
		stream <<(*idb_element_new)->m_graph_font;
		stream <<(*idb_element_new)->m_rotate;
	}


	for(idb_element_ImageInfo=mdb_element_ImageInfo.begin();idb_element_ImageInfo<mdb_element_ImageInfo.end();idb_element_ImageInfo++)
	{
		stream <<(*idb_element_ImageInfo)->id;
		stream <<(*idb_element_ImageInfo)->tip;
		stream <<(*idb_element_ImageInfo)->m_x;
		stream <<(*idb_element_ImageInfo)->m_y;
		stream <<(*idb_element_ImageInfo)->m_data;
		stream <<(*idb_element_ImageInfo)->m_scale;
		stream <<(*idb_element_ImageInfo)->m_scale_w;
	}

	file.close();
}

void QSTableWidget::saveAsRecordsToFile()
{
	QString filename = QFileDialog::getSaveFileName(
		this,tr("Save As...Document"),QDir::currentPath(),tr("Lsw files (*.lsw)"),0,QFileDialog::DontUseNativeDialog);
	if(!filename.endsWith(".lsw"))
	{
		if(filename!="")
		{
			filename=filename+".lsw";
		}
		else
		{
			filename="";
		}
	}

	if( !filename.isNull())
	{	
		QFile file( filename);
		if( !file.open( QIODevice::WriteOnly ) )
			return;
		QDataStream stream( &file );
		m_filename=filename;
		stream.setVersion(QDataStream::Qt_4_2);
		element_hdr->magic_id=12084691;	
		stream << element_hdr->magic_id;
		stream << element_hdr->m_rows_count;
		stream << element_hdr->m_cols_count;
		stream << element_hdr->m_preview_rows;
		stream << element_hdr->m_preview_cols;
		stream << element_hdr->rowHeightInfo;
		stream << element_hdr->colWidthInfo;
		stream << element_hdr->lxyInfo;
		stream << element_hdr->lbackGroundColor;
		for(idb_element_new=mdb_element_new.begin();idb_element_new<mdb_element_new.end();idb_element_new++)
		{
		stream <<(*idb_element_new)->m_cell_desc;
		stream <<(*idb_element_new)->m_cell_font;
		stream <<(*idb_element_new)->m_color;
		stream <<(*idb_element_new)->m_graph_font;
		stream <<(*idb_element_new)->m_rotate;
		}
		for(idb_element_ImageInfo=mdb_element_ImageInfo.begin();idb_element_ImageInfo<mdb_element_ImageInfo.end();idb_element_ImageInfo++)
		{
			stream <<(*idb_element_ImageInfo)->id;
			stream <<(*idb_element_ImageInfo)->tip;
			stream <<(*idb_element_ImageInfo)->m_x;
			stream <<(*idb_element_ImageInfo)->m_y;
			stream <<(*idb_element_ImageInfo)->m_data;
			stream <<(*idb_element_ImageInfo)->m_scale;
			stream <<(*idb_element_ImageInfo)->m_scale_w;
		}

		file.close();
	}
}
bool QSTableWidget::fExistFileName()
{
	return m_filename!=""? true:false;
}

QString QSTableWidget::getFileName()
{
	return m_filename;
}


void QSTableWidget::loadRecordsFromFileExtended(QString filename)
{
	QFile file( filename);
	m_filename=filename;
	if( !file.open( QIODevice::ReadOnly ) )
	return;
	QDataStream stream( &file );
	stream.setVersion( QDataStream::Qt_4_2 );
	int lmagic_id;
	int lm_rows_count;
	int lm_cols_count;
	int lm_preview_rows;
	int lm_preview_cols;
	QString lrowHeightInfo;
	QString lcolWidthInfo;
	QString lxyInfo;
	QColor lbackGroundColor;



	stream >> lmagic_id;
	if(lmagic_id!=12084691)
	{
		QMessageBox::warning(this,
			"",
			"File is not valid.<br />"
			,QMessageBox::Ok);
		return;
	}
	stream >> lm_rows_count;
	stream >> lm_cols_count;
	stream >> lm_preview_rows;
	stream >> lm_preview_cols;

	stream >> lrowHeightInfo;
	stream >> lcolWidthInfo;
	stream >> lxyInfo;
	stream >> lbackGroundColor;

	mdb_hdr.clear();
	element_hdr=new db_header;
	element_hdr->magic_id=lmagic_id;
	element_hdr->m_rows_count=lm_rows_count;
	element_hdr->m_cols_count=lm_cols_count;

	element_hdr->m_preview_rows=lm_preview_rows;
	element_hdr->m_preview_cols=lm_preview_cols;

	element_hdr->rowHeightInfo=lrowHeightInfo;
	element_hdr->colWidthInfo=lcolWidthInfo;
	element_hdr->lxyInfo=lxyInfo;
	element_hdr->lbackGroundColor=lbackGroundColor;
	mdb_hdr.push_back(element_hdr);

	mdb_element_new.clear(); 
	//while(!stream.atEnd())
	for(int i=0;i<lm_rows_count*lm_cols_count;i++)
	{
		stream >>m_label_cell;
		stream >>m_font_cell;
		stream >>m_color;
		stream >>m_graph_font;
		stream >>m_rotate;

		element_new=new db_element_new;
		element_new->m_rotate=0.0f;
		element_new->m_cell_desc=m_label_cell;
		element_new->m_cell_font=m_font_cell;
		element_new->m_color=m_color;
		element_new->m_graph_font=m_graph_font;
		element_new->m_rotate=m_rotate;
		mdb_element_new.push_back(element_new);
	}

	mdb_element_ImageInfo.clear(); 
	while(!stream.atEnd())
	{
		stream >> m_image_id;
		stream >> m_image_tip;
		stream >> m_image_x;
		stream >> m_image_y; 
		stream >> m_image_data;
		stream >> m_scale;
		stream >> m_scale_w;

		element_ImageInfo=new db_ImageInfo;
		element_ImageInfo->id=m_image_id;
		element_ImageInfo->tip=m_image_tip;
		element_ImageInfo->m_x=m_image_x;
		element_ImageInfo->m_y=m_image_y;
		element_ImageInfo->m_data=m_image_data;
		element_ImageInfo->m_scale=m_scale;
		element_ImageInfo->m_scale_w=m_scale_w;
		mdb_element_ImageInfo.push_back(element_ImageInfo);
	}		

	file.close();
}

void QSTableWidget::ccsignal(QPoint s)
{
}

void QSTableWidget::removeSelectedSColumn(int &leftcol,int &rightcol)
{
	setUpdatesEnabled(false);
	QList<QTableWidgetSelectionRange> mx;
	QList<QTableWidgetSelectionRange>::iterator ix;
	int m_arow,m_brow,m_acol,m_bcol;

	mx=selectedRanges();
	if(mx.count()>0)
	{
		ix=mx.begin();
		m_arow=(*ix).topRow();
		m_brow=(*ix).bottomRow();
		m_acol=(*ix).leftColumn();
		m_bcol=(*ix).rightColumn();
		if(m_acol==0)
		{
		m_acol=0;
		}
		if(m_bcol==columnCount()-1)
		{
			m_bcol--;
		}

		for(int icol=m_bcol;icol>m_acol-1;icol--)
		{
			removeColumn(icol);
		}
	}
	setUpdatesEnabled(true);
	leftcol=m_acol;
	rightcol=m_bcol;
}


void QSTableWidget::concatenateSelectedSColumn()
{
	setUpdatesEnabled(false);
	QList<QTableWidgetSelectionRange> mx;
	QList<QTableWidgetSelectionRange>::iterator ix;
	int m_arow,m_brow,m_acol,m_bcol;

	mx=selectedRanges();
	if(mx.count()>0)
	{
		ix=mx.begin();
		m_arow=(*ix).topRow();
		m_brow=(*ix).bottomRow();
		m_acol=(*ix).leftColumn();
		m_bcol=(*ix).rightColumn();
		QString m_concatenate_string="";
		if(m_acol==0)
		{
			m_acol=0;
		}
		if(m_bcol==columnCount()-1)
		{
			m_bcol--;
		}
		for(int irow=m_arow;irow<m_brow+1;irow++)
		{
			for(int icol=m_acol;icol<m_bcol+1;icol++)
			{
				m_concatenate_string=m_concatenate_string+item(irow,icol)->text().trimmed()+" ";
				if(icol>m_acol)
				{
					item(irow,icol)->setText("");
				}
			}
			item(irow,m_acol)->setText(m_concatenate_string.trimmed());
			m_concatenate_string="";
		}
	}
	setUpdatesEnabled(true);
}


void QSTableWidget::expandSelectedSColumn()
{
	setUpdatesEnabled(false);
	QList<QTableWidgetSelectionRange> mx;
	QList<QTableWidgetSelectionRange>::iterator ix;
	int m_arow,m_brow,m_acol,m_bcol;

	mx=selectedRanges();
	if(mx.count()>0)
	{
		ix=mx.begin();
		m_arow=(*ix).topRow();
		m_brow=(*ix).bottomRow();
		m_acol=(*ix).leftColumn();
		m_bcol=(*ix).rightColumn();
		QString m_concatenate_string="";
		if(m_acol==0)
		{
			m_acol=0;
		}
		if(m_bcol==columnCount()-1)
		{
			m_bcol--;
		}
		for(int irow=m_arow;irow<m_brow+1;irow++)
		{
			QStringList list2 = item(irow,m_acol)->text().trimmed().split(" ", QString::KeepEmptyParts);
			int m_string_count_all=list2.count();
			int m_string_character_count_all=item(irow,m_acol)->text().length()+m_string_count_all-1;
			int m_string_count=m_string_count_all/(m_bcol+1-m_acol);
			int m_string_character_count=m_string_character_count_all/(m_bcol+1-m_acol);
			int ii=0;
			if((m_string_count_all<(m_bcol+1-m_acol))||(m_string_count_all==(m_bcol+1-m_acol)))
			{
				mdb_element_expand.clear();
				for(int icol=m_acol;icol<m_bcol+1;icol++)
				{
				if((icol-m_acol)<list2.count())
				{
					element_expand=new db_element_expand;
					element_expand->erow=irow;
					element_expand->ecol=icol;
					element_expand->epos=0;
					element_expand->e_description=list2.at(icol-m_acol);
					mdb_element_expand.push_back(element_expand);
				}
				}
				for(idb_element_expand=mdb_element_expand.begin();idb_element_expand<mdb_element_expand.end();idb_element_expand++)
				{
					item((*idb_element_expand)->erow,(*idb_element_expand)->ecol)->setText((*idb_element_expand)->e_description);
				}
				mdb_element_expand.clear();
			}
			else
			{
				for(int icol=m_acol;icol<m_bcol+1;icol++)
				{
					if(icol==m_acol)
					{
						int m_length=0;
						QString m_str1="";
						for(int i=0;i<m_string_count_all;i++)
						{
							m_length=m_length+list2.at(i).length();
							if(m_length<m_string_character_count)
							{
								m_str1=m_str1+list2.at(i).trimmed()+" ";
								ii=i+1;
							}
							else
							{
								m_length=0;
								ii=i;
								i=m_string_count_all;
							}
						}
						m_str1.trimmed();
						item(irow,icol)->setText(m_str1);
					}
					else if(icol<m_bcol)
					{
						int m_length=0;
						QString m_str1="";
						for(int i=ii;i<m_string_count_all;i++)
						{
							if(i<list2.count())
							{
								m_length=m_length+list2.at(i).length();
								if(m_length<m_string_character_count)
								{
									m_str1=m_str1+list2.at(i).trimmed()+" ";
									ii=i+1;
								}
								else
								{
									m_length=0;
									ii=i;
									i=m_string_count_all;
								}
							}
						}
						m_str1.trimmed();
						item(irow,icol)->setText(m_str1);
					}
					else if(icol==m_bcol)
					{
						int m_length=0;
						QString m_str1="";
						for(int i=ii;i<m_string_count_all;i++)
						{
							if(i<list2.count())
							{
								m_length=m_length+list2.at(i).length();
									m_str1=m_str1+list2.at(i).trimmed()+" ";
							}
						}
						m_str1.trimmed();
						item(irow,icol)->setText(m_str1);
					}

				}
			}
			setUpdatesEnabled(true);
		}
	}
}

void QSTableWidget::save_to_undo()
{
copyundo_status=1;
mdb_hdr_undo.clear();
QTableWidget::setUpdatesEnabled(false);

element_hdr_undo=new db_header;
element_hdr_undo->magic_id=0;	
element_hdr_undo->m_rows_count=rowCount();
element_hdr_undo->m_cols_count=columnCount();
element_hdr_undo->m_preview_rows=0;
element_hdr_undo->m_preview_cols=0;
mdb_hdr_undo.push_back(element_hdr_undo);
mdb_element_new_undo.clear();
for(int row_i=0;row_i<rowCount();row_i++)
{
	for(int col_i=0;col_i<columnCount();col_i++)
	{
		element_new_undo=new db_element_new;
		element_new_undo->m_cell_desc=item(row_i,col_i)->text();	
		element_new_undo->m_cell_font=item(row_i,col_i)->font();
		mdb_element_new_undo.push_back(element_new_undo);
	}
}
QTableWidget::setUpdatesEnabled(true);
}

void QSTableWidget::undo()
{
	int row=0;
	QTableWidget::setUpdatesEnabled(false);
	if(copyundo_status==1)
	{
		int wcols=(element_hdr_undo->m_cols_count);
		int	wrows=(element_hdr_undo->m_rows_count);
	setColumnCount(wcols);
	setRowCount(wrows);
	if(mdb_element_new_undo.count()!=0)
	{

		for(int r=0;r<wrows;r++)
		{
			for(int c=0;c<wcols;c++)
			{
				setItem(r,c,new QTableWidgetItem(mdb_element_new_undo.at(r*wcols+c)->m_cell_desc));
				item(r,c)->setFont(mdb_element_new_undo.at(r*wcols+c)->m_cell_font);
				setRowHeight(r,18);
			}
		}
	}
	else
	{
		for(int r=0;r<wrows;r++)
		{
			for(int c=0;c<wcols;c++)
			{
				if(c==(wcols-1))
				{
					setItem(r,c,new QTableWidgetItem("1"));
				}
				else
				{
					setItem(r,c,new QTableWidgetItem(""));
				}
				setRowHeight(r,18);
			}
		}
	}
	}
	QTableWidget::setUpdatesEnabled(true);
	show();
	copyundo_status=0;
}

void QSTableWidget::removeSelectedEmptyRows()
{
	setUpdatesEnabled(false);
	QList<QTableWidgetSelectionRange> mx;
	QList<QTableWidgetSelectionRange>::iterator ix;
	int m_arow,m_brow,m_acol,m_bcol;

	mx=selectedRanges();
	if(mx.count()>0)
	{
		ix=mx.begin();
		m_arow=(*ix).topRow();
		m_brow=(*ix).bottomRow();
		m_acol=(*ix).leftColumn();
		m_bcol=(*ix).rightColumn();
		if(m_bcol==columnCount()-1)
		{
			m_bcol--;
		}
		for(int irow=m_brow;irow>m_arow-1;irow--)
		{
			QString m_r_empty="";
			for(int icol=m_acol;icol<m_bcol+1;icol++)
			{
			 m_r_empty=m_r_empty+item(irow,icol)->text();
			}
			if(m_r_empty=="")
			{
			removeRow(irow);
			}
		}
	}
	setUpdatesEnabled(true);
}


void QSTableWidget::concatenateSelectedSRows()
{
	setUpdatesEnabled(false);
	QList<QTableWidgetSelectionRange> mx;
	QList<QTableWidgetSelectionRange>::iterator ix;
	int m_arow,m_brow,m_acol,m_bcol;

	mx=selectedRanges();
	if(mx.count()>0)
	{
		ix=mx.begin();
		m_arow=(*ix).topRow();
		m_brow=(*ix).bottomRow();
		m_acol=(*ix).leftColumn();
		m_bcol=(*ix).rightColumn();
		QString m_concatenate_string="";
		if(m_acol==0)
		{
			m_acol=0;
		}
		if(m_bcol==columnCount()-1)
		{
			m_bcol--;
		}
		for(int icol=m_acol;icol<m_bcol+1;icol++)
		{
			for(int irow=m_arow;irow<m_brow+1;irow++)
			{
				m_concatenate_string=m_concatenate_string+item(irow,icol)->text().trimmed()+" ";
				if(irow>m_arow)
				{
					item(irow,icol)->setText("");
				}
			}
			item(m_arow,icol)->setText(m_concatenate_string.trimmed());
			m_concatenate_string="";
		}
	}
	setUpdatesEnabled(true);
}


void QSTableWidget::expandSelectedSRows()
{
	setUpdatesEnabled(false);
	QList<QTableWidgetSelectionRange> mx;
	QList<QTableWidgetSelectionRange>::iterator ix;
	int m_arow,m_brow,m_acol,m_bcol;

	mx=selectedRanges();
	if(mx.count()>0)
	{
		ix=mx.begin();
		m_arow=(*ix).topRow();
		m_brow=(*ix).bottomRow();
		m_acol=(*ix).leftColumn();
		m_bcol=(*ix).rightColumn();
		QString m_concatenate_string="";
		if(m_acol==0)
		{
			m_acol=0;
		}
		if(m_bcol==columnCount()-1)
		{
			m_bcol--;
		}
		for(int icol=m_acol;icol<m_bcol+1;icol++)
		{
			QStringList list2 = item(m_arow,icol)->text().trimmed().split(" ", QString::KeepEmptyParts);
			int m_string_count_all=list2.count();
			int m_string_character_count_all=item(m_arow,icol)->text().length()+m_string_count_all-1;
			int m_string_count=m_string_count_all/(m_brow+1-m_arow);
			int m_string_character_count=m_string_character_count_all/(m_brow+1-m_arow);
			int ii=0;
			if((m_string_count_all<(m_brow+1-m_arow))||(m_string_count_all==(m_brow+1-m_arow)))
			{
				mdb_element_expand.clear();
				for(int irow=m_arow;irow<m_brow+1;irow++)
				{
					if((irow-m_arow)<list2.count())
					{
						element_expand=new db_element_expand;
						element_expand->erow=irow;
						element_expand->ecol=icol;
						element_expand->epos=0;
						element_expand->e_description=list2.at(irow-m_arow);
						mdb_element_expand.push_back(element_expand);
					}
				}
				for(idb_element_expand=mdb_element_expand.begin();idb_element_expand<mdb_element_expand.end();idb_element_expand++)
				{
					item((*idb_element_expand)->erow,(*idb_element_expand)->ecol)->setText((*idb_element_expand)->e_description.trimmed());
				}
				mdb_element_expand.clear();
			}
			else
			{
				for(int irow=m_arow;irow<m_brow+1;irow++)
				{
					if(irow==m_arow)
					{
						int m_length=0;
						QString m_str1="";
						for(int i=0;i<m_string_count_all;i++)
						{
							m_length=m_length+list2.at(i).length();
							if(m_length<m_string_character_count)
							{
								m_str1=m_str1+list2.at(i).trimmed()+" ";
								ii=i+1;
							}
							else
							{
								m_length=0;
								ii=i;
								i=m_string_count_all;
							}
						}
						m_str1.trimmed();
						item(irow,icol)->setText(m_str1);
					}
					else if(irow<m_brow)
					{
						int m_length=0;
						QString m_str1="";
						for(int i=ii;i<m_string_count_all;i++)
						{
							if(i<list2.count())
							{
								m_length=m_length+list2.at(i).length();
								if(m_length<m_string_character_count)
								{
									m_str1=m_str1+list2.at(i).trimmed()+" ";
									ii=i+1;
								}
								else
								{
									m_length=0;
									ii=i;
									i=m_string_count_all;
								}
							}
						}
						m_str1.trimmed();
						item(irow,icol)->setText(m_str1);
					}
					else if(irow==m_brow)
					{
						int m_length=0;
						QString m_str1="";
						for(int i=ii;i<m_string_count_all;i++)
						{
							if(i<list2.count())
							{
								m_length=m_length+list2.at(i).length();
								m_str1=m_str1+list2.at(i).trimmed()+" ";
							}
						}
						m_str1.trimmed();
						item(irow,icol)->setText(m_str1);
					}

				}
			}
			setUpdatesEnabled(true);
		}
	}

}

void QSTableWidget::addInfoImage(int aid,double ax,double ay,QByteArray m_data,double m_scale,double m_scale_w)
{
	element_ImageInfo=new db_ImageInfo;
	element_ImageInfo->id=aid;	
	element_ImageInfo->m_x=ax;	
	element_ImageInfo->m_y=ay;	
	element_ImageInfo->m_data=m_data;
	element_ImageInfo->m_scale=m_scale;
	element_ImageInfo->m_scale_w=m_scale_w;
	mdb_element_ImageInfo.push_back(element_ImageInfo);
}

QColor QSTableWidget::getColor(int col)
{
	mdb_element_new.begin();
	return mdb_element_new.at(col)->m_color;
}

void QSTableWidget::setColor(int col, QColor m_color)
{
	for(int row_i=0;row_i<rowCount();row_i++)
	{
		for(int col_i=0;col_i<columnCount();col_i++)
		{
			if(col_i==col)
			{
				mdb_element_new.begin();
				mdb_element_new.at(row_i*columnCount()+col_i)->m_color=m_color;
			}
		}
	}
}

QFont QSTableWidget::getGraphicFont(int col)
{
	mdb_element_new.begin();
	return mdb_element_new.at(col)->m_graph_font;
}

void QSTableWidget::setGraphicFont(int col, QFont m_graphicFont)
{
	for(int row_i=0;row_i<rowCount();row_i++)
	{
		for(int col_i=0;col_i<columnCount();col_i++)
		{
			if(col_i==col)
			{
				mdb_element_new.begin();
				mdb_element_new.at(row_i*columnCount()+col_i)->m_graph_font=m_graphicFont;
			}
		}
	}
}

double QSTableWidget::getRotate(int col)
{
	mdb_element_new.begin();
	return mdb_element_new.at(col)->m_rotate;
}

void QSTableWidget::setRotate(int col, double m_rotate)
{
	for(int row_i=0;row_i<rowCount();row_i++)
	{
		for(int col_i=0;col_i<columnCount();col_i++)
		{
			if(col_i==col)
			{
				mdb_element_new.begin();
				mdb_element_new.at(row_i*columnCount()+col_i)->m_rotate=m_rotate;
			}
		}
	}
}
