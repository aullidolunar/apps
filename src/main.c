#include "main.h"

gchar * get_current_slim_theme (const gchar *slim_config) {
	gchar *tmp;
	config_t cfg;
	config_setting_t *setting;
	config_init (&cfg);
	if (!config_read_file (&cfg, slim_config)) {
		g_print ("Error %s %s: %s\n", _("parsing"), slim_config, config_error_text (&cfg));
		tmp = NULL;
	} else {
		const gchar *str;
		config_lookup_string (&cfg, "current_theme", &str);
		tmp = g_strdup (str);
	}
	config_destroy (&cfg);
	return tmp;
}

gint fill_tree_view_now (GtkTreeModelSort *modelSort, GtkWidget *b) {
	gint index = 0;
	if (g_file_test (SLIM_THEMES_DIR, G_FILE_TEST_IS_DIR)) {
		GDir *dh = g_dir_open (SLIM_THEMES_DIR, 0, NULL);
		GtkListStore *model_child = GTK_LIST_STORE (gtk_tree_model_sort_get_model (modelSort));
		GdkPixbuf *p = gdk_pixbuf_new_from_file_at_size (DATA_DIR "/folder.png", 24, 24, NULL);
		const gchar *item;
		while ((item = g_dir_read_name (dh))) {
			gchar *theme_name = g_build_filename (SLIM_THEMES_DIR, item, "slim.theme", NULL);
			if (g_file_test (theme_name, G_FILE_TEST_IS_REGULAR)) {
				GtkTreeIter iter;
				gtk_list_store_append (model_child, &iter);
				gtk_list_store_set (model_child, &iter, 0, p, 1, item, -1);
				index++;
			}
			g_free (theme_name);
		}
		gtk_widget_set_sensitive (b, index);
		g_object_unref (p);
		g_dir_close (dh);
	} else {
		g_print ("Error: %s: %s\n", _("SLim theme directory not found"), SLIM_THEMES_DIR);
	}
	return index;
}

int main (int argc, char *argv[]) {
	bind_textdomain_codeset (PACKAGE, "UTF-8");
	bindtextdomain (PACKAGE, LOCALEDIR);
	textdomain (PACKAGE);
	setlocale (LC_ALL, "");
	if (g_file_test (UI_PATH, G_FILE_TEST_IS_REGULAR)) {
		AppInfo *ai;
		GtkBuilder *builder;
		gtk_init (&argc, &argv);
		ai = g_slice_new0 (AppInfo);
		ai->slim_theme = NULL;
		ai->_pid = 0;
		builder = gtk_builder_new ();
		gtk_builder_add_from_file (builder, UI_PATH, NULL);
		gtk_builder_connect_signals (builder, ai);
		ai->window = GTK_WIDGET (gtk_builder_get_object (builder, "window1"));
		ai->label = GTK_WIDGET (gtk_builder_get_object (builder, "label1"));
		ai->tree_view = GTK_WIDGET (gtk_builder_get_object (builder, "treeview1"));
		ai->button = GTK_WIDGET (gtk_builder_get_object (builder, "button1"));
		ai->model_sort = GTK_TREE_MODEL_SORT (gtk_tree_view_get_model (GTK_TREE_VIEW (ai->tree_view)));
		g_object_unref (builder);
		if (g_file_test (ICON_PATH, G_FILE_TEST_IS_REGULAR))
			gtk_window_set_icon_from_file (GTK_WINDOW (ai->window), ICON_PATH, NULL);
		gtk_window_set_title (GTK_WINDOW (ai->window), PACKAGE_STRING);
		ai->slim_theme = get_current_slim_theme ("/etc/slim.conf");
		if (ai->slim_theme)
			gtk_label_set_text (GTK_LABEL (ai->label), ai->slim_theme);
		gtk_tree_sortable_set_sort_column_id (GTK_TREE_SORTABLE (ai->model_sort), 1, GTK_SORT_ASCENDING);
		fill_tree_view_now (ai->model_sort, ai->button);
		gtk_widget_show_all (ai->window);
		gtk_main ();
		if (ai->slim_theme) g_free (ai->slim_theme);
		g_slice_free (AppInfo, ai);
	} else {
		g_print ("%s: %s\n", _("UI file not found"), UI_PATH);
	}
	return 0;
}
