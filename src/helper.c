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
	GdkPixbuf *pb;
	GtkWidget *m;
	GtkWidget *content;
	GtkWidget *h1;
	GtkWidget *y;
	GtkWidget *n;
	GtkWidget *i;
	GtkWidget *l;
	gchar *tmp;
	gboolean response;
	m = gtk_dialog_new ();
	content = gtk_dialog_get_content_area (GTK_DIALOG (m));
	gtk_window_set_title (GTK_WINDOW (m), PACKAGE_STRING);
	h1 = create_box_helper (HORIZONTAL_BOX);
	gtk_container_set_border_width (GTK_CONTAINER (h1), 10);
	pb = gdk_pixbuf_new_from_file_at_size (RES_DIR "/warning.png", 64, 64, NULL);
	i = gtk_image_new_from_pixbuf (pb);
	tmp = g_strdup_printf ("<b>%s</b>\n\n%s", _("Alarm process runing"), _("Do you want to exit anyway?"));
	l = gtk_label_new ("");
	gtk_label_set_markup (GTK_LABEL (l), tmp);
	gtk_box_pack_start (GTK_BOX(h1), i, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX(h1), l, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX(content), h1, FALSE, FALSE, 0);
	add_button_helper (GTK_DIALOG (m), _("Yes"), YES_BUTTON);
	add_button_helper (GTK_DIALOG (m), _("No"), NO_BUTTON);
	gtk_widget_show_all (m);
	if (gtk_dialog_run (GTK_DIALOG (m)) == GTK_RESPONSE_YES) {
		response = TRUE;
	} else {
		response = FALSE;
	}
	g_free (tmp);
	g_object_unref (pb);
	gtk_widget_destroy (m);
	return response;
}
