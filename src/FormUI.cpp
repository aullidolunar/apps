#include "FormUI.hpp"

FormUI::FormUI () {
	/* initialized managed local widgets */
	Gtk::VBox *centerWidget = Gtk::manage (new Gtk::VBox);
	Gtk::Table *table = Gtk::manage (new Gtk::Table (3, 2));
	Gtk::MenuBar *menuBar = Gtk::manage (new Gtk::MenuBar);
	Gtk::MenuItem *miApp = Gtk::manage (new Gtk::MenuItem (_("_Application"), true));
	Gtk::Menu *mApp = Gtk::manage (new Gtk::Menu);
	Gtk::ImageMenuItem *iReset = Gtk::manage (new Gtk::ImageMenuItem (Gtk::Stock::CLEAR));
	iExecute = Gtk::manage (new Gtk::ImageMenuItem (Gtk::Stock::EXECUTE));
	Gtk::SeparatorMenuItem *iSep = Gtk::manage (new Gtk::SeparatorMenuItem);
	Gtk::ImageMenuItem *iQuit = Gtk::manage (new Gtk::ImageMenuItem (Gtk::Stock::QUIT));
	Gtk::MenuItem *miHelp = Gtk::manage (new Gtk::MenuItem (_("_Help"), true));
	Gtk::Menu *mHelp = Gtk::manage (new Gtk::Menu);
	Gtk::ImageMenuItem *iAbout = Gtk::manage (new Gtk::ImageMenuItem (Gtk::Stock::ABOUT));
	Gtk::Label *label1 = Gtk::manage (new Gtk::Label (_("Input servings:")));
	_s = Gtk::manage (new Gtk::Entry);
	Gtk::Label *label2 = Gtk::manage (new Gtk::Label (_("Input dishes per serving:")));
	_d = Gtk::manage (new Gtk::Entry);
	Gtk::Label *label3 = Gtk::manage (new Gtk::Label (_("Input number of ovens:")));
	_o = Gtk::manage (new Gtk::Entry);
	/* set window props */
	set_title (PACKAGE_STRING);
	set_icon_from_file (ICON_PATH);
	/* set widgets props */
	set_menu_item_props (iReset, GDK_r, Gdk::CONTROL_MASK);
	set_menu_item_props (iExecute, GDK_e, Gdk::CONTROL_MASK);
	set_menu_item_props (iAbout, GDK_a, Gdk::CONTROL_MASK);
	iExecute->set_sensitive (false);
	label1->set_justify (Gtk::JUSTIFY_LEFT);
	table->set_border_width (10);
	/* set some signal handlers */
	iReset->signal_activate().connect (sigc::mem_fun (*this, &FormUI::on_reset_activated) );
	iExecute->signal_activate().connect (sigc::mem_fun (*this, &FormUI::on_execute_activated) );
	iQuit->signal_activate().connect (sigc::mem_fun (*this, &FormUI::on_quit_activated) );
	iAbout->signal_activate().connect (sigc::mem_fun (*this, &FormUI::on_about_activated) );
	_s->signal_key_press_event().connect (sigc::mem_fun (*this, &FormUI::on_any_entry_press_event), false);
	_s->signal_changed().connect (sigc::mem_fun (*this, &FormUI::on_any_entry_text_changed));
	_d->signal_key_press_event().connect (sigc::mem_fun (*this, &FormUI::on_any_entry_press_event), false);
	_d->signal_changed().connect (sigc::mem_fun (*this, &FormUI::on_any_entry_text_changed));
	_o->signal_key_press_event().connect (sigc::mem_fun (*this, &FormUI::on_any_entry_press_event), false);
	_o->signal_changed().connect (sigc::mem_fun (*this, &FormUI::on_any_entry_text_changed));
	/* layout */
	mApp->append (*iReset);
	mApp->append (*iExecute);
	mApp->append (*iSep);
	mApp->append (*iQuit);
	miApp->set_submenu (*mApp);
	menuBar->append (*miApp);
	mHelp->append (*iAbout);
	miHelp->set_submenu (*mHelp);
	menuBar->append (*miHelp);
	centerWidget->pack_start (*menuBar, false, false, 0);
	table->attach (*label1, 0, 1, 0, 1, Gtk::SHRINK, Gtk::SHRINK);
	table->attach (*_s, 1, 2, 0, 1);
	table->attach (*label2, 0, 1, 1, 2, Gtk::SHRINK);
	table->attach (*_d, 1, 2, 1, 2);
	table->attach (*label3, 0, 1, 2, 3, Gtk::SHRINK);
	table->attach (*_o, 1, 2, 2, 3);
	centerWidget->pack_start (*table);
	add (*centerWidget);
	/* let them loose */
	show_all ();
}

