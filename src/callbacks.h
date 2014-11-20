#ifndef CALLBACKS_H_INCLUDED
#define CALLBACKS_H_INCLUDED

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <gtk/gtk.h>
#include <glib/gi18n.h>
#include <vte/vte.h>
#include <locale.h>
#include <libintl.h>
#include "callbacks.h"

typedef struct {
	GtkWidget *toplevel;
	GtkWidget *terminal;
	GtkWidget *scroll1;
	GtkWidget *combo1;
} DataInfo, *LPDATAINFO;

void on_window1_destroy(GtkWidget *, LPDATAINFO);

#endif
