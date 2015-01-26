#include "helpers.h"

void show_preferences_dialog (LPDATAINFO lpdi) {
	gtk_widget_set_sensitive (GTK_WIDGET (lpdi->object[CHECK_4_NOTIFY]), lpdi->haveNotify);
	gtk_dialog_run ( (GTK_DIALOG (lpdi->object[PREFDIALOG])));
	gtk_widget_hide (GTK_WIDGET (lpdi->object[PREFDIALOG]));
}

void show_about_dialog (LPDATAINFO lpdi) {
	gtk_dialog_run ( (GTK_DIALOG (lpdi->object[ABOUTDIALOG])));
	gtk_widget_hide (GTK_WIDGET (lpdi->object[ABOUTDIALOG]));
}

gboolean show_message_box (GtkWindow *parent) {
	GtkWidget *m;
	gboolean response;
	m = gtk_message_dialog_new_with_markup (parent, GTK_DIALOG_MODAL|GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_WARNING, GTK_BUTTONS_YES_NO, "<b>%s</b>", _("Alarm still in process"));
	gtk_window_set_title (GTK_WINDOW (m), PACKAGE_STRING);
	gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (m), _("do you want to exit anyway?"));
	if (gtk_dialog_run (GTK_DIALOG (m)) == GTK_RESPONSE_YES) {
		response = TRUE;
	} else {
		response = FALSE;
	}
	gtk_widget_destroy (m);
	return response;
}

#ifdef WITH_LIBNOTIFY
void do_notification (NotifyNotification *notification, gboolean haveNotify, gboolean state, int max) {
	if (haveNotify) {
		gchar *tmp;
		tmp = g_strdup_printf ("%s %s", _("The alarm has"), state ? _("started") : _("stopped"));
		notify_notification_update (notification, PACKAGE_STRING, tmp, ICON_PATH);
		notify_notification_show (notification, NULL);
		g_free (tmp);
	}
}
#endif

void play_sound (void) {
	ca_context_play (ca_gtk_context_get (), 0, CA_PROP_MEDIA_FILENAME, SOUND_PATH, NULL);
}

gboolean timer_ticks (LPDATAINFO lpdi) {
	gboolean state;
	state = G_SOURCE_CONTINUE;
	lpdi->sec++;
	if (lpdi->sec == 60) {
		lpdi->sec = 0;
		lpdi->min++;
	}
	if (lpdi->min == lpdi->max) {
		lpdi->sec = 0;
		lpdi->min = 0;
		if (lpdi->haveSound) play_sound ();
#ifdef WITH_LIBNOTIFY
		if (lpdi->haveNotify) do_notification (lpdi->notification, lpdi->haveNotify, FALSE, -1);
#endif
		state = G_SOURCE_REMOVE;
		toggle_ui (lpdi->object[CENTERCHILD], lpdi->object[PLAY_STOP_MENU_ITEM], lpdi->object[PREF_MENU_ITEM], FALSE);
		gtk_window_deiconify (GTK_WINDOW (lpdi->object[TOPLEVEL]));
		gtk_window_present (GTK_WINDOW (lpdi->object[TOPLEVEL]));
		gtk_status_icon_set_tooltip_text (lpdi->status_icon, _("Alarm is not running"));
		lpdi->IDSource = 0;
	}
	set_timer_time (lpdi->object[TIMER_LABEL], lpdi->sec, lpdi->min, lpdi->max);
	return state;
}

gboolean start_or_stop_timer_now (LPDATAINFO lpdi) {
	gboolean state;
	state = gtk_widget_get_sensitive (GTK_WIDGET (lpdi->object[CENTERCHILD]));
	if (state) {
		if (lpdi->haveReset) lpdi->sec = 0;
		lpdi->IDSource = g_timeout_add (1000, (GSourceFunc)timer_ticks, lpdi);
	} else {
		g_source_remove (lpdi->IDSource);
		lpdi->IDSource = 0;
	}
	gtk_status_icon_set_tooltip_text (lpdi->status_icon, state ? _("Alarm is running") : _("Alarm is not running"));
#ifdef WITH_LIBNOTIFY
	if (lpdi->haveNotify) do_notification (lpdi->notification, lpdi->haveNotify, state, lpdi->max);
#endif
	return state;
}

void toggle_window (GtkWindow *parent) {
	gboolean state;
	state = gtk_widget_get_visible(GTK_WIDGET (parent));
	if (state) {
		gtk_widget_set_visible (GTK_WIDGET (parent), FALSE);
	} else {
		gtk_window_deiconify (parent);
		gtk_window_present (parent);
	}
}

void toggle_ui (GObject *centerChild, GObject* menu_item, GObject *pref_item, gboolean state) {
	gtk_widget_set_sensitive (GTK_WIDGET (centerChild), !state);
	gtk_widget_set_sensitive (GTK_WIDGET (pref_item), !state);
	gtk_menu_item_set_label (GTK_MENU_ITEM (menu_item), state ? GTK_STOCK_MEDIA_STOP : GTK_STOCK_MEDIA_PLAY);
}

gboolean test_timer_running (GtkWindow *window, GObject *centerchild) {
	gboolean state;
	state = gtk_widget_get_sensitive (GTK_WIDGET (centerchild));
	if (!state) return !show_message_box (window);
	return FALSE;
}

void show_popup_menu (GtkMenu *menu, guint button, guint activate_time) {
	gtk_menu_popup (menu, NULL, NULL, NULL, NULL, button, activate_time);
}

void set_timer_time (GObject *widget, gint s, gint m, gint max) {
	gchar *tmp;
	tmp = g_strdup_printf ("[%02i:%02i/%02i:00]", m, s, max);
	gtk_label_set_text (GTK_LABEL (widget), tmp);
	g_free (tmp);
}
