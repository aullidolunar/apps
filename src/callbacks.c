#include "callbacks.h"

GPid spawned_to_terminal (VteTerminal *vteterminal, const gchar *cmd_line, const gchar *url, const gchar *output_dir) {
	GString *tmp;
	GPid _pid;
	gchar **cmds;
	tmp = g_string_new (cmd_line);
	g_string_append (tmp, url);
	g_shell_parse_argv (tmp->str, NULL, &cmds, NULL);
	_pid = vte_terminal_fork_command_full (vteterminal, VTE_PTY_DEFAULT, output_dir, cmds, NULL, G_SPAWN_SEARCH_PATH, NULL, NULL, NULL, NULL);
	g_string_free (tmp, TRUE);
	g_strfreev (cmds);
	return _pid;
}

void toggle_sensitive (GtkWidget *child) {
	gboolean state = gtk_widget_get_sensitive (child);
	gtk_widget_set_sensitive (child, !state);
}

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

void on_button2_clicked (GtkButton *button, LPDATAINFO data) {
	data->combo_pos = 0;
	gtk_widget_set_sensitive (data->add_button, FALSE);
	gtk_widget_set_sensitive (data->ok_button, FALSE);
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (data->check1), FALSE);		
	gtk_combo_box_set_active (GTK_COMBO_BOX (data->combo1), data->combo_pos);
	gtk_entry_set_text (GTK_ENTRY (data->url_text), "");
	gtk_entry_set_text (GTK_ENTRY (data->user_text), "");
	gtk_entry_set_text (GTK_ENTRY (data->pass_text), "");
	gtk_list_store_clear (data->model_combo);
	vte_terminal_reset (VTE_TERMINAL (data->terminal), TRUE, TRUE);
}

void on_button3_clicked (GtkButton *button, LPDATAINFO data) {
	gtk_widget_destroy (data->toplevel);
}

void on_button4_clicked (GtkButton *button, LPDATAINFO data) {
	data->total = gtk_tree_model_iter_n_children (GTK_TREE_MODEL (data->model_combo), NULL);
	if (data->total) {
		gchar *url;
		GtkTreeIter iter;
		toggle_sensitive (data->child1);
		gtk_tree_model_iter_nth_child (GTK_TREE_MODEL (data->model_combo), &iter, NULL, data->pos);
		gtk_tree_model_get (GTK_TREE_MODEL (data->model_combo), &iter, 1, &url, -1);
		data->_str = g_string_new (params[data->combo_pos]);
		if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (data->check1))) {
			g_string_append (data->_str, "--username");
			g_string_append (data->_str, gtk_entry_get_text (GTK_ENTRY (data->user_text)));
			g_string_append (data->_str, "--password");
			g_string_append (data->_str, gtk_entry_get_text (GTK_ENTRY (data->pass_text)));
		}
		data->pid = spawned_to_terminal (VTE_TERMINAL(data->terminal), data->_str->str, url, gtk_entry_get_text (GTK_ENTRY (data->output_dir)));
		g_free (url);
	}
}

void child_exited (VteTerminal *vteterminal, LPDATAINFO data) {
	GtkTreeIter iter;
	GdkPixbuf *pixbuf;
	gchar *img;
	gint status;
	status = vte_terminal_get_child_exit_status (vteterminal);
	img = g_build_filename (RES_DIR, status ? "error.png" : "download.png", NULL);
	pixbuf = gdk_pixbuf_new_from_file_at_size (img, 16, 16, NULL);
	gtk_tree_model_iter_nth_child (GTK_TREE_MODEL (data->model_combo), &iter, NULL, data->pos);
	gtk_list_store_set (data->model_combo, &iter, 0, pixbuf, -1);
	g_free (img);
	g_object_unref (pixbuf);
	data->pid = 0;
	data->pos++;
	if (data->pos < data->total) {
		gchar *url;
		GtkTreeIter iter;
		gtk_tree_model_iter_nth_child (GTK_TREE_MODEL (data->model_combo), &iter, NULL, data->pos);
		gtk_tree_model_get (GTK_TREE_MODEL (data->model_combo), &iter, 1, &url, -1);
		data->pid = spawned_to_terminal (VTE_TERMINAL(data->terminal), data->_str->str, url, gtk_entry_get_text (GTK_ENTRY (data->output_dir)));
		g_free (url);
	} else {
		toggle_sensitive (data->child1);
		g_string_free (data->_str, TRUE);
		data->pos = 0;
	}
}
