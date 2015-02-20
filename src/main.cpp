#include "FormUI.hpp"

int main (int argc, char *argv[]) {
	bind_textdomain_codeset (PACKAGE_NAME, "UTF-8");
	bindtextdomain (PACKAGE_NAME, LOCALEDIR);
	textdomain (PACKAGE_NAME);
	setlocale (LC_ALL, "");
	Gtk::Main kit (argc, argv);
	Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
	try { refBuilder->add_from_file (UI_PATH); }
	catch (const Glib::FileError& ex) {
		std::cout << "FileError: " << ex.what() << std::endl;
		return 1;
	}
	catch (const Gtk::BuilderError& ex) {
		std::cout << "BuilderError: " << ex.what() << std::endl;
		return 1;
	}
	Gnome::Vte::init();
	FormUI * ui = 0;
	refBuilder->get_widget_derived ("window1", ui);
	if (ui) {
		kit.run (*ui);
	}
	delete ui;
	return 0;
}
