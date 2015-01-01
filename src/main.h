#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <gtk/gtk.h>
#include <glib/gi18n.h>
#include <gdk/gdkkeysyms.h>
#include <locale.h>
#include <libintl.h>

typedef struct {
	GtkWidget *window;
	GtkWidget *combo;
	GtkWidget *val1;
	GtkWidget *val2;
	GtkWidget *resp;
} AppInfo, *LPAPPINFO;

enum {
	UNUSED,
	INCREMENT,
	DECREMENT,
	PERCENTAGE
};

#endif
