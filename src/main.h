#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <gtk/gtk.h>
#include <glib/gi18n.h>
#include <glib/gstdio.h>
#include <gdk/gdkkeysyms.h>
#include <locale.h>
#include <libintl.h>

typedef struct {
	GtkWidget *window;
	GtkWidget *tree_view;
	GtkWidget *label;
	GtkWidget *button;
	GPid _pid;
	GtkTreeModelSort *model_sort;
	gchar *slim_theme;
} AppInfo, *LPAPPINFO;

static const gint MAX_LINE = 256;
static const gchararray SLIM_CONF_PATH = "/etc/slim.conf";
static const gchararray SLIM_THEMES_DIR = "/usr/share/slim/themes";

#endif
