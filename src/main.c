#include "callbacks.h"

int main (int argc, char *argv[]) {
	GOptionContext *context;
	GError *error;
	gint audio;
	gint video;
	gboolean dirs;
	GOptionEntry entries[] = {
		{"audio", 'a', 0, G_OPTION_ARG_INT, &audio, _("set audio bitrate in MP3 option (default is 256)"), _("number")},
		{"video", 'v', 0, G_OPTION_ARG_INT, &video, _("set download video format in VIDEO and 3GP options (defaults are -1 for best and 17 respectly)"), _("string")},
		{"dirs", 'd', 0, G_OPTION_ARG_NONE, &dirs, _("display directory paths"), NULL},
		{NULL}
	};
	// locale stuff
	bind_textdomain_codeset (PACKAGE, "UTF-8");
	bindtextdomain (PACKAGE, LOCALEDIR);
	textdomain (PACKAGE);
	setlocale (LC_ALL, "");
	// parse command line
	audio = 256;
	video = -1;
	dirs = FALSE;
	context = g_option_context_new (PACKAGE_STRING);
	g_option_context_add_main_entries (context, entries, NULL);
	g_option_context_add_group (context, gtk_get_option_group (TRUE));
	if (!g_option_context_parse (context, &argc, &argv, &error)) {
		g_print ("Error: %s\n", error->message);
		g_error_free (error);
		g_option_context_free (context);
		return 1;
	}
	if (dirs) {
		g_print ("*** %s ***\nPREFIX: %s\nRES_DIR: %s\nLOCALEDIR: %s\nF_PATH: %s\nY_PATH: %s\n", PACKAGE_STRING, PREFIX, RES_DIR, LOCALEDIR, F_PATH, Y_PATH);
		return 0;
	}
	g_option_context_free (context);
	// test builder file
	if (g_file_test (UI_PATH, G_FILE_TEST_IS_REGULAR)) {
		GtkBuilder *builder;
		DataInfo *ptr;
		gtk_init (&argc, &argv);
		ptr = g_slice_new0 (DataInfo);
		builder = gtk_builder_new ();
		ptr->combo_pos = 0;
		ptr->total = 0;
		ptr->pos = 0;
		ptr->pid = -1;
		ptr->audio_bit = audio;
		ptr->video_format = video;
		gtk_builder_add_from_file (builder, UI_PATH, NULL);
		ptr->toplevel = GTK_WIDGET (gtk_builder_get_object (builder, "window1"));
		ptr->scroll1 = GTK_WIDGET (gtk_builder_get_object (builder, "scrolledwindow1"));
		ptr->combo1 = GTK_WIDGET (gtk_builder_get_object (builder, "comboboxtext1"));
		ptr->url_text = GTK_WIDGET (gtk_builder_get_object (builder, "entry1"));
		ptr->user_text = GTK_WIDGET (gtk_builder_get_object (builder, "entry3"));
		ptr->pass_text = GTK_WIDGET (gtk_builder_get_object (builder, "entry4"));
		ptr->output_dir = GTK_WIDGET (gtk_builder_get_object (builder, "entry2"));
		ptr->check1 = GTK_WIDGET (gtk_builder_get_object (builder, "checkbutton1"));
		ptr->add_button = GTK_WIDGET (gtk_builder_get_object (builder, "button1"));
		ptr->ok_button = GTK_WIDGET (gtk_builder_get_object (builder, "button4"));
		ptr->child1 = GTK_WIDGET (gtk_builder_get_object (builder, "vbox1"));
		ptr->child2 = GTK_WIDGET (gtk_builder_get_object (builder, "vbox3"));
		ptr->model_combo = GTK_LIST_STORE (gtk_builder_get_object (builder, "liststore1"));
		gtk_builder_connect_signals (builder, ptr);
		g_object_unref (builder);
		if (g_file_test (ICON_PATH, G_FILE_TEST_IS_REGULAR)) {
			gtk_window_set_icon_from_file (GTK_WINDOW (ptr->toplevel), ICON_PATH, NULL);
		}
		ptr->terminal = vte_terminal_new ();
		g_signal_connect (ptr->terminal, "child-exited", G_CALLBACK(child_exited), ptr);
		gtk_container_add (GTK_CONTAINER (ptr->scroll1), ptr->terminal);
		gtk_combo_box_set_active (GTK_COMBO_BOX (ptr->combo1), ptr->combo_pos);
		gtk_widget_show_all (ptr->toplevel);
		gtk_main ();
		if (ptr->pid > 0) {
			g_spawn_close_pid (ptr->pid);
			g_string_free (ptr->_str, TRUE);
		}
		g_slice_free (DataInfo, ptr);
		return 0;
	}
	g_print ("%s.\n", _("No UI file was found"));
	return 1;
}
