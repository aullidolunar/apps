#include "alarm.hh"

int main (int argc, char *argv[]) {
	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
	QApplication app(argc, argv);
	/* qt translations */
	QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&qtTranslator);
    /* project translations */
	QTranslator translator;
	//translator.load (QLocale::system().name() + QString(".qm"), LOCALEDIR);
	translator.load (QLocale::system().name(), LOCALEDIR);
	app.installTranslator (&translator);
	AlarmUI gui;
	gui.show ();
	return app.exec();
}
