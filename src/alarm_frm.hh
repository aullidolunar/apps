#ifndef ALARM_FRM_HH
#define ALARM_FRM_HH

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gtkmm/statusicon.h>
#include <gtkmm/window.h>
#include <gtkmm/dialog.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/aboutdialog.h>
#include <glibmm/i18n.h>
#include <iomanip>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "main.hh"
#include "notify.hh"

class alarm_frm : public Gtk::Window
{
	private:
		Glib::RefPtr<Gtk::StatusIcon> m_StatusIcon;
		Gtk::Menu *m_fileMenu;
		Gtk::Label *m_timeout_label;
		Gtk::ImageMenuItem *m_quit_item;
		Gtk::ImageMenuItem *m_pref_item;
		Gtk::ImageMenuItem *m_start_item;
		Gtk::ImageMenuItem *m_about_item;
		Gtk::Widget *m_textview;
		Gtk::Dialog *m_prefDialog;
		Gtk::SpinButton *m_spinner;
		Gtk::CheckButton *m_notify_check;
		Gtk::CheckButton *m_sound_check;
		Gtk::CheckButton *m_reset_check;
		sigc::connection m_timeout_connection;
		bool m_notify_checked;
		bool m_sound_checked;
		bool m_reset_checked;
		int m_timeout;
		int sec;
		int min;
		Mix_Music *music;
		std::unique_ptr<notify_class> m_notification;
	public:
		alarm_frm (BaseObjectType*, const Glib::RefPtr<Gtk::Builder>&);
		virtual ~alarm_frm ();
	protected:
		virtual bool on_delete_event (GdkEventAny*);
		virtual bool on_window_state_event (GdkEventWindowState *);
		void status_icon_activate_cb ();
		void status_icon_popup_cb (guint, guint32);
		bool tickme ();
		void on_start ();
		void on_quit ();
		void on_pref ();
		void on_about ();
		void update_timeout_label ();
		void toggle_items (bool state = true);
};

#endif
