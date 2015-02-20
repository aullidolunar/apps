#ifndef FORMUI_HPP_INCLUDED
#define FORMUI_HPP_INCLUDED

#include "main.hpp"

class FormUI : public Gtk::Window
{
	private:
		typedef std::vector<Glib::ustring> array_handle;
		Glib::RefPtr<Gtk::Builder> m_refBuilder;
		Gtk::Button *button_execute;
		Gtk::Button *button_add;
		Gtk::ScrolledWindow *sw2;
		Gtk::Entry *entry;
		Gtk::TreeView *tv;
		Gnome::Vte::Terminal terminal;
		Glib::RefPtr<Gtk::ListStore> store;
		Gtk::TreeModel::Children::iterator currentItem;
		Gtk::TreeModel::Children::const_iterator lastItem;
	public:
		FormUI (BaseObjectType*, const Glib::RefPtr<Gtk::Builder>&);
		virtual ~FormUI ();
	protected:
		void spawn_in_terminal ();
		void on_child_exited ();
		void on_execute_clicked ();
		void on_entry_changed ();
		void on_add_clicked ();
		void toggle (bool state = true);
		class ModelColumns : public Gtk::TreeModel::ColumnRecord
		{
			public:
				Gtk::TreeModelColumn< Glib::RefPtr<Gdk::Pixbuf> > m_colPixbuf;
				Gtk::TreeModelColumn<Glib::ustring> m_colStr;
				ModelColumns() {
					add (m_colPixbuf);
					add (m_colStr);
				}
		};
		ModelColumns modelColumns;
};


#endif
