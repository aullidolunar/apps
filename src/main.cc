#include "alarm_frm.hh"

int main (int argc, char *argv[]) {
	bind_textdomain_codeset (PACKAGE_NAME, "UTF-8");
	bindtextdomain (PACKAGE_NAME, LOCALEDIR);
	textdomain (PACKAGE_NAME);
	setlocale (LC_ALL, "");
	Gtk::Main kit(argc, argv);
	Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
	try {
		refBuilder->add_from_file (PACKAGE_BUILDER);
	}
	catch (const Glib::FileError& ex) {
		cout << "FileError: " << ex.what() << endl;
		return 1;
	}
	catch (const Gtk::BuilderError& ex) {
		cout << "BuilderError: " << ex.what() << endl;
		return 1;
	}
	alarm_frm* pAlarmFrm = 0;
	refBuilder->get_widget_derived ("window1", pAlarmFrm);
	if (pAlarmFrm) kit.run();
	delete pAlarmFrm;
	return 0;
}
