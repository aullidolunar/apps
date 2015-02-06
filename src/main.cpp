#include "FormUI.hpp"

int main (int argc, char *argv[]) {
	bind_textdomain_codeset (PACKAGE_NAME, "UTF-8");
	bindtextdomain (PACKAGE_NAME, LOCALEDIR);
	textdomain (PACKAGE_NAME);
	setlocale (LC_ALL, "");
	Gtk::Main kit (argc, argv);
	FormUI ui;
	Gtk::Main::run (ui);
	return 0;
}
