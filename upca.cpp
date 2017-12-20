#include "upca.h"
#include <QPainter>

UPCA::UPCA()
{
	barCodeHeight = 80;
	placeMarker = 0;
	imageWidth = 0;
	imageScale = 1;
	UPCABegin = "0000000000000101";
	UPCAMiddle = "01010";
	UPCAEnd = "1010000000000000";

	UPCALeft  <<"0001101"<<"0011001"<<"0010011"<<"0111101"<<"0100011"<<"0110001"<<"0101111"<<"0111011"<<"0110111"<<"0001011";
	UPCARight <<"1110010"<<"1100110"<<"1101100"<<"1000010"<<"1011100"<<"1001110"<<"1010000"<<"1000100"<<"1001000"<<"1110100";

}
UPCA::~UPCA()
{

}

void UPCA::drawSet(QString upcCode, int drawLocation, int barHeight)
{
//	int[] currentLetterArray = new int[upcCode.Length];
	int currentLetterArray[20]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
	placeMarker += upcCode.length();
	barHeight = barCodeHeight - barHeight;
	bool ok;
	int i = 0;
	QPainter painter;
	QBrush brush;

	for(i = 0; i <= upcCode.length() - 1; i++)
	{
		currentLetterArray[i] = (upcCode.mid(i, 1)).toInt(&ok,10);
	}
	for(i = 0; i <= upcCode.length() - 1; i++)
	{
		if(currentLetterArray[i] == 0)
		{
//			g.DrawLine(Pens.White, i + (drawLocation), 0, i + (drawLocation), barHeight - 6);
			painter.setRenderHint(QPainter::Antialiasing, true);
			painter.setPen(Qt::SolidLine);
			painter.setPen(Qt::white);
			brush.setStyle(Qt::SolidPattern);
			brush.setColor(Qt::white);
			painter.setBrush(brush);
			painter.drawRect(QRectF( i + (drawLocation), 0, i + (drawLocation), barHeight - 6));
		}
		else if(currentLetterArray[i] == 1)
		{
//			g.DrawLine(Pens.Black, i + (drawLocation), 0, i + (drawLocation), barHeight - 6);
			painter.setRenderHint(QPainter::Antialiasing, true);
			painter.setPen(Qt::SolidLine);
			painter.setPen(Qt::black);
			brush.setStyle(Qt::SolidPattern);
			brush.setColor(Qt::black);
			painter.setBrush(brush);
			painter.drawRect(QRectF(i + (drawLocation), 0, i + (drawLocation), barHeight - 6));
		}
	}
}

int UPCA::GetCheckSum(QString barCode)
{
	bool ok;
	QString leftSideOfBarCode = barCode.left(12);
	int total = 0;
	int currentDigit = 0;
	int i = 0;
	for( i = 0; i <= leftSideOfBarCode.count()- 1; i++)
	{
		currentDigit = leftSideOfBarCode.mid(i, 1).toInt(&ok,10);
		if(((i - 1) % 2 == 0))
		{
			total += currentDigit * 1;
		}
		else
		{
			total += currentDigit * 3;
		}
	}
	int iCheckSum = (10 - (total % 10)) % 10;
	return iCheckSum;
}

void UPCA::CreateBarCode(QString txt, int scale)
{
	QString incomingString = txt.toUpper();
	placeMarker = 0;
	txt = txt.mid(0, 11) + QString::number(GetCheckSum(txt),10);
	int wholeSet = 0;
	for(wholeSet = 1; wholeSet <= incomingString.length(); wholeSet++)
	{
		bool ok;
		int currentASCII = (incomingString.mid((wholeSet - 1),1)).toInt(&ok,10)- 48;
		QString currentLetter = "";
		if(wholeSet == 1)
		{
			drawSet(UPCABegin, placeMarker, 0);
			drawSet(UPCALeft[currentASCII], placeMarker, 0);
		}
		else if(wholeSet <= 5)
		{
			drawSet(UPCALeft[currentASCII], placeMarker, 6);
		}
		else if(wholeSet == 6)
		{
			drawSet(UPCALeft[currentASCII], placeMarker, 6);
			drawSet(UPCAMiddle, placeMarker, 0);
		}
		else if(wholeSet <= 11)
		{
			drawSet(UPCARight[currentASCII], placeMarker, 6);
		}
		else if(wholeSet == 12)
		{
			drawSet(UPCARight[currentASCII], placeMarker, 0);
			drawSet(UPCAEnd, placeMarker, 0);
		}
	}

/*
	System.Drawing.Font font = new System.Drawing.Font("Courier New, Bold", 9);
	try
	{
		g.DrawString(txt.Substring(0, 1), font, Brushes.Black, new System.Drawing.PointF(0, 67));
		g.DrawString(txt.Substring(1, 5), font, Brushes.Black, new System.Drawing.PointF(22, 67));
		g.DrawString(txt.Substring(6, 5), font, Brushes.Black, new System.Drawing.PointF(60, 67));
		g.DrawString(txt.Substring(11, 1), font, Brushes.Black, new System.Drawing.PointF(108, 67));
	}
	finally
	{
		font.Dispose();
	}
	img = Image.FromHbitmap(newBitmap.GetHbitmap());
	return img;
*/
}