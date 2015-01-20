#include "callbacks.h"

gboolean move_item (GtkTreeView *tv, gint where_to_move) {
	GtkTreeSelection *selection = gtk_tree_view_get_selection (tv);
	GtkTreeModel *modelParent;
	GtkTreeIter iter;
	if (gtk_tree_selection_get_selected (selection, &modelParent, &iter)) {
		GtkTreePath *path;
		if (where_to_move == SELECTION_MOVE_UP) { // up
			path = gtk_tree_model_get_path (modelParent, &iter);
			if (!gtk_tree_path_prev (path)) {
				gint total = gtk_tree_model_iter_n_children (modelParent, NULL);
				gtk_tree_path_free (path);
				path = gtk_tree_path_new_from_indices (total-1, -1);
			}
		} else { // down
			if (gtk_tree_model_iter_next (modelParent, &iter)) {
				path = gtk_tree_model_get_path (modelParent, &iter);
			} else {
				path = gtk_tree_path_new_first ();
			}
		}
		gtk_tree_view_scroll_to_cell (tv, path, NULL, FALSE, 0.0, 0.0);
		gtk_tree_view_set_cursor (tv, path, NULL, FALSE);
		gtk_tree_path_free (path);
	}
	return TRUE;
}

GPid spawned_to_terminal (VteTerminal *vteterminal, int op_type, const gchar *url, const gchar *output_dir, int audio, int video, gboolean userCredentials, const gchar *strUser, const gchar* strPass) {
	GPid _pid;
	gchar *poop;
	gchar **cmds;
	GString *tmp;
	
	tmp = g_string_new (Y_PATH);
	
	/* changed in favor for 2.0 */
	switch (op_type) {
		case FORMAT_MP3:
		{
			poop = g_strdup_printf (" -f 17 --extract-audio --audio-format mp3 --audio-quality %ik ", audio);
			break;
		}
		case FORMAT_MP3_BEST:
		{
			poop = g_strdup_printf (" -f best --extract-audio --audio-format mp3 --audio-quality 320k ", audio);
			break;
		}
		case FORMAT_VIDEO:
		{
			poop = g_strdup_printf ((video == -1) ? " -f best " : "-f %i ", video);
			break;
		}
		case FORMAT_3GP:
		{
			poop = g_strdup_printf (" -f %i ", video == -1 ? 17 : video);
			break;
		}
		case FORMAT_FACEBOOK:
		{
			// no options available
			poop = g_strdup_printf (" ");
			break;
		}
	}
	g_string_append (tmp, poop);
	g_free (poop);
	g_string_append (tmp, url);
	if (userCredentials) {
		g_string_append (tmp, " -u \"");
		g_string_append (tmp, strUser);
		g_string_append (tmp, "\" -p \"");
		g_string_append (tmp, strPass);
		g_string_append (tmp, "\"");
	}
#ifdef ENABLE_DEBUG
	g_print ("Executed: [%s]\n", tmp->str);
#endif
	g_shell_parse_argv (tmp->str, NULL, &cmds, NULL);
	_pid = vte_terminal_fork_command_full (vteterminal, VTE_PTY_DEFAULT, output_dir, cmds, NULL, G_SPAWN_SEARCH_PATH, NULL, NULL, NULL, NULL);
	g_string_free (tmp, TRUE);
	g_strfreev (cmds);
	return _pid;
}

void view_popup_menu_oncopy (GtkWidget *menuitem, gchar *_url) {
	GtkClipboard *clip;
	clip = gtk_clipboard_get (GDK_SELECTION_CLIPBOARD);
	gtk_clipboard_set_text (clip, _url, -1);
	g_free (_url);
}

void on_liststore1_row_deleted (GtkTreeModel *tree_model, GtkTreePath *path, LPDATAINFO data) {
	gint total;
	total = gtk_tree_model_iter_n_children (tree_model, NULL);
	if (!total) gtk_button_clicked (GTK_BUTTON (data->clean_button));
}

