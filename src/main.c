#include "callbacks.h"

int main (int argc, char *argv[]) {
	GError *error = NULL;
	GtkBuilder *builder;
	gint exitStatus;
	bind_textdomain_codeset (PACKAGE, "UTF-8");
	bindtextdomain (PACKAGE, LOCALEDIR);
	textdomain (PACKAGE);
	setlocale (LC_ALL, "");
	gtk_init (&argc, &argv);
	builder = gtk_builder_new ();
	if (gtk_builder_add_from_file (builder, UI_PATH, &error)) {
		const gchar *object_names[] = {
			"window1", // TOPLEVEL
			"vbox3", // CENTERCHILD
			"label1", // TIMER_LABEL
			"imagemenuitem1", // PLAY_STOP_MENU_ITEM
			"dialog1", // PREFDIALOG
			"checkbutton2", // CHECK_4_NOTIFY
			"aboutdialog1", // ABOUTDIALOG
			"menu1", // STATUS_MENU_ITEM
			"imagemenuitem2", // PREF_MENU_ITEM
			NULL
		};
		DataInfo di;
		gint pos;
		di.max = 1;
		di.sec = 0;
		di.min = 0;
		di.IDSource = 0;
#ifdef WITH_LIBNOTIFY
		di.haveNotify = notify_init (PACKAGE_STRING);
		if (di.haveNotify) di.notification = notify_notification_new ("", NULL, NULL);
#else
		di.haveNotify = FALSE;
#endif
		for (pos = 0; pos < NTH_DATAINFO_OBJECTS; pos++) di.object[pos] = gtk_builder_get_object (builder, object_names[pos]);
		gtk_builder_connect_signals (builder, &di);
		g_object_unref (builder);
		set_timer_time (di.object[TIMER_LABEL], di.sec, di.min, di.max);
		const gchar *authors[] = {
			SELFIE,
			NULL
		};
		g_object_set (di.object[ABOUTDIALOG], "authors", authors, "version", PACKAGE_VERSION, "translator-credits", SELFIE, "logo", gtk_window_get_icon (GTK_WINDOW (di.object[TOPLEVEL])), NULL);
		if (g_file_test (ICON_PATH, G_FILE_TEST_IS_REGULAR)) gtk_window_set_icon_from_file (GTK_WINDOW (di.object[TOPLEVEL]), ICON_PATH, NULL);
		gtk_window_set_title (GTK_WINDOW (di.object[TOPLEVEL]), PACKAGE_STRING);
		di.status_icon = gtk_status_icon_new_from_file (ICON_PATH);
		gtk_status_icon_set_tooltip_text (di.status_icon, _("Alarm is not running"));
		g_signal_connect (di.status_icon, "activate", G_CALLBACK (on_status_icon_activate), GTK_WINDOW (di.object[TOPLEVEL]));
		g_signal_connect (di.status_icon, "popup-menu", G_CALLBACK (on_status_icon_popup_menu), GTK_MENU (di.object[STATUS_MENU_ITEM]));
		gtk_widget_show_all (GTK_WIDGET (di.object[TOPLEVEL]));
		gtk_main ();
		g_object_unref (di.status_icon);
#ifdef WITH_LIBNOTIFY
		if (di.haveNotify) {
			g_object_unref (di.notification);
			notify_uninit ();
		}
#endif
		if (di.IDSource) g_source_remove (di.IDSource);
		exitStatus = 0;
	} else {
		g_print ("Error: %s\n", error->message);
		g_clear_error (&error);
		exitStatus = 1;
	}
	return exitStatus;
}
