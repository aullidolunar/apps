#include "main.h"

void load_combo (GtkComboBox *c) {
	const gchar *labels[] = {
		_("Choose your operation"),
		_("Increment"),
		_("Decrement"),
		_("Percentage"),
		NULL
	};
	GtkListStore *m;
	GdkPixbuf *p;
	gint pos;
	m = GTK_LIST_STORE (gtk_combo_box_get_model (c));
	p = gdk_pixbuf_new_from_file_at_size (DATA_DIR "/bullet.png", 24, 24, NULL);
	for (pos = 0; labels[pos] != NULL; pos++) {
		GtkTreeIter iter;
		gtk_list_store_append (m, &iter);
		if (pos > 0) {
			gtk_list_store_set (m, &iter, 0, p, 1, labels[pos], -1);
		} else {
			GdkPixbuf *tmp;
			tmp = gdk_pixbuf_new_from_file_at_size (DATA_DIR "/question.png", 24, 24, NULL);
			gtk_list_store_set (m, &iter, 0, tmp,  1, labels[pos], -1);
			g_object_unref (tmp);
		}
	}
	g_object_unref (p);
	gtk_combo_box_set_active (c, 0);
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
		builder = gtk_builder_new ();
		gtk_builder_add_from_file (builder, UI_PATH, NULL);
		gtk_builder_connect_signals (builder, ai);
		ai->window = GTK_WIDGET (gtk_builder_get_object (builder, "window1"));
		ai->combo = GTK_WIDGET (gtk_builder_get_object (builder, "combobox1"));
		ai->label = GTK_WIDGET (gtk_builder_get_object (builder, "label4"));
		ai->val1 = GTK_WIDGET (gtk_builder_get_object (builder, "entry1"));
		ai->val2 = GTK_WIDGET (gtk_builder_get_object (builder, "entry2"));
		ai->resp = GTK_WIDGET (gtk_builder_get_object (builder, "entry3"));
		g_object_unref (builder);
		if (g_file_test (ICON_PATH, G_FILE_TEST_IS_REGULAR))
			gtk_window_set_icon_from_file (GTK_WINDOW (ai->window), ICON_PATH, NULL);
		gtk_window_set_title (GTK_WINDOW (ai->window), PACKAGE_STRING);
		load_combo (GTK_COMBO_BOX (ai->combo));
		gtk_widget_show_all (ai->window);
		gtk_main ();
		g_slice_free (AppInfo, ai);
	} else {
		g_print ("%s: %s\n", _("UI file not found"), UI_PATH);
	}
	return 0;
}
