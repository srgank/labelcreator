#ifndef QSTABLEWIDGETDELEGATE_H
#define QSTABLEWIDGETDELEGATE_H

#include <QItemDelegate>

class QSTableWidgetDelegate : public QItemDelegate
{
	Q_OBJECT

public:
	QSTableWidgetDelegate(QObject *parent);
	~QSTableWidgetDelegate();

	QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,const QModelIndex &index) const;

	void setEditorData(QWidget *editor, const QModelIndex &index) const;
	void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const;

	void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	void setAFont(QFont a_font);
	QFont getAFont(){return m_font;}
private:
	QFont m_font;
	
};

#endif // QSTABLEWIDGETDELEGATE_H
