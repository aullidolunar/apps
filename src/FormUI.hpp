#ifndef FORMUI_HPP_INCLUDED
#define FORMUI_HPP_INCLUDED

#include "main.hpp"

class FormUI : public Gtk::Window
{
	private:
		typedef void (FormUI::*function_ptr)();
		Gtk::ImageMenuItem *iExecute;
		Gtk::Entry *_s;
		Gtk::Entry *_d;
		Gtk::Entry *_o;
	public:
		FormUI ();
		virtual ~FormUI ();
	protected:
		void set_menu_item_props (Gtk::ImageMenuItem*, guint, Gdk::ModifierType, function_ptr);
		void on_reset_activated ();
		void on_execute_activated ();
		void on_quit_activated ();
		void on_about_activated ();
		bool on_any_entry_press_event (GdkEventKey*);
		void on_any_entry_text_changed ();
};


#endif
