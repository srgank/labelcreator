#ifndef QMYDOCKWIDGET_H
#define QMYDOCKWIDGET_H

#include <QDockWidget>

class QMyDockWidget : public QDockWidget
{
	Q_OBJECT

public:
	QMyDockWidget(QWidget *parent);
	~QMyDockWidget();

signals:
	void mydockwidgetdestroyed();
	
};

#endif // QMYDOCKWIDGET_H
