#ifndef QGBOTTOMSCENE_H
#define QGBOTTOMSCENE_H

#include <QWidget>
#include "ui_qgbottomscene.h"

class QGBottomScene : public QWidget
{
	Q_OBJECT

public:
	QGBottomScene(QWidget *parent = 0);
	~QGBottomScene();

private:
	Ui::QGBottomSceneClass ui;
};

#endif // QGBOTTOMSCENE_H
