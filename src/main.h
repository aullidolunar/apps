#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <gtk/gtk.h>
#include <glib/gi18n.h>
#include <locale.h>
#include <libintl.h>
#include "notify.h"

typedef struct {
	GtkWidget *mainWindow;
	GtkWidget *notebook;
	GtkWidget *button_play;
	GtkWidget *time_label;
	gint max;
	gboolean _notify;
	gboolean _sound;
	gboolean _reset;
	guint source_id;
	gint timer_end;
	gint s;
	gint m;
#if (WITH_GTK2 || GTK_MINOR_VERSION < 14)
	GtkStatusIcon *status_icon;
#endif
#if WITH_LIBNOTIFY
	NotifyNotification *notification;
#endif
} AppWidgets, *LPAPPWIDGETS;

#endif
