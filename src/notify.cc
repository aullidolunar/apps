#include "notify.hh"
#include "alarm_frm.hh"

notify_class::notify_class (Gtk::Window& parent, int to) {
#ifdef HAVE_NOTIFYMM
	Notify::init (PACKAGE_NAME);
	m_notify = Glib::RefPtr<Notify::Notification>(new Notify::Notification (Glib::ustring()));
	m_notify->set_timeout (to * 1000);
#else
	_to = to;
	_sec = 0;
	m_notify = std::unique_ptr<Gtk::Dialog>(new Gtk::Dialog ("", parent));
	Gtk::Table *widget_center = Gtk::manage (new Gtk::Table (2, 2));
	Glib::RefPtr<Gdk::Pixbuf> pixbuf = Gdk::Pixbuf::create_from_file (PACKAGE_ICON, 64, 64);
	Gtk::Image *icon = Gtk::manage (new Gtk::Image (pixbuf));
	Gtk::Label *title = Gtk::manage (new Gtk::Label ("", 0.0));
	title->set_markup (Glib::ustring::compose ("<b>%1</b>", PACKAGE_STRING_LONG));
	body = Gtk::manage (new Gtk::Label ("", 0.0));
	widget_center->attach (*icon, 0, 1, 0, 2);
	widget_center->attach (*title, 1, 2, 0, 1);
	widget_center->attach (*body, 1, 2, 1, 2);
	m_notify->set_decorated (false);
	m_notify->get_vbox()->pack_start (*widget_center);
	m_notify->get_vbox()->show_all ();
#endif
}

notify_class::~notify_class () {
#ifndef HAVE_NOTIFYMM
	if (m_timeout_connection.connected()) {
		m_timeout_connection.disconnect ();
#ifdef ENABLE_DEBUG
		std::cout << "notify_class: A connection was disconnected" << std::endl;
#endif
	}
#endif
}

void notify_class::ShowMe(bool state) {
	Glib::ustring _body = Glib::ustring::compose ("%1 %2", _("The alarm has"), (state ? _("finished") : _("started")));
#ifdef HAVE_NOTIFYMM
	m_notify->update (PACKAGE_STRING_LONG, _body, PACKAGE_ICON);
	m_notify->show ();
#else
	body->set_text (_body);
	if (m_timeout_connection.connected()) {
		_sec = 0;
	} else {
		m_timeout_connection = Glib::signal_timeout().connect_seconds(sigc::mem_fun(*this, &notify_class::tickme), 1);
		m_notify->show ();
	}
#endif
}

bool notify_class::tickme () {
#ifndef HAVE_NOTIFYMM
	_sec++;
	if (_sec == _to) {
		m_notify->hide();
		_sec = 0;
		return false;
	}
#endif
	return true;
}
