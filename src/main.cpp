#include "reguser.hpp"

int main (int argc, char *argv[]) {
	QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
	QApplication app(argc, argv);
	QTranslator translator;
	translator.load (QLocale::system().name() + QString(".qm"), LOCALEDIR);
	app.installTranslator (&translator);
#if QT_VERSION > QT_VERSION_CHECK(4, 3, 5)
	app.setAttribute(Qt::AA_DontShowIconsInMenus, false);
#endif
	RegUser gui;
	gui.show ();
	return app.exec();
}
