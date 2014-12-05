#include "notify.h"

void notify_up (LPAPPWIDGETS p) {
#if (WITH_LIBNOTIFY && WITH_GTK2)
	p->notification = notify_notification_new ("", NULL, NULL);
#elif (WITH_GTK3)
	p->app = g_application_new ("org." PACKAGE, G_APPLICATION_FLAGS_NONE);
	if (!p->app) {
#ifdef WITH_DEBUG
		g_print ("Error on g_application_new\n");
#endif
	}
	if (g_application_register (p->app, NULL, NULL)) {
		p->notification = g_notification_new (PACKAGE);
	} else {
#ifdef WITH_DEBUG
		g_print ("Error on g_application_register\n");
#endif
	}
#endif
}

void notify_popup (LPAPPWIDGETS p, gboolean is_started) {
#if (WITH_LIBNOTIFY && WITH_GTK2)
	gchar *tmp;
	tmp = g_strdup_printf("%s %s" , _("The alarm has"), (is_started) ?  _("started") : _("finised"));
	notify_notification_update (p->notification, PACKAGE_STRING, tmp, ICON_PATH);
	notify_notification_show (p->notification, NULL);
	g_free(tmp);
#elif (WITH_GTK3)
	GIcon *icon;
	GFile *file;
	gchar *tmp;
	tmp = g_strdup_printf("%s %s" , _("The alarm has"), (is_started) ?  _("started") : _("finised"));
	file = g_file_new_for_path (ICON_PATH);
	icon = g_file_icon_new (file);
	g_notification_set_body (p->notification, tmp);
	g_notification_set_icon (p->notification, icon);
	g_application_send_notification (p->app, "show-state", p->notification);
	g_object_unref (file);
	g_object_unref (icon);
	g_free(tmp);
#endif
}

