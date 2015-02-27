#include "FormUI.hpp"

FormUI::FormUI (BaseObjectType* parent, const Glib::RefPtr<Gtk::Builder>& builder) :
	Gtk::Window (parent), m_refBuilder (builder),  terminal(), entry (0), _pid (0)
{
	m_refBuilder->get_widget ("button1", button_add);
	m_refBuilder->get_widget ("button2", button_execute);
	m_refBuilder->get_widget ("entry1", entry);
	m_refBuilder->get_widget ("scrolledwindow2", sw2);
	m_refBuilder->get_widget ("treeview1", tv);
	/* I haven't found a solution to using a liststore from builder file
	and bypass the warning: "Unable to convert from GdkPixbuf to gtkmm__GdkPixbuf"
	* I'll keep this line to remember how to cast other objects
	store = Glib::RefPtr<Gtk::ListStore>::cast_dynamic(m_refBuilder->get_object ("liststore1"));
	*/
	if (tv) {
		store = Gtk::ListStore::create (modelColumns);
		tv->set_model (store);
		tv->append_column ("", modelColumns.m_colPixbuf);
		tv->append_column ("URL", modelColumns.m_colStr);
		tv->set_headers_visible ();
	}
	if (sw2) {
		sw2->set_hadjustment (terminal.get_adjustment());
	}
	if (button_add) button_add->signal_clicked().connect( sigc::mem_fun(*this, &FormUI::on_add_clicked) );
	if (button_execute) button_execute->signal_clicked().connect( sigc::mem_fun(*this, &FormUI::on_execute_clicked) );
	if (entry) entry->signal_changed ().connect ( sigc::mem_fun (*this, &FormUI::on_entry_changed) );
	terminal.signal_child_exited().connect(sigc::mem_fun(*this, &FormUI::on_child_exited));
	
	signal_delete_event	().connect (sigc::mem_fun (*this, &FormUI::cb_on_delete_event));
	
	set_title (PACKAGE_STRING);
	set_icon_from_file (ICON_PATH);
	
	sw2->add (terminal);
	
	/* let them loose */
	show_all ();
}

FormUI::~FormUI () {
	if (_pid) {
		kill (_pid, 0);
		Glib::spawn_close_pid (_pid);
		_pid = 0;
	}
}

void FormUI::on_execute_clicked () {
	Gtk::TreeModel::Children children = store->children ();
	currentItem = children.begin ();
	lastItem = children.end ();
	spawn_in_terminal ();
	toggle (false);
}

void FormUI::on_entry_changed () {
	button_add->set_sensitive (entry->get_text_length ());
}

void FormUI::on_add_clicked () {
	Gtk::TreeModel::Row row = *(store->append());
	row[modelColumns.m_colPixbuf] = Gdk::Pixbuf::create_from_file (DATA_DIR "/bullet.png", 16, 16);
	row[modelColumns.m_colStr] = entry->get_text ();
	entry->set_text ("");
	button_add->set_sensitive (false);
}

void FormUI::spawn_in_terminal () {
	Gtk::TreeModel::Row row = *currentItem;
	array_handle argv;
	array_handle envv;
	argv.push_back (YOUTUBEDL_PATH);
	argv.push_back ("-f");
	argv.push_back ("best");
	argv.push_back ("--extract-audio");
	argv.push_back ("--audio-format");
	argv.push_back ("mp3");
	argv.push_back ("--audio-quality");
	argv.push_back ("320k");
	argv.push_back (row[modelColumns.m_colStr]);
	_pid = terminal.fork_command (YOUTUBEDL_PATH, argv, envv, Glib::get_user_special_dir (G_USER_DIRECTORY_MUSIC));
	row[modelColumns.m_colPixbuf] = Gdk::Pixbuf::create_from_file (DATA_DIR "/current.png", 16, 16);
}

void FormUI::on_child_exited () {
	Gtk::TreeModel::Row row = *currentItem;
	if (!terminal.get_child_exit_status ()) {
		row[modelColumns.m_colPixbuf] = Gdk::Pixbuf::create_from_file (DATA_DIR "/download.png", 16, 16);
	} else {
		row[modelColumns.m_colPixbuf] = Gdk::Pixbuf::create_from_file (DATA_DIR "/error.png", 16, 16);
	}
	currentItem++;
	if (currentItem != lastItem) {
		spawn_in_terminal ();
	} else {
		toggle ();
		_pid = 0;
	}
}

void FormUI::toggle (bool state) {
	entry->set_sensitive (state);
	button_add->set_sensitive (state);
	button_execute->set_sensitive (state);
}

bool FormUI::show_mb () {
	bool retState;
	Gtk::MessageDialog md(*this, Glib::ustring::compose ("<b>%1</b>", _("Warning: youtube-dl in process")), true, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_YES_NO, true);
	md.set_title (PACKAGE_STRING);
	md.set_secondary_text (_("Closing can generate a corrupted file, do you want to continue anyway?"));
	Glib::PropertyProxy<bool> puf = md.property_destroy_with_parent ();
	puf.set_value (true);
	if (md.run() == Gtk::RESPONSE_YES) {
		retState = true;
	} else {
		retState = false;
	}
	md.hide ();
	return retState;
}

bool FormUI::cb_on_delete_event (GdkEventAny* event) {
	if (_pid) {
		if (show_mb ()) {
			return false;
		} else {
			return true;
		}
	} else {
		return false;
	}
}
