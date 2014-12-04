#include "main-window.h"
#include "status-icon.h"
#include "page1.h"
#include "page2.h"

int main (int argc, char *argv[]) {
	// locale stuff
	AppWidgets *p;
	p = g_slice_new0 (AppWidgets);
	gtk_init (&argc, &argv);
#if WITH_LIBNOTIFY
	notify_init (PACKAGE_STRING);
	p->notification = notify_up ();
#endif
	// init values
	p->max = 120;
	p->timer_end = 1;
	init_app_ui (p);
	set_status_icon (p);
	set_contents_page1 (p, _("Main"));
	set_contents_page2 (p, _("Preferences"));
	gtk_widget_show_all (p->mainWindow);
	gtk_main ();
	if (p->source_id) {
		g_source_remove (p->source_id);
	}
#if WITH_LIBNOTIFY
	notify_uninit ();
#endif
	g_slice_free (AppWidgets, p);
	return 0;
}
