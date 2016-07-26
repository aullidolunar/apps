#include "form.hxx"

int main (int argc, char *argv[]) {
	QTranslator qtTranslator;
	qtTranslator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
	QTranslator proTranslator;
	proTranslator.load (QLocale::system().name(), ":/");
	QApplication app(argc, argv);
	app.installTranslator (&qtTranslator);
	app.installTranslator (&proTranslator);
	QWidget widget;
	MyForm form (&widget);
	form.show();
	return app.exec();
}
