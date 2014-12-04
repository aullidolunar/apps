#include "timer.h"

gboolean timer_callback (gpointer d) {
	LPAPPWIDGETS p = (LPAPPWIDGETS)d;
	gboolean state;
	gchar *tmp;
	p->s++;
	state = G_SOURCE_CONTINUE;
	if (p->s == 60) {
		p->s = 0;
		p->m++;
	}
	if (p->m == p->timer_end) {
		p->s = 0;
		p->m = 0;
		if (!p->_sound) {
			play_sound ();
		}
#ifdef WITH_LIBNOTIFY
		if (!p->_notify) {
			notify_popup (p->notification, FALSE);
		}
#endif
		state = G_SOURCE_REMOVE;
		g_source_remove (p->source_id);
		update_button_helper (GTK_WIDGET (p->button_play), STOP);
		gtk_widget_set_sensitive (p->notebook, TRUE);
		gtk_window_deiconify (GTK_WINDOW (p->mainWindow));
		gtk_window_present (GTK_WINDOW (p->mainWindow));
	}
	tmp = g_strdup_printf ("%02i:%02i", p->m, p->s);
	gtk_label_set_text (GTK_LABEL (p->time_label), tmp);
	g_free (tmp);
	return state;
}

void timer_destroyed (gpointer d) {
	LPAPPWIDGETS p = (LPAPPWIDGETS)d;
	p->source_id = 0;
}

guint start_timer (LPAPPWIDGETS p) {
	return g_timeout_add_full (G_PRIORITY_DEFAULT, 1000, timer_callback, p, timer_destroyed);
}