/* added in 2.0 */
void view_popup_menu_onremove (GtkWidget *menuitem, GtkTreeView *tv) {
	GtkTreeSelection *selection;
	GtkTreeModel *model;
	GtkTreeIter iter;
	selection = gtk_tree_view_get_selection (tv);
	if (gtk_tree_selection_get_selected (selection, &model, &iter)) {
		gtk_list_store_remove (GTK_LIST_STORE (model), &iter);
	}
}

gboolean cb_each (GtkTreeModel *model, GtkTreePath *path, GtkTreeIter *iter, LPREMOVEDATA lprd) {
	gboolean retVal;
	gtk_tree_model_get (model, iter, 5, &retVal, -1);
	if (retVal == lprd->refState) {
		GtkTreeRowReference *rowref;
		rowref = gtk_tree_row_reference_new (model, path);
		lprd->refNode = g_list_append (lprd->refNode, rowref);
	}
	return FALSE;
}

void view_popup_menu_onremovefailed (GtkWidget *menuitem, GtkTreeModel *model) {
	GList *node;
	RemoveData rd;
	rd.refNode = NULL;
	rd.refState = FALSE;
	gtk_tree_model_foreach (model, (GtkTreeModelForeachFunc)cb_each, &rd);
	for (node = rd.refNode; node != NULL; node = node->next) {
		GtkTreePath *path;
		path = gtk_tree_row_reference_get_path ((GtkTreeRowReference*)node->data);
        if (path) {
           GtkTreeIter  iter;
           if (gtk_tree_model_get_iter (model, &iter, path)) {
			   gtk_list_store_remove (GTK_LIST_STORE (model), &iter);
           }
           gtk_tree_path_free (path);
        }
     }
     g_list_foreach (rd.refNode, (GFunc) gtk_tree_row_reference_free, NULL);
     g_list_free (rd.refNode);
}

void view_popup_menu_onremovesucceeded (GtkWidget *menuitem, GtkTreeModel *model) {
	GList *node;
	RemoveData rd;
	rd.refNode = NULL;
	rd.refState = TRUE;
	gtk_tree_model_foreach (model, (GtkTreeModelForeachFunc)cb_each, &rd);
	for (node = rd.refNode; node != NULL; node = node->next) {
		GtkTreePath *path;
		path = gtk_tree_row_reference_get_path ((GtkTreeRowReference*)node->data);
        if (path) {
           GtkTreeIter  iter;
           if (gtk_tree_model_get_iter (model, &iter, path)) {
			   gtk_list_store_remove (GTK_LIST_STORE (model), &iter);
           }
           gtk_tree_path_free (path);
        }
     }
     g_list_foreach (rd.refNode, (GFunc) gtk_tree_row_reference_free, NULL);
     g_list_free (rd.refNode);
}

