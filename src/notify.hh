#ifndef NOTIFY_HH_INC
#define NOTIFY_HH_INC

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gtkmm/window.h>
#include <glibmm/i18n.h>
#ifdef HAVE_NOTIFYMM
#include <libnotifymm.h>
#else
#include <gtkmm/dialog.h>
#include <gtkmm/table.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>
#include <memory>
#endif


class notify_class {
	private:
#ifdef HAVE_NOTIFYMM
	Glib::RefPtr<Notify::Notification> m_notify;
#else
	std::unique_ptr<Gtk::Dialog> m_notify;
	sigc::connection m_timeout_connection;
	Gtk::Label *body;
	int _sec;
	int _to;
#endif
	public:
		notify_class (Gtk::Window&, int);
		~notify_class ();
		void ShowMe (bool state = true);
	protected:
		bool tickme ();
};

#endif
