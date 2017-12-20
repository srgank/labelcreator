#include "qdbbase.h"
#include <QFileDialog>
#include <QDir>
#include <QStandardItem>
#include <QAbstractTableModel>
#include <QVector>


QDBBase::QDBBase(QWidget *parent)
	: QWidget(parent)
{
 m_filename="";
}


QDBBase::~QDBBase()
{

}

int QDBBase::addRecord(QString x_a1,QString x_b1,QString x_c1,QString x_d1,
					   QString x_a2,QString x_b2,QString x_c2,QString x_d2,QString x_count)
{
	//mdb_element.clear(); 
	new_element=new db_element;
	new_element->m_A1=x_a1;	
	new_element->m_B1=x_b1;
	new_element->m_C1=x_c1;
	new_element->m_D1=x_d1;
	new_element->m_A2=x_a2;	
	new_element->m_B2=x_b2;
	new_element->m_C2=x_c2;
	new_element->m_D2=x_d2;
	new_element->m_Count=x_count;
	mdb_element.push_back(new_element);
	return 0;
}

void QDBBase::removeRecord(QString m_searchString)
{
	for(idb_element=mdb_element.begin();idb_element<mdb_element.end();idb_element++)
	{
		if((*idb_element)->m_A1==m_searchString)
		{
				delete (*idb_element);
				mdb_element.erase(idb_element);
		}
	}
}

void QDBBase::loadRecordsFromFile()
{
	QString filename = QFileDialog::getOpenFileName(
		this,tr("Open Document"),QDir::currentPath(),tr("Ltc files (*.ltc)"));
	if( !filename.isNull() )
	{	
		QFile file( filename);
		m_filename=filename;
		if( !file.open( QIODevice::ReadOnly ) )
		return;
		QDataStream stream( &file );
		stream.setVersion( QDataStream::Qt_4_2 );
		QString a1,b1,c1,d1,a2,b2,c2,d2,mcount;
		mdb_element.clear(); 
		stream >> m_label1;
		stream >> m_label2;
		stream >> m_label3;
		stream >> m_label4;
		stream >> m_label5;
		stream >> m_label6;
		stream >> m_label7;
		stream >> m_label8;

		while(!stream.atEnd())
			{
			stream >>a1;
			stream >>b1;
			stream >>c1;
			stream >>d1;
			stream >>a2;
			stream >>b2;
			stream >>c2;
			stream >>d2;
			stream >>mcount;
			stream >>m_font1;
			stream >>m_font2;
			stream >>m_font3;
			stream >>m_font4;
			stream >>m_font5;
			stream >>m_font6;
			stream >>m_font7;
			stream >>m_font8;
			new_element=new db_element;
			new_element->m_A1=a1;	
			new_element->m_B1=b1;	
			new_element->m_C1=c1;	
			new_element->m_D1=d1;	
			new_element->m_A2=a2;	
			new_element->m_B2=b2;	
			new_element->m_C2=c2;	
			new_element->m_D2=d2;
			new_element->m_Count=mcount;
			new_element->m_f1=m_font1;
			new_element->m_f2=m_font2;
			new_element->m_f3=m_font3;
			new_element->m_f4=m_font4;
			new_element->m_f5=m_font5;
			new_element->m_f6=m_font6;
			new_element->m_f7=m_font7;
			new_element->m_f8=m_font8;
			mdb_element.push_back(new_element);
		}
		file.close();
	}
}

void QDBBase::saveRecordsToFile()
{
		QFile file( m_filename);
		if( !file.open( QIODevice::WriteOnly ) )
			return;
		QDataStream stream( &file );
		stream.setVersion(QDataStream::Qt_4_2);
		stream << m_label1;
		stream << m_label2;
		stream << m_label3;
		stream << m_label4;
		stream << m_label5;
		stream << m_label6;
		stream << m_label7;
		stream << m_label8;


		for(idb_element=mdb_element.begin();idb_element<mdb_element.end();idb_element++)
		{
			stream <<(*idb_element)->m_A1;
			stream <<(*idb_element)->m_B1;
			stream <<(*idb_element)->m_C1;
			stream <<(*idb_element)->m_D1;
			stream <<(*idb_element)->m_A2;
			stream <<(*idb_element)->m_B2;
			stream <<(*idb_element)->m_C2;
			stream <<(*idb_element)->m_D2;
			stream <<(*idb_element)->m_Count;
			stream <<(*idb_element)->m_f1;
			stream <<(*idb_element)->m_f2;
			stream <<(*idb_element)->m_f3;
			stream <<(*idb_element)->m_f4;
			stream <<(*idb_element)->m_f5;
			stream <<(*idb_element)->m_f6;
			stream <<(*idb_element)->m_f7;
			stream <<(*idb_element)->m_f8;
		}
		file.close();
}