gboolean current_item_popup (GtkTreeView *_tv, GtkButton *button_clean, GdkEventButton *event) {
	GtkTreePath *path;
	GtkTreeModel *model;
	gboolean state;
	GtkWidget *menu;
	GtkWidget *item_remove_all;
	GtkWidget *item_remove_succeeded;
	GtkWidget *wii;
	GtkWidget *wii2;
	
	menu = gtk_menu_new ();
	model = gtk_tree_view_get_model (_tv);
	if (gtk_tree_view_get_path_at_pos (_tv, event->x, event->y, &path, NULL, NULL, NULL)) {
		GtkWidget *item_copy;
		GtkWidget *item_remove;
		GtkTreeIter iter;
		gchar *url;		
		gtk_tree_model_get_iter (model, &iter, path);
		gtk_tree_model_get (model, &iter, 1, &url, -1);
		item_copy = gtk_image_menu_item_new_from_stock (GTK_STOCK_COPY, NULL);
		item_remove = gtk_image_menu_item_new_from_stock (GTK_STOCK_REMOVE, NULL);
		g_signal_connect (item_copy, "activate", G_CALLBACK (view_popup_menu_oncopy), url);
		g_signal_connect (item_remove, "activate", G_CALLBACK (view_popup_menu_onremove), _tv);
		gtk_menu_shell_append (GTK_MENU_SHELL(menu), item_copy);
		gtk_menu_shell_append (GTK_MENU_SHELL(menu), item_remove);
		gtk_menu_shell_append (GTK_MENU_SHELL(menu), gtk_separator_menu_item_new ());
		state = FALSE;
		if (path) gtk_tree_path_free (path);
	} else {
		state = TRUE;
	}
	item_remove_all = gtk_image_menu_item_new_with_label (_("Remove failed"));
	g_signal_connect (item_remove_all, "activate", G_CALLBACK (view_popup_menu_onremovefailed), model);
	item_remove_succeeded = gtk_image_menu_item_new_with_label (_("Remove succeeded"));
	g_signal_connect (item_remove_succeeded, "activate", G_CALLBACK (view_popup_menu_onremovesucceeded), model);
	wii = gtk_image_new_from_pixbuf (gtk_widget_render_icon (GTK_WIDGET (_tv), GTK_STOCK_REMOVE, GTK_ICON_SIZE_MENU, NULL));
	wii2 = gtk_image_new_from_pixbuf (gtk_widget_render_icon (GTK_WIDGET (_tv), GTK_STOCK_REMOVE, GTK_ICON_SIZE_MENU, NULL));
	gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (item_remove_all), wii);
	gtk_image_menu_item_set_image (GTK_IMAGE_MENU_ITEM (item_remove_succeeded), wii2);
	
	gtk_menu_shell_append (GTK_MENU_SHELL(menu), item_remove_all);
	gtk_menu_shell_append (GTK_MENU_SHELL(menu), item_remove_succeeded);
	gtk_widget_show_all (menu);
	gtk_menu_popup (GTK_MENU (menu), NULL, NULL, NULL, NULL, (event != NULL) ? event->button : UNUSED_1, gdk_event_get_time ((GdkEvent*)event));
	return state;
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
			// display a nice context menu
			gint items = gtk_tree_model_iter_n_children (gtk_tree_view_get_model (tv), NULL);
			if (items) return current_item_popup (tv, GTK_BUTTON (data->clean_button), event);
			return FALSE;
		}
	}
	return FALSE;
}

gboolean on_treeview1_key_press_event (GtkTreeView *tv, GdkEventKey *event, LPDATAINFO data) {
	switch (event->keyval)
	{
		case GDK_KEY_Up:
		{
			return move_item (tv, SELECTION_MOVE_UP);
		}
		case GDK_KEY_Down:
		{
			return move_item (tv, SELECTION_MOVE_DOWN);
		}
	}
	return FALSE;
}

void on_window1_destroy(GtkWindow *widget, LPDATAINFO data) {
	gtk_main_quit();
}

void on_comboboxtext1_changed (GtkComboBoxText *combo_text, LPDATAINFO data) {
	data->combo_pos = gtk_combo_box_get_active (GTK_COMBO_BOX (combo_text));
}

void on_checkbutton1_toggled (GtkToggleButton *togglebutton, LPDATAINFO data) {
	gboolean state = gtk_toggle_button_get_active (togglebutton);
	gtk_widget_set_sensitive (data->child2, state);
}

