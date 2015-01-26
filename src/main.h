#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <gtk/gtk.h>
#include <glib/gi18n.h>
#include <locale.h>
#ifdef WITH_LIBNOTIFY
#include <libnotify/notify.h>
#endif
#include <canberra-gtk.h>

enum DataInfoObjects {
	TOPLEVEL,
	CENTERCHILD,
	TIMER_LABEL,
	PLAY_STOP_MENU_ITEM,
	PREFDIALOG,
	CHECK_4_NOTIFY,
	ABOUTDIALOG,
	STATUS_MENU_ITEM,
	PREF_MENU_ITEM, 
	NTH_DATAINFO_OBJECTS
};

typedef struct {
	GObject *object[NTH_DATAINFO_OBJECTS];
	GtkStatusIcon *status_icon;
	gboolean haveSound;
	gboolean haveNotify;
	gboolean haveReset;
	gint sec;
	gint min;
	gint max;
#ifdef WITH_LIBNOTIFY
	NotifyNotification *notification;
#endif
	guint IDSource;
} DataInfo, *LPDATAINFO;

#endif