FormUI::~FormUI () {
}

void FormUI::set_menu_item_props (Gtk::ImageMenuItem* i, guint k, Gdk::ModifierType m/*, void* func*/) {
	i->add_accelerator ("activate", get_accel_group (), k, m, Gtk::ACCEL_VISIBLE);
	//i->signal_activate().connect (sigc::mem_fun (*this, func) );
}

void FormUI::on_reset_activated () {
	_s->set_text ("");
	_d->set_text ("");
	_o->set_text ("");
}

void FormUI::on_execute_activated () {
	int s = atoi (_s->get_text ().c_str ());
	int d = atoi (_d->get_text ().c_str ());
	int o = atoi (_o->get_text ().c_str ());
	int x = s /d;
	int m = x / o;
	int n = x % o;
	Gtk::MessageDialog msgbox(*this, _("<b>The results are in</b>"), true, Gtk::MessageType::MESSAGE_INFO, Gtk::ButtonsType::BUTTONS_CLOSE, true);
	msgbox.set_title (PACKAGE_STRING);
	Glib::ustring s_s = Glib::ustring::compose (g_dngettext (PACKAGE_NAME, "You need %1 round to serve", "You need %1 rounds to serve", m), m);
	Glib::ustring s_l = Glib::ustring::compose (g_dngettext (PACKAGE_NAME, "and %1 dish more", "and %1 dishes more", n), n);
	msgbox.set_secondary_text (s_s + " " + s_l);
	msgbox.run ();
	msgbox.hide ();
}

void FormUI::on_quit_activated () {
	hide ();
}

void FormUI::on_about_activated () {
	Gtk::AboutDialog about;
	about.set_transient_for (*this);
	about.set_version (PACKAGE_VERSION);
	about.set_logo (get_icon ());
	about.set_comments (_("gtkmm test application"));
	about.set_license ("http://www.gnu.org/copyleft/gpl.html");
	about.set_copyright (Glib::ustring::compose ("copyleft %1 2015 %2", "ɔ", PACKAGE_AUTHOR));
	std::vector<Glib::ustring> list_authors;
	list_authors.push_back (SELFIE);
	about.set_authors (list_authors);
	about.set_translator_credits (Glib::ustring::compose ("Español: %1", SELFIE));
	std::vector<Glib::ustring> list_artists;
	list_artists.push_back (Glib::ustring::compose ("%1: http://findicons.com/", _("Icon")));
	about.set_artists (list_artists);
	about.run ();
	about.hide ();
}

void FormUI::on_any_entry_text_changed () {
	int e1 = _s->get_text_length ();
	int e2 = _d->get_text_length ();
	int e3 = _o->get_text_length ();
	iExecute->set_sensitive ((e1 && e2 && e3));
}

bool FormUI::on_any_entry_press_event (GdkEventKey* event) {
	bool retval = true;
	switch (event->keyval) {
		case GDK_KEY_Tab:
		case GDK_KEY_BackSpace:
		case GDK_KEY_KP_0:
		case GDK_KEY_KP_1:
		case GDK_KEY_KP_2:
		case GDK_KEY_KP_3:
		case GDK_KEY_KP_4:
		case GDK_KEY_KP_5:
		case GDK_KEY_KP_6:
		case GDK_KEY_KP_7:
		case GDK_KEY_KP_8:
		case GDK_KEY_KP_9:
		case GDK_KEY_0:
		case GDK_KEY_1:
		case GDK_KEY_2:
		case GDK_KEY_3:
		case GDK_KEY_4:
		case GDK_KEY_5:
		case GDK_KEY_6:
		case GDK_KEY_7:
		case GDK_KEY_8:
		case GDK_KEY_9:
		{ 
			retval = false; 
		}
	}
	return retval;
}
