#include "callbacks.h"

enum { FORMAT_MP3, FORMAT_MP3_BEST, FORMAT_VIDEO, FORMAT_3GP, FORMAT_FACEBOOK };
enum { UNUSED, LEFT_CLICK, MIDDLE_CLICK, RIGHT_CLICK };

void view_popup_menu_onDoSomething (GtkWidget *menuitem, gchar *_url) {
	GtkClipboard *clip;
	clip = gtk_clipboard_get (GDK_SELECTION_CLIPBOARD);
	gtk_clipboard_set_text (clip, _url, -1);
	g_free (_url);
}

gboolean current_item_popup (GtkTreeView *_tv, GdkEventButton *event) {
	GtkTreePath *path;
	gboolean state;
	if (gtk_tree_view_get_path_at_pos (_tv, event->x, event->y, &path, NULL, NULL, NULL)) {
		GtkWidget *menu;
		GtkWidget *item_copy;
		GtkTreeModel *model;
		GtkTreeIter iter;
		gchar *url;
		model = gtk_tree_view_get_model (_tv);
		gtk_tree_model_get_iter (model, &iter, path);
		gtk_tree_model_get (model, &iter, 1, &url, -1);
		menu = gtk_menu_new ();
		item_copy = gtk_image_menu_item_new_from_stock (GTK_STOCK_COPY, NULL);
		g_signal_connect (item_copy, "activate", G_CALLBACK (view_popup_menu_onDoSomething), url);
		gtk_menu_shell_append (GTK_MENU_SHELL(menu), item_copy);
		gtk_widget_show_all (menu);
		gtk_menu_popup (GTK_MENU (menu), NULL, NULL, NULL, NULL, (event != NULL) ? event->button : UNUSED, gdk_event_get_time ((GdkEvent*)event));
		state = FALSE;
		gtk_tree_path_free (path);
	} else {
		state = TRUE;
	}
	return state;
}

GPid spawned_to_terminal (VteTerminal *vteterminal, const gchar *cmd_line, const gchar *url, const gchar *output_dir) {
	GString *tmp;
	GPid _pid;
	gchar **cmds;
	tmp = g_string_new (cmd_line);
	g_string_append (tmp, url);
	g_print ("Executed: %s\n", tmp->str);
	g_shell_parse_argv (tmp->str, NULL, &cmds, NULL);
	_pid = vte_terminal_fork_command_full (vteterminal, VTE_PTY_DEFAULT, output_dir, cmds, NULL, G_SPAWN_SEARCH_PATH, NULL, NULL, NULL, NULL);
	g_string_free (tmp, TRUE);
	g_strfreev (cmds);
	return _pid;
}

gint oops_dialog (GtkWindow *parent) {
	GtkWidget *m;
	gint value;
	m = gtk_message_dialog_new_with_markup (parent, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_WARNING, GTK_BUTTONS_YES_NO, "<b>%s:</b>", _("A youtube-dl process is running"));
	gtk_window_set_title (GTK_WINDOW (m), gtk_window_get_title (parent));
	gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (m), "%s", _("Exit the application will generate a corrupted file, do you want exit anyway?"));
	value = gtk_dialog_run (GTK_DIALOG (m));
	gtk_widget_destroy (m);
	return value;
}

void toggle_sensitive (GtkWidget *child) {
	gboolean state = gtk_widget_get_sensitive (child);
	gtk_widget_set_sensitive (child, !state);
}

// added 14.01.2015 for version 1.3
gboolean treeview1_button_press_event_cb (GtkTreeView *tv, GdkEventButton *event, LPDATAINFO data) {
	switch (event->button) {
		case RIGHT_CLICK:
		{
			return current_item_popup (tv, event);
		}
	}
	return FALSE;
}

void on_window1_destroy(GtkWindow *widget, LPDATAINFO data) {
	gtk_main_quit();
}

void on_comboboxtext1_changed (GtkComboBoxText *combo_text, LPDATAINFO data) {
	data->combo_pos = gtk_combo_box_get_active (GTK_COMBO_BOX (combo_text));
	gint _dir_name[] = {
		G_USER_DIRECTORY_MUSIC,
		G_USER_DIRECTORY_MUSIC,
		G_USER_DIRECTORY_VIDEOS,
		G_USER_DIRECTORY_VIDEOS,
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
	pixbuf = gdk_pixbuf_new_from_file_at_size (DATA_DIR "/wait.png", 16, 16, NULL);
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
	gboolean response;
	g_signal_emit_by_name (data->toplevel, "delete-event", data, &response);
	if (!response) {
		gtk_widget_destroy (data->toplevel);
	}
}

void on_button4_clicked (GtkButton *button, LPDATAINFO data) {
	data->total = gtk_tree_model_iter_n_children (GTK_TREE_MODEL (data->model_combo), NULL);
	if (data->total) {
		gchar *poop;
		gchar *url;
		GtkTreeIter iter;
		toggle_sensitive (data->child1);
		gtk_tree_model_iter_nth_child (GTK_TREE_MODEL (data->model_combo), &iter, NULL, data->pos);
		gtk_tree_model_get (GTK_TREE_MODEL (data->model_combo), &iter, 1, &url, -1);
		data->_str = g_string_new (Y_PATH);
		switch (data->combo_pos) {
			case FORMAT_MP3:
			{
				poop = g_strdup_printf (" -f 17 --extract-audio --audio-format mp3 --audio-quality %ik ", data->audio_bit);
				g_string_append (data->_str, poop);
				break;
			}
			case FORMAT_MP3_BEST:
			{
				poop = g_strdup_printf (" -f best --extract-audio --audio-format mp3 --audio-quality 320k ", data->audio_bit);
				g_string_append (data->_str, poop);
				break;
			}
			case FORMAT_VIDEO:
			{
				poop = g_strdup_printf ((data->video_format == -1) ? " -f best " : "-f %i ",  data->video_format);
				g_string_append (data->_str, poop);
				break;
			}
			case FORMAT_3GP:
			{
				poop = g_strdup_printf (" -f %i ", data->video_format);
				g_string_append (data->_str, poop);
				break;
			}
			case FORMAT_FACEBOOK:
			{
				// no options available
				poop = g_strdup_printf (" ");
				g_string_append (data->_str, poop);
				break;
			}
		}
		g_free (poop);
		if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (data->check1))) {
			g_string_append (data->_str, "-u ");
			g_string_append (data->_str, gtk_entry_get_text (GTK_ENTRY (data->user_text)));
			g_string_append (data->_str, " -p \"");
			g_string_append (data->_str, gtk_entry_get_text (GTK_ENTRY (data->pass_text)));
			g_string_append (data->_str, "\" "); // we need space to avoid string concatenation with url
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
	img = g_build_filename (DATA_DIR, status ? "error.png" : "download.png", NULL);
	pixbuf = gdk_pixbuf_new_from_file_at_size (img, 16, 16, NULL);
	gtk_tree_model_iter_nth_child (GTK_TREE_MODEL (data->model_combo), &iter, NULL, data->pos);
	gtk_list_store_set (data->model_combo, &iter, 0, pixbuf, -1);
	g_free (img);
	g_object_unref (pixbuf);
	data->pos++;
	g_spawn_close_pid (data->pid);
	data->pid = -1;
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

gboolean on_window1_delete_event (GtkWindow *widget, GdkEvent *event, LPDATAINFO data) {
	if (data->pid > 0) {
		gint response;
		response = oops_dialog (widget);
		if (response != GTK_RESPONSE_YES) {
			return TRUE;
		} else {
			return FALSE;
		}
	}
	return FALSE;
}
