#include "alarm_frm.hh"

alarm_frm::alarm_frm (BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& _refBuilder) :
	Gtk::Window(cobject), m_notify_checked(true), m_sound_checked(true), m_reset_checked(false),
	m_timeout(1), sec(0), min(0)
{
	set_title (PACKAGE_STRING_LONG);
	set_icon_from_file (PACKAGE_ICON);
	m_StatusIcon = Gtk::StatusIcon::create_from_file (PACKAGE_ICON);
	if (m_StatusIcon) {
		m_StatusIcon->signal_activate().connect (sigc::mem_fun(*this, &alarm_frm::status_icon_activate_cb));
		m_StatusIcon->signal_popup_menu	().connect (sigc::mem_fun(*this, &alarm_frm::status_icon_popup_cb));
	}
	_refBuilder->get_widget ("menu1", m_fileMenu);
	_refBuilder->get_widget ("label2", m_timeout_label);
	_refBuilder->get_widget ("textview1", m_textview);
	/* get menu items*/
	_refBuilder->get_widget ("imagemenuitem1", m_start_item);
	if (m_start_item) {
		m_start_item->signal_activate().connect (sigc::mem_fun(*this, &alarm_frm::on_start));
	}
	_refBuilder->get_widget ("imagemenuitem2", m_pref_item);
	if (m_pref_item) {
		m_pref_item->signal_activate().connect (sigc::mem_fun(*this, &alarm_frm::on_pref));
	}
	_refBuilder->get_widget ("imagemenuitem3", m_quit_item);
	if (m_quit_item) {
		m_quit_item->signal_activate().connect (sigc::mem_fun(*this, &alarm_frm::on_quit));
	}
	_refBuilder->get_widget ("imagemenuitem4", m_about_item);
	if (m_about_item) {
		m_about_item->signal_activate().connect (sigc::mem_fun(*this, &alarm_frm::on_about));
	}
	/* get dialog and items */
	_refBuilder->get_widget ("dialog1", m_prefDialog);
	_refBuilder->get_widget ("spinbutton1", m_spinner);
	_refBuilder->get_widget ("checkbutton1", m_notify_check);
	_refBuilder->get_widget ("checkbutton2", m_sound_check);
	_refBuilder->get_widget ("checkbutton3", m_reset_check);
	/* notification stuff */
	m_notification = std::unique_ptr<notify_class>(new notify_class (*this, 4));
	/* sound stuff */
	int audio_rate = 44100;			// Frequency of audio playback
	Uint16 audio_format = AUDIO_S16; 	// Format of the audio we're playing
	int audio_channels = 2;			// 2 channels = stereo
	int audio_buffers = 4096;		// Size of the audio buffers in memory
	SDL_Init (SDL_INIT_AUDIO);
	Mix_OpenAudio (audio_rate, audio_format, audio_channels, audio_buffers);
	music = Mix_LoadMUS (PACKAGE_SOUND);
	update_timeout_label ();
	show_all ();
}

alarm_frm::~alarm_frm () {
	Mix_FreeMusic (music);
	Mix_CloseAudio();
	SDL_Quit();
	if (m_timeout_connection.connected()) {
		m_timeout_connection.disconnect ();
#ifdef ENABLE_DEBUG
		std::cout << "A connection was disconnected" << std::endl;
#endif
	}
}

bool alarm_frm::on_delete_event (GdkEventAny* event) {
	if (m_timeout_connection.connected()) {
		bool ret = false;
		Gtk::MessageDialog msgbox (*this, Glib::ustring::compose("<b>%1</b>", _("The alarm is still running")), true, Gtk::MESSAGE_WARNING, Gtk::BUTTONS_YES_NO);
		msgbox.set_secondary_text (_("Do you want to exit anyway?"));
		if (msgbox.run () != Gtk::ResponseType::RESPONSE_YES) ret = true;
		msgbox.hide ();
		if (!ret) {
			Gtk::Main::quit ();
		}
		return ret;
	}
	Gtk::Main::quit ();
	return false;
}

