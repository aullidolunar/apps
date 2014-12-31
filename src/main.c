#include "helpers.h"
#include <stdlib.h>

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
		builder = gtk_builder_new_from_file (UI_PATH);
		gtk_builder_connect_signals (builder, ai);
		ai->window = GTK_WIDGET (gtk_builder_get_object (builder, "window1"));
		ai->toolbar = GTK_WIDGET (gtk_builder_get_object (builder, "toolbar1"));
		ai->centerWidget = GTK_WIDGET (gtk_builder_get_object (builder, "box2"));
		ai->combo1 = GTK_WIDGET (gtk_builder_get_object (builder, "combobox1"));
		ai->combo2 = GTK_WIDGET (gtk_builder_get_object (builder, "combobox2"));
		ai->combo3 = GTK_WIDGET (gtk_builder_get_object (builder, "combobox3"));
		ai->status_icon = GTK_WIDGET (gtk_builder_get_object (builder, "image1"));
		ai->status_text = GTK_WIDGET (gtk_builder_get_object (builder, "label1"));
		ai->tool1 = GTK_WIDGET (gtk_builder_get_object (builder, "toolbutton1"));
		g_object_unref (builder);
		if (g_file_test (ICON_PATH, G_FILE_TEST_IS_REGULAR))
			gtk_window_set_icon_from_file (GTK_WINDOW (ai->window), ICON_PATH, NULL);
		init_ui (ai);
		ai->deleteMe = TRUE;
		ai->pid = 0;
		gtk_window_set_title (GTK_WINDOW (ai->window), PACKAGE_STRING);
		gtk_widget_show_all (ai->window);
		gtk_main ();
		if (ai->list != NULL) g_list_free_full (ai->list, g_free);
		if (ai->outfile) g_free (ai->outfile);
		g_slice_free (AppInfo, ai);
	} else {
		g_print ("%s: %s\n", _("UI file not found"), UI_PATH);
	}
	return 0;
}