void on_button1_clicked (GtkButton *button, LPDATAINFO data) {
	GdkPixbuf *pixbuf;
	GtkTreeModel *model_combo;
	GtkTreeIter iter;
	GtkTreeIter iter_combo;
	const gchar* url;
	gchar *op;
	url = gtk_entry_get_text (GTK_ENTRY (data->url_text));
	gtk_list_store_append (data->model_tv, &iter);
	pixbuf = gdk_pixbuf_new_from_file_at_size (DATA_DIR "/wait.png", 16, 16, NULL);
	/* added in 2.0 */
	model_combo = gtk_combo_box_get_model (GTK_COMBO_BOX (data->combo1));
	gtk_tree_model_iter_nth_child (model_combo, &iter_combo, NULL, data->combo_pos);
	gtk_tree_model_get (model_combo, &iter_combo, 0, &op, -1);
	gtk_list_store_set (data->model_tv, &iter, 0, pixbuf, 1, url, 2, g_get_user_special_dir (out_paths[data->combo_pos]), 3, op, 4, data->combo_pos, 5, TRUE, -1);
	gtk_entry_set_text (GTK_ENTRY (data->url_text), "");
	gtk_widget_set_sensitive (data->ok_button, TRUE);
	g_free (op);
	g_object_unref (pixbuf);
}

void on_entry1_changed (GtkEntry *url_text, LPDATAINFO data) {
	gint len = gtk_entry_get_text_length (url_text);
	gtk_widget_set_sensitive (data->add_button, (gboolean)len);
}

void on_button2_clicked (GtkButton *button, LPDATAINFO data) {
	data->combo_pos = FORMAT_MP3_BEST;
	gtk_widget_set_sensitive (data->add_button, FALSE);
	gtk_widget_set_sensitive (data->ok_button, FALSE);
	gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (data->check1), FALSE);		
	gtk_combo_box_set_active (GTK_COMBO_BOX (data->combo1), data->combo_pos);
	gtk_entry_set_text (GTK_ENTRY (data->url_text), "");
	gtk_entry_set_text (GTK_ENTRY (data->user_text), "");
	gtk_entry_set_text (GTK_ENTRY (data->pass_text), "");
	gtk_list_store_clear (data->model_tv);
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
	data->total = gtk_tree_model_iter_n_children (GTK_TREE_MODEL (data->model_tv), NULL);
	if (data->total) {
		gint op;
		gchar *url;
		gchar *out_dir;
		GtkTreeIter iter;
		toggle_sensitive (data->child1);
		gtk_tree_model_iter_nth_child (GTK_TREE_MODEL (data->model_tv), &iter, NULL, data->pos);
		gtk_tree_model_get (GTK_TREE_MODEL (data->model_tv), &iter, 1, &url, 2, &out_dir, 4, &op, -1);
		data->pid = spawned_to_terminal (
			VTE_TERMINAL (data->terminal),
			op,
			url,
			out_dir,
			data->audio_bit,
			data->video_format,
			gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (data->check1)),
			gtk_entry_get_text (GTK_ENTRY (data->user_text)),
			gtk_entry_get_text (GTK_ENTRY (data->pass_text))
		);
		g_free (out_dir);
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
	gtk_tree_model_iter_nth_child (GTK_TREE_MODEL (data->model_tv), &iter, NULL, data->pos);
	gtk_list_store_set (data->model_tv, &iter, 0, pixbuf, 5, status ? FALSE : TRUE, -1);
	g_free (img);
	g_object_unref (pixbuf);
	data->pos++;
	g_spawn_close_pid (data->pid);
	data->pid = -1;
	if (data->pos < data->total) {
		gint op;
		gchar *url;
		gchar *out_dir;
		GtkTreeIter iter;
		gtk_tree_model_iter_nth_child (GTK_TREE_MODEL (data->model_tv), &iter, NULL, data->pos);
		gtk_tree_model_get (GTK_TREE_MODEL (data->model_tv), &iter, 1, &url, 2, &out_dir, 4, &op, -1);
		data->pid = spawned_to_terminal (
			VTE_TERMINAL (data->terminal),
			op,
			url,
			out_dir,
			data->audio_bit,
			data->video_format,
			gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (data->check1)),
			gtk_entry_get_text (GTK_ENTRY (data->user_text)),
			gtk_entry_get_text (GTK_ENTRY (data->pass_text))
		);
		g_free (out_dir);
		g_free (url);
	} else {
		toggle_sensitive (data->child1);
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
