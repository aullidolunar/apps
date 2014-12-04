#include "helper.h"

GtkWidget * create_button_helper (int _id) {
	const gchar *file_name_icons[][2] = {
		{ "play.png", _("Start the alarm") },
		{ "about.png", _("About alarm") },
		{ "exit.png", _("Close alarm") }
	};
	GtkWidget *tmp;
	GtkWidget *i;
	GdkPixbuf *p;
	gchar *file_path;
	tmp = gtk_button_new ();
	file_path = g_build_filename (RES_DIR, file_name_icons[_id][0], NULL);
	p = gdk_pixbuf_new_from_file_at_size (file_path, 24, 24, NULL);
	i = gtk_image_new_from_pixbuf (p);
	gtk_button_set_image (GTK_BUTTON (tmp), i);
	gtk_widget_set_tooltip_text (tmp, file_name_icons[_id][1]);
	g_free (file_path);
	g_object_unref (p);
	return tmp;
}

void update_button_helper (GtkWidget *b, const gint _id) {
	const gchar *helpers[][2] = {
		{ "play.png", _("Start the alarm") },
		{ "stop.png", _("Stop the alarm") },
	};
	GtkWidget *i;
	GdkPixbuf *p;
	gchar *file_path;
	file_path = g_build_filename (RES_DIR, helpers[_id][0], NULL);
	p = gdk_pixbuf_new_from_file_at_size (file_path, 24, 24, NULL);
	i = gtk_image_new_from_pixbuf (p);
	gtk_button_set_image (GTK_BUTTON (b), i);
	gtk_widget_set_tooltip_text (b, helpers[_id][1]);
	g_free (file_path);
	g_object_unref (p);
}

GtkWidget * create_box_helper (const int _o) {
	GtkWidget *tmp;
	if (_o) { // vertical
#ifdef WITH_GTK2
		tmp = gtk_vbox_new (FALSE, 0);
#else
		tmp = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
#endif
	} else { // horizontal
#ifdef WITH_GTK2		
		tmp = gtk_hbox_new (FALSE, 0);
#else
		tmp = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
#endif
	}
	return tmp;
}

void toggle_ui (GtkWindow *parent) {
	gboolean state;
	state = gtk_widget_get_visible(GTK_WIDGET (parent));
	if (state) {
		gtk_widget_set_visible (GTK_WIDGET (parent), FALSE);
	} else {
		gtk_window_deiconify (parent);
		gtk_window_present (parent);
	}
}

void add_button_helper (GtkDialog *d, const gchar *label, gint _id) {
	int ids[] = {
		GTK_RESPONSE_YES,
		GTK_RESPONSE_NO
	};
	GtkWidget *tmp;
	GtkWidget *i;
	GdkPixbuf *p;
	gchar *f;
	tmp = gtk_button_new_with_label (label);
	f = g_build_filename (RES_DIR, _id ? "no.png" : "yes.png", NULL);
	p = gdk_pixbuf_new_from_file_at_size (f, 24, 24, NULL);
	i = gtk_image_new_from_pixbuf (p);
	gtk_button_set_image (GTK_BUTTON (tmp), i);
	gtk_dialog_add_action_widget (d, tmp, ids[_id]);
	gtk_widget_show (tmp);
	g_object_unref (p);
	g_free (f);
}

gboolean message_box_helper (GtkWindow *parent) {
	GtkWidget *m;
	GtkWidget *y;
	GtkWidget *n;
	gboolean response;
	m = gtk_message_dialog_new_with_markup (parent, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_WARNING, GTK_BUTTONS_NONE, "<b>%s</b>", _("Alarm process runing"));
	gtk_window_set_title (GTK_WINDOW (m), PACKAGE_STRING);
	gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (m), _("Do you want to exit anyway?"));
	add_button_helper (GTK_DIALOG (m), _("Yes"), YES_BUTTON);
	add_button_helper (GTK_DIALOG (m), _("No"), NO_BUTTON);
	if (gtk_dialog_run (GTK_DIALOG (m)) == GTK_RESPONSE_YES) {
		response = TRUE;
	} else {
		response = FALSE;
	}
	gtk_widget_destroy (m);
	return response;
}
