#include "callbacks.h"

gint msg_box (GtkWindow *parent, GtkMessageType type, GtkButtonsType buttons, const gchar *h, const gchar *b) {
	GtkWidget *dialog = gtk_message_dialog_new_with_markup (parent, GTK_DIALOG_DESTROY_WITH_PARENT, type, buttons, "<b>%s</b>", h);
	gint response = 0;
	gtk_window_set_title (GTK_WINDOW (dialog), PACKAGE_STRING);
	gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), b);
	response = gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);
	return response;
}

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

void toggle_ui (GtkWidget *tv, GtkWidget *b) {
	const gchararray button_params[][2] = {
		{"gtk-execute", _("Launch SLim with current selected theme")},
		{"gtk-close", _("Close SLim instance")}
	};
	gboolean state;
	state = gtk_widget_get_sensitive (tv);
	gtk_button_set_label (GTK_BUTTON (b), button_params[state][0]);
	gtk_widget_set_tooltip_text (b, button_params[state][1]);
	gtk_widget_set_sensitive (tv, !state);
}

void watcher (GPid pid, gint status, gpointer d) {
	LPAPPINFO ai = (LPAPPINFO)d;
	g_spawn_close_pid (pid);
	ai->_pid = 0;
	toggle_ui (ai->tree_view, ai->button);
}

void on_window1_destroy (GtkWindow *window, LPAPPINFO ai) {
	gtk_main_quit ();
}

void on_button1_clicked (GtkButton *button, LPAPPINFO ai) {
	gboolean state = gtk_widget_get_sensitive (ai->tree_view);
	if (state) {
		GtkTreeView *tv = GTK_TREE_VIEW (ai->tree_view);
		GtkTreeViewColumn *column;
		GtkTreePath *path;
		gtk_tree_view_get_cursor (tv, &path, &column);
		if (path) {
			gtk_tree_view_row_activated (tv, path, column);
			gtk_tree_path_free (path);
		}
		gtk_widget_set_sensitive (ai->tree_view, FALSE);
	} else {
		kill (ai->_pid, 9);
		ai->_pid = 0;
	}
}

void on_button2_clicked (GtkButton *button, LPAPPINFO ai) {
	GtkTreeView *tv = GTK_TREE_VIEW (ai->tree_view);
	GtkTreeViewColumn *column;
	GtkTreePath *path;
	gchar *body;
	gtk_tree_view_get_cursor (tv, &path, &column);
	if (path) {
		GtkClipboard *clip;
		GtkTreeIter iter;
		gchar *theme;
		clip = gtk_clipboard_get (GDK_SELECTION_CLIPBOARD);
		gtk_tree_model_get_iter (GTK_TREE_MODEL (ai->model_sort), &iter, path);
		gtk_tree_model_get (GTK_TREE_MODEL (ai->model_sort), &iter, 1, &theme, -1);
		gtk_clipboard_set_text (clip, theme, -1);
		body = g_strdup_printf ("%s: %s", _("Theme name copied to clipboard"), theme);
		g_free (theme);
		gtk_tree_path_free (path);
	} else {
		body = g_strdup_printf (_("No theme name was selected"));
	}
	msg_box (GTK_WINDOW (ai->window), GTK_MESSAGE_INFO, GTK_BUTTONS_CLOSE, _("Clipboard information"), body);
	g_free (body);
}

void on_button3_clicked (GtkButton *button, LPAPPINFO ai) {
	gboolean retState;
	g_signal_emit_by_name (ai->window, "delete-event", ai, &retState, NULL);
	if (!retState) gtk_widget_destroy (ai->window);
}

void on_treeview1_row_activated (GtkTreeView *tv, GtkTreePath *path, GtkTreeViewColumn *column, LPAPPINFO ai) {
	GtkTreeModel *model_sort = GTK_TREE_MODEL (ai->model_sort);
	GError *error = NULL;
	GtkTreeIter iter;
	gboolean ret;
	gchar *str;
	gchar *cmd;
	gchar **cmd_to_spawn;
	GPid pid;
	gtk_tree_model_get_iter (model_sort, &iter, path);
	gtk_tree_model_get (model_sort, &iter, 1, &str, -1);
	cmd = g_strdup_printf ("%s -p %s%s%s", SLIM_PATH, SLIM_THEMES_DIR, G_DIR_SEPARATOR_S, str);
	g_shell_parse_argv (cmd, NULL, &cmd_to_spawn, NULL);
	ret = g_spawn_async (NULL, cmd_to_spawn, NULL, G_SPAWN_SEARCH_PATH|G_SPAWN_DO_NOT_REAP_CHILD|G_SPAWN_STDOUT_TO_DEV_NULL|G_SPAWN_STDERR_TO_DEV_NULL, NULL, NULL, &pid, &error);
	if (!ret) {
		g_print ("Error: %s\n", error->message);
		g_clear_error (&error);
	} else {
		toggle_ui (ai->tree_view, ai->button);
		g_child_watch_add (pid, watcher, ai);
		ai->_pid = pid;
	}
	g_strfreev (cmd_to_spawn);
	g_free (cmd);
	g_free (str);
}

gboolean on_treeview1_key_press_event (GtkTreeView *tv, GdkEventKey *event, LPAPPINFO ai) {
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

gboolean on_window1_delete_event (GtkWindow *win, GdkEvent *event, LPAPPINFO ai) {
	gboolean retState = FALSE;
	if (ai->_pid) {
		gint response = msg_box (win, GTK_MESSAGE_WARNING, GTK_BUTTONS_YES_NO, _("SLim is still running!"), _("Are you sure you want to exit?"));
		if (response == GTK_RESPONSE_YES) {
			kill (ai->_pid, 9);
			ai->_pid = 0;
		} else {
			retState = TRUE;
		}
	}
	return retState;
}
