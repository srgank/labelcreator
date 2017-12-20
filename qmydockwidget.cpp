#include "qmydockwidget.h"

QMyDockWidget::QMyDockWidget(QWidget *parent)
	: QDockWidget(parent)
{
setGeometry(0,0,300,height());
}

QMyDockWidget::~QMyDockWidget()
{
emit mydockwidgetdestroyed();
}
