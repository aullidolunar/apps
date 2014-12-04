#include "notify.h"

#ifdef WITH_LIBNOTIFY

NotifyNotification* notify_up () {
	return notify_notification_new ("", NULL, NULL);
}

void notify_popup (NotifyNotification *notification, gboolean is_started) {
	gchar *tmp;
	tmp = g_strdup_printf("%s %s" , _("The alarm has"), (is_started) ?  _("started") : _("finised"));
	notify_notification_update (notification, PACKAGE_STRING, tmp, ICON_PATH);
	notify_notification_show (notification, NULL);
	g_free(tmp);
}

#endif
