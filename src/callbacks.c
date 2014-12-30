#include "callbacks.h"

void on_window1_destroy (GtkWindow *window, LPAPPINFO ai) {
	gtk_main_quit ();
}

gboolean on_window1_delete_event (GtkWindow *window, GdkEvent* event, LPAPPINFO ai) {
	gboolean state = gtk_widget_get_sensitive (ai->centerWidget);
	if (!state) {
		return !notify_bye_bye (window, _("do you want to exit application anyway?"));
	}
	return FALSE;
}

void on_toolbutton1_clicked (GtkToolButton *b, LPAPPINFO ai) {
	gboolean state = gtk_widget_get_sensitive (ai->centerWidget);
	if (!state) {
		state = !notify_bye_bye (GTK_WINDOW (ai->window), _("do still you want to abort the operation?"));
		if (!state) {
			toggle_tool_button (b, TRUE);
			gtk_widget_set_sensitive (ai->centerWidget, TRUE);
			set_status_msg (GTK_LABEL (ai->status_text), GTK_IMAGE (ai->status_icon), _("Convertion aborted"), FALSE);
			kill (ai->pid, 9);
		}
	} else {
		GtkTreeModel *model;
		GtkTreeIter iter;
		gint pos;
		gchar *directory;
		gint total;
		pos = gtk_combo_box_get_active (GTK_COMBO_BOX (ai->combo1));
		model = gtk_combo_box_get_model (GTK_COMBO_BOX (ai->combo1));
		gtk_tree_model_iter_nth_child (model, &iter, NULL, pos);
		gtk_tree_model_get (model, &iter, 2, &directory, -1);
		total = read_files (directory, &ai->list);
#ifdef ENABLE_DEBUG
		g_print ("We should see same total: %i\n", total);
#endif
		if (total) {
#ifdef ENABLE_DEBUG
			g_print ("If items, we should be here by now\n");
#endif
			ai->total = total;
			ai->current = 0;
			toggle_tool_button (b, FALSE);
			gtk_widget_set_sensitive (ai->centerWidget, FALSE);
			set_status_msg (GTK_LABEL (ai->status_text), GTK_IMAGE (ai->status_icon), _("Starting convertion..."), TRUE);
			/* run stuff here */
			preprocess_runner (ai);
		} else {
			set_status_msg (GTK_LABEL (ai->status_text), GTK_IMAGE (ai->status_icon), _("No files to convert"), FALSE);
		}
		g_free (directory);
	}
}

void on_toolbutton3_clicked (GtkToolButton *b, LPAPPINFO ai) {
	gboolean state = gtk_widget_get_sensitive (ai->centerWidget);
	gboolean ret;
	g_signal_emit_by_name (ai->window, "delete-event", ai, &ret);
	if (!ret) {
		kill (ai->pid, 9);
		gtk_widget_destroy (ai->window);
	}
}

void on_checkbutton1_toggled (GtkToggleButton *button, LPAPPINFO ai) {
	ai->deleteMe = gtk_toggle_button_get_active (button);
}

void on_combobox1_changed (GtkComboBox *c, LPAPPINFO ai) {
	gint s1 = gtk_combo_box_get_active (c);
	gint s2 = gtk_combo_box_get_active (GTK_COMBO_BOX (ai->combo2));
	gint s3 = gtk_combo_box_get_active (GTK_COMBO_BOX (ai->combo3));
	gtk_widget_set_sensitive (ai->tool1, (s1 && s2 && s3));
}

void on_combobox2_changed (GtkComboBox *c, LPAPPINFO ai) {
	gint s1 = gtk_combo_box_get_active (GTK_COMBO_BOX (ai->combo1));
	gint s2 = gtk_combo_box_get_active (c);
	gint s3 = gtk_combo_box_get_active (GTK_COMBO_BOX (ai->combo3));
	gtk_widget_set_sensitive (ai->tool1, (s1 && s2 && s3));
}

void on_combobox3_changed (GtkComboBox *c, LPAPPINFO ai) {
	gint s1 = gtk_combo_box_get_active (GTK_COMBO_BOX (ai->combo1));
	gint s2 = gtk_combo_box_get_active (GTK_COMBO_BOX (ai->combo2));
	gint s3 = gtk_combo_box_get_active (c);
	gtk_widget_set_sensitive (ai->tool1, (s1 && s2 && s3));
}
