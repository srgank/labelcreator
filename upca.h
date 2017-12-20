#ifndef UPCA_H
#define UPCA_H
#include <QImage>
#include <QStringList>

class UPCA 
{
public:
	UPCA();
	~UPCA();
	void CreateBarCode(QString txt, int scale);

private:
	int barCodeHeight;
	int placeMarker;
	int imageWidth;
	float imageScale;
	QString UPCABegin;
	QString UPCAMiddle;
	QString UPCAEnd;

	QStringList UPCALeft;
	QStringList UPCARight;
	void drawSet(QString upcCode, int drawLocation, int barHeight);
	int GetCheckSum(QString barCode);

};

#endif // UPCA_H
