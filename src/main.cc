#include "alarm.hh"

int main (int argc, char *argv[]) {
	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
	/* QT translations */
	QTranslator qtTranslator;
	qtTranslator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
	/* project translations */
	QTranslator proTranslator;
	proTranslator.load (QLocale::system().name(), ":/locales");
	QApplication app(argc, argv);
	app.setQuitOnLastWindowClosed  (false);
	app.installTranslator (&qtTranslator);
	app.installTranslator (&proTranslator);
	QWidget parent;
	AlarmUI gui (&qtTranslator, &proTranslator, &parent);
	gui.show ();
	return app.exec();
}
