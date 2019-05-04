#include <QApplication>
#include "plabel.h"
#include <QSettings>
#include <QDate>
#include <QTime>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PLabel w;

    w.setInitialDate(QDate::currentDate(),QTime::currentTime());
    w.createDockWindows();
    if(!w.generateSSID2Number(w.generateSSIDNumber()))
    {
        w.createLicenceDialog();
    }
    if(argc==2)
    {
        w.showDataFromFileExtended(argv[1]);
    }
    w.showMaximized();
    a.connect(&a, SIGNAL(lastWindowClosed()), &a, SLOT(quit()));
    return a.exec();
}
