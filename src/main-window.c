#include "main-window.h"

void button_quit_clicked (GtkButton *w, LPAPPWIDGETS p) {
	gboolean response;
	g_signal_emit_by_name (p->mainWindow, "delete-event", p, &response);
	if (!response) {
		gtk_widget_destroy (p->mainWindow);
	}
}

void button_play_clicked (GtkButton *w, LPAPPWIDGETS p) {
	gboolean state;
	state = gtk_widget_get_sensitive (p->notebook);
	gint event;
	if (state) { // play
		if (!p->_reset) {
			p->s = 0;
		}
		p->m = 0;
		p->source_id = start_timer (p);
		event = PLAY;
	} else {
		// stop
		event = STOP;
		g_source_remove (p->source_id);
		p->source_id = 0;
	}
	if (!p->_notify) {
		notify_popup (p, state);
	}
	update_button_helper (GTK_WIDGET (w), event);
	gtk_widget_set_sensitive (p->notebook, !state);
}

void button_about_clicked (GtkButton *w, GtkWindow *p) {
	const gchar * const authors[] = {
		"Joel Almeida <" PACKAGE_BUGREPORT ">",
		NULL
	};
	GdkPixbuf *pb;
	pb = gdk_pixbuf_new_from_file_at_size (ICON_PATH, 64, 64, NULL);
#if WITH_GTK2
	gtk_show_about_dialog (p, "authors", authors, "website-label", _("Visit program github site"), "website", "https://github.com/aullidolunar/apps/tree/galarm2", "license", "GPLv3: http://www.gnu.org/licenses/gpl-3.0.html", "comments", _("Alarm utility"),"version", PACKAGE_VERSION, "logo", pb, NULL);
#else
	gtk_show_about_dialog (p, "authors", authors, "website-label", _("Visit program github site"), "website", "https://github.com/aullidolunar/apps/tree/galarm2", "license-type", GTK_LICENSE_GPL_3_0, "comments", _("Alarm utility"),"version", PACKAGE_VERSION, "logo", pb, NULL);
#endif
	g_object_unref (pb);
}

gboolean on_window1_window_state_event (GtkWidget *sender, GdkEventWindowState *event, gpointer data) {
#if (WITH_GTK2 || GTK_MINOR_VERSION < 14)
	if (event->new_window_state == GDK_WINDOW_STATE_ICONIFIED) {
		gtk_widget_set_visible (sender, FALSE);
	}
#endif
	return FALSE;
}

gboolean on_window1_delete_event(GtkWindow *widget, GdkEvent *event, LPAPPWIDGETS p) {
	gboolean state;
	state = gtk_widget_get_sensitive (p->notebook);
	if (!state) {
		return !message_box_helper (widget);
	}
	return FALSE;
}

void on_notebook1_switch_page(GtkNotebook *notebook, gpointer arg1, guint arg2, LPAPPWIDGETS p) {
	gtk_widget_set_sensitive (p->button_play, !(gboolean)arg2);
}

void init_app_ui (LPAPPWIDGETS ptr) {
	GtkWidget *centerWidget;
	GtkWidget *button_box;
	GtkWidget *button_about;
	GtkWidget *button_quit;
	
	ptr->mainWindow = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	centerWidget = create_box_helper (VERTICAL_BOX);
	ptr->notebook = gtk_notebook_new ();
	button_box = create_box_helper (HORIZONTAL_BOX);

	ptr->button_play = create_button_helper (BUTTON_PLAY);
	button_about = create_button_helper (BUTTON_ABOUT);
	button_quit = create_button_helper (BUTTON_QUIT);	
		
	g_signal_connect (ptr->mainWindow, "destroy", G_CALLBACK(gtk_main_quit), ptr);
	g_signal_connect (ptr->mainWindow, "window-state-event", G_CALLBACK(on_window1_window_state_event), NULL);
	g_signal_connect (ptr->mainWindow, "delete-event", G_CALLBACK(on_window1_delete_event), ptr);
	g_signal_connect (ptr->notebook, "switch-page", G_CALLBACK(on_notebook1_switch_page), ptr);
	g_signal_connect (ptr->button_play, "clicked", G_CALLBACK(button_play_clicked), ptr);
	g_signal_connect (button_about, "clicked", G_CALLBACK(button_about_clicked), ptr->mainWindow);
	g_signal_connect (button_quit, "clicked", G_CALLBACK(button_quit_clicked), ptr);
	
	gtk_box_pack_start (GTK_BOX (centerWidget), ptr->notebook, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (button_box), ptr->button_play, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (button_box), button_about, TRUE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (button_box), button_quit, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (centerWidget), button_box, FALSE, FALSE, 0);
	gtk_container_add (GTK_CONTAINER (ptr->mainWindow), centerWidget);
	gtk_container_set_border_width (GTK_CONTAINER (ptr->mainWindow), 10);
}