bool alarm_frm::on_window_state_event (GdkEventWindowState *event) {
	if (event->new_window_state == GDK_WINDOW_STATE_ICONIFIED) hide ();
	return false;
}

void alarm_frm::status_icon_activate_cb () {
	if (get_visible ()) {
        iconify ();
        hide ();
    } else {
		deiconify ();
        present ();
    }
}

void alarm_frm::status_icon_popup_cb (guint button, guint32 activate_time) {
	m_fileMenu->popup (button, activate_time);
}

void alarm_frm::on_start () {
	if (m_timeout_connection.connected()) {
		m_timeout_connection.disconnect ();
	} else {
		if (m_reset_checked) sec = 0;
		m_timeout_connection = Glib::signal_timeout().connect_seconds(sigc::mem_fun(*this, &alarm_frm::tickme), 1);
	}
	toggle_items (!m_timeout_connection.connected());
}

void alarm_frm::on_pref () {
	m_spinner->set_value (m_timeout);
	m_notify_check->set_active (m_notify_checked);
	m_sound_check->set_active (m_sound_checked);
	m_reset_check->set_active (m_reset_checked);
	if (m_prefDialog->run()) {
		m_timeout = m_spinner->get_value_as_int ();
		m_notify_checked = m_notify_check->get_active ();
		m_sound_checked = m_sound_check->get_active ();
		m_reset_checked = m_reset_check->get_active ();
		update_timeout_label ();
	}
	m_prefDialog->hide();
}

void alarm_frm::on_quit () {
	bool ret;
	g_signal_emit_by_name (gobj(), "delete-event", 0, &ret);
}

void alarm_frm::update_timeout_label () {
	Glib::ustring tmp_sec = Glib::ustring::format(std::setfill (L'0'), std::setw(2), sec);
    Glib::ustring tmp_min = Glib::ustring::format(std::setfill (L'0'), std::setw(2), min);
    Glib::ustring tmp_timeout = Glib::ustring::format(std::setfill (L'0'), std::setw(2), m_timeout);
    m_timeout_label->set_label (Glib::ustring::compose("[%1:%2/%3:00]",  tmp_min, tmp_sec, tmp_timeout));
}

bool alarm_frm::tickme () {
	bool state = true;
	sec++;
	if (sec == 60) {
		sec = 0;
		min++;
	}
	if (min == m_timeout) {
		min = 0;
		state = false;
		toggle_items ();
		deiconify ();
		present ();
		if (m_sound_checked) Mix_PlayMusic (music, 0);
	}
	update_timeout_label ();
	return state;
}

void alarm_frm::toggle_items (bool state) {
	m_start_item->set_label (state ? "gtk-media-play" : "gtk-media-stop");
	m_pref_item->set_sensitive (state);
	m_textview->set_sensitive (state);
	if (m_notify_checked) m_notification->ShowMe (state);
}

void alarm_frm::on_about () {
	Gtk::AboutDialog aboutDialog;
	Glib::ustring translators = Glib::ustring::compose ("Español: %1\n", SELFIE); 
	Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_file (PACKAGE_ICON, 64, 64);
	std::vector<Glib::ustring> authors = {SELFIE};
	aboutDialog.set_transient_for (*this);
	aboutDialog.set_program_name (PACKAGE_NAME);
	aboutDialog.set_version (PACKAGE_VERSION);
	aboutDialog.set_logo (pixbuf);
	aboutDialog.set_authors (authors);
	aboutDialog.set_comments (_("gtkmm2 crossplatform alarm application"));
	aboutDialog.set_license	("http://www.gnu.org/licenses/gpl-3.0.html");
	aboutDialog.set_website ("http://foo.com");
	aboutDialog.set_translator_credits (translators);
	aboutDialog.set_website_label (_("Visit github project website"));
	aboutDialog.run ();
	aboutDialog.hide ();
}
