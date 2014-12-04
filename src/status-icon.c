#include "status-icon.h"

#if (WITH_GTK2 || GTK_MINOR_VERSION < 14)
void status_icon_activate (GtkStatusIcon *status_icon, LPAPPWIDGETS p) {

	toggle_ui (GTK_WINDOW (p->mainWindow));
}
#endif

void set_status_icon (LPAPPWIDGETS p) {
#if (WITH_GTK2 || GTK_MINOR_VERSION < 14)
	p->status_icon = gtk_status_icon_new_from_file (ICON_PATH);
	gtk_status_icon_set_tooltip_text (p->status_icon, _("Alarm is stopped"));
	gtk_status_icon_set_visible (p->status_icon, TRUE);
	g_signal_connect (p->status_icon, "activate", G_CALLBACK(status_icon_activate), p);
#endif
}
