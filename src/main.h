#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <gtk/gtk.h>
#include <glib/gi18n.h>
#include <locale.h>
#include <libintl.h>

typedef struct {
	GtkWidget *window;
	GtkWidget *toolbar;
	GtkWidget *centerWidget;
	GtkWidget *combo1; // combo for input directory
	GtkWidget *combo2; // combo for output directory
	GtkWidget *combo3; // combo for bitrate
	GtkWidget *tool1; // execute
	GtkWidget *status_icon; // as
	GtkWidget *status_text; // it is :)
	gboolean deleteMe; // delete source file
	GList *list; // file container
	gint total;
	gint current;
	GPid pid;
	gchar *outfile;
	gchar *infile;
} AppInfo, *LPAPPINFO;

#endif
