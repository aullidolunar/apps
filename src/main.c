#include "callbacks.h"

int main (int argc, char *argv[]) {
	// test builder file
	if (g_file_test (UI_PATH, G_FILE_TEST_IS_REGULAR)) {
		GtkBuilder *builder;
		DataInfo *ptr;
		gtk_init (&argc, &argv);
		ptr = g_slice_new0 (DataInfo);
		builder = gtk_builder_new ();
		gtk_builder_add_from_file (builder, UI_PATH, NULL);
		ptr->toplevel = GTK_WIDGET (gtk_builder_get_object (builder, "window1"));
		ptr->scroll1 = GTK_WIDGET (gtk_builder_get_object (builder, "scrolledwindow1"));
		ptr->combo1 = GTK_WIDGET (gtk_builder_get_object (builder, "comboboxtext1"));
		gtk_builder_connect_signals (builder, ptr);
		g_object_unref (builder);
		if (g_file_test (ICON_PATH, G_FILE_TEST_IS_REGULAR)) {
			gtk_window_set_icon_from_file (GTK_WINDOW (ptr->toplevel), ICON_PATH, NULL);
		}
		ptr->terminal = vte_terminal_new ();
		gtk_container_add (GTK_CONTAINER (ptr->scroll1), ptr->terminal);
		
		gtk_combo_box_set_active (GTK_COMBO_BOX (ptr->combo1),0);
		gtk_widget_show_all (ptr->toplevel);
		gtk_main ();
		g_slice_free (DataInfo, ptr);
		return 0;
	}
	g_print ("%s.\n", _("No UI file was found"));
	return 1;
}
