#include "alarm.hh"

int main (int argc, char *argv[]) {
	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
	QApplication app(argc, argv);
	QTranslator translator;
	translator.load (QLocale::system().name() + QString(".qm"), LOCALEDIR);
	app.installTranslator (&translator);
	AlarmUI gui;
	gui.show ();
	return app.exec();
}
