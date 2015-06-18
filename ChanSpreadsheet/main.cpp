#include "chanspreadsheet.h"
#include <QtWidgets/QApplication>
#include <qsplashscreen.h>

int main(int argc, char* argv[])
{

	QApplication a(argc, argv);

	QSplashScreen* splash = new QSplashScreen;
	splash->setPixmap(QPixmap(srcFileName::pSplash));
	splash->show();

	splash->showMessage(QObject::tr("loading resource"), Qt::AlignLeft | Qt::AlignBottom, Qt::blue);
	splash->showMessage(QObject::tr("Chan Spreadsheet has been loaded"), Qt::AlignLeft | Qt::AlignBottom, Qt::blue);

	ChanSpreadsheet w;
	w.show();

	splash->finish(&w);

	delete splash;
	return a.exec();
}