void QDBBase::saveAsRecordsToFile()
{
	QString filename = QFileDialog::getSaveFileName(
		this,tr("Save As...Document"),QDir::currentPath(),tr("Ltc files (*.ltc)"));
	if( !filename.isNull())
	{	
		QFile file( filename);
		if( !file.open( QIODevice::WriteOnly ) )
			return;
		QDataStream stream( &file );
		m_filename=filename;
		stream.setVersion(QDataStream::Qt_4_2);
			stream << m_label1;
			stream << m_label2;
			stream << m_label3;
			stream << m_label4;
			stream << m_label5;
			stream << m_label6;
			stream << m_label7;
			stream << m_label8;

		for(idb_element=mdb_element.begin();idb_element<mdb_element.end();idb_element++)
		{
			stream <<(*idb_element)->m_A1;
			stream <<(*idb_element)->m_B1;
			stream <<(*idb_element)->m_C1;
			stream <<(*idb_element)->m_D1;
			stream <<(*idb_element)->m_A2;
			stream <<(*idb_element)->m_B2;
			stream <<(*idb_element)->m_C2;
			stream <<(*idb_element)->m_D2;
			stream <<(*idb_element)->m_Count;

			stream <<(*idb_element)->m_f1;
			stream <<(*idb_element)->m_f2;
			stream <<(*idb_element)->m_f3;
			stream <<(*idb_element)->m_f4;
			stream <<(*idb_element)->m_f5;
			stream <<(*idb_element)->m_f6;
			stream <<(*idb_element)->m_f7;
			stream <<(*idb_element)->m_f8;
		}
		file.close();
	}
}
bool QDBBase::fExistFileName()
{
	return m_filename!=""? true:false;
}

QString QDBBase::getFileName()
{
	return m_filename;
}

void QDBBase::setLabel(QStringList sl)
{
	m_label1=sl.at(0);
	m_label2=sl.at(1);
	m_label3=sl.at(2);
	m_label4=sl.at(3);
	m_label5=sl.at(4);
	m_label6=sl.at(5);
	m_label7=sl.at(6);
	m_label8=sl.at(7);
}
QStringList QDBBase::getLabel()
{
QStringList sl;
sl<<m_label1<<m_label2<<m_label3<<m_label4<<m_label5<<m_label6<<m_label7<<m_label8<<"count";
return sl;
}

void QDBBase::loadRecordsFromFileExtended(QString filename)
{
		QFile file( filename);
		m_filename=filename;
		if( !file.open( QIODevice::ReadOnly ) )
			return;
		QDataStream stream( &file );
		stream.setVersion( QDataStream::Qt_4_2 );
		QString a1,b1,c1,d1,a2,b2,c2,d2,mcount;
		mdb_element.clear(); 
		stream >> m_label1;
		stream >> m_label2;
		stream >> m_label3;
		stream >> m_label4;
		stream >> m_label5;
		stream >> m_label6;
		stream >> m_label7;
		stream >> m_label8;

		while(!stream.atEnd())
		{
			stream >>a1;
			stream >>b1;
			stream >>c1;
			stream >>d1;
			stream >>a2;
			stream >>b2;
			stream >>c2;
			stream >>d2;
			stream >>mcount;
			stream >> m_font1;
			stream >> m_font2;
			stream >> m_font3;
			stream >> m_font4;
			stream >> m_font5;
			stream >> m_font6;
			stream >> m_font7;
			stream >> m_font8;
	
			new_element=new db_element;
			new_element->m_A1=a1;	
			new_element->m_B1=b1;	
			new_element->m_C1=c1;	
			new_element->m_D1=d1;	
			new_element->m_A2=a2;	
			new_element->m_B2=b2;	
			new_element->m_C2=c2;	
			new_element->m_D2=d2;
			new_element->m_Count=mcount;

			new_element->m_f1=m_font1;
			new_element->m_f2=m_font2;
			new_element->m_f3=m_font3;
			new_element->m_f4=m_font4;
			new_element->m_f5=m_font5;
			new_element->m_f6=m_font6;
			new_element->m_f7=m_font7;
			new_element->m_f8=m_font8;

			mdb_element.push_back(new_element);
		}
		file.close();
}

void QDBBase::setFonts(QVector<QFont*> sl)
{
	m_fonts=sl;
}

QVector<QFont*> QDBBase::getFonts()
{
	return m_fonts;
}

void QDBBase::ccsignal(QPoint s)
{
}