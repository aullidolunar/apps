#include "alarm.hh"

int main (int argc, char *argv[]) {
	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
	QApplication app(argc, argv);
	AlarmUI gui;
	gui.show ();
	return app.exec();
}
