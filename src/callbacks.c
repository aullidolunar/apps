#include "callbacks.h"

void on_window1_destroy(GtkWidget *object, LPDATAINFO data) {
	gtk_main_quit();
}

void on_comboboxtext1_changed (GtkComboBoxText *combo_text, LPDATAINFO data) {
	data->combo_pos = gtk_combo_box_get_active (GTK_COMBO_BOX (combo_text));
	gint _dir_name[] = {
		G_USER_DIRECTORY_MUSIC,
		G_USER_DIRECTORY_VIDEOS,
		G_USER_DIRECTORY_DOWNLOAD,
		G_USER_DIRECTORY_VIDEOS
	};
	gtk_entry_set_text (GTK_ENTRY (data->output_dir), g_get_user_special_dir (_dir_name[data->combo_pos]));
}

void on_checkbutton1_toggled (GtkToggleButton *togglebutton, LPDATAINFO data) {
	gboolean state = gtk_toggle_button_get_active (togglebutton);
	gtk_widget_set_sensitive (data->child2, state);
}

void on_button1_clicked (GtkButton *button, LPDATAINFO data) {
	GdkPixbuf *pixbuf;
	GtkTreeIter iter;
	const gchar* url;
	url = gtk_entry_get_text (GTK_ENTRY (data->url_text));
	gtk_list_store_append (data->model_combo, &iter);
	pixbuf = gdk_pixbuf_new_from_file_at_size (RES_DIR "/wait.png", 16, 16, NULL);
	gtk_list_store_set (data->model_combo, &iter, 0, pixbuf, 1, url, -1);
	gtk_entry_set_text (GTK_ENTRY (data->url_text), "");
	gtk_widget_set_sensitive (data->ok_button, TRUE);
	g_object_unref (pixbuf);
}

void on_entry1_changed (GtkEntry *url_text, LPDATAINFO data) {
	gint len = gtk_entry_get_text_length (url_text);
	gtk_widget_set_sensitive (data->add_button, (gboolean)len);
}
