#ifndef QGSCENE_H
#define QGSCENE_H

#include <QGraphicsScene>



class QGScene : public QGraphicsScene
{
	Q_OBJECT

public:
	QGScene(QObject *parent);
	~QGScene();
	int e_col,e_row;
	void deleteSelectedItem();
	void autoSelectedItem();
	void autoBottomSelectedItem();
	void setRC(int acol,int arow);
	void addInfo(int aid,int ax,int ay,QColor m_color,QFont m_graph_Font,double m_rotate);
	double GetInfoX(int aid);
	double GetInfoY(int aid);
	void addInfoImage(int aid,double ax,double ay,QByteArray m_data,double m_scale, double m_scale_w);
	double GetInfoImageX(int aid);
	double GetInfoImageY(int aid);
	void itemsShowGridBorderVisible();
	void itemsHideGridBorder();


	bool m_stat_update;



public:
	typedef struct dbprint_elementPos{
		int id;
		double m_x;
		double m_y;
		double m_width;
		double m_height;
		QColor m_color;
		QFont m_graphic_Font;
		double m_rotate;
		double m_scale;
		double m_scalew;

	} *pdbprint_elementPos;

	pdbprint_elementPos newprint_elementPos;
	

	QVector <pdbprint_elementPos> mdbprint_elementPos;
	QVector <pdbprint_elementPos>::iterator idbprint_elementPos;


	typedef QVector<pdbprint_elementPos> Typemdbprint_elementPos;
	Typemdbprint_elementPos x;

void scaleSelectedItem(double scale);
void setColorText(QColor m_color);
void setTextFont(QFont m_graph_font);
QColor GetColorText();
QFont getGraphicFont(int aid);
QColor getColor(int aid);
double getWidth(int aid);
double getHeight(int aid);
double getScale(int aid);
double getScaleW(int aid);
QByteArray GetInfoImageData(int aid);

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

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent * mouseEvent);
	virtual void drawForeground(QPainter * painter, const QRectF & rect);
public:
	void GetNewPosition(Typemdbprint_elementPos *x);
	void InitilizeItems();
	QFont GetGpahicsFont();
    double GetRotate(int aid);
	void setRotate(double m_rotate);
signals:
	void mChangeFont();
private:

	QPointF m_A,m_B,m_Aresize,m_Bresize;

	bool stat_selected;
	bool stat_resize;

};

#endif // QGSCENE_H
