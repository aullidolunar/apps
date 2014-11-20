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
	GtkWidget *child2;
	GtkWidget *terminal;
	GtkWidget *scroll1;
	GtkWidget *combo1;
	GtkWidget *url_text;
	GtkWidget *output_dir;
	GtkWidget *add_button;
	GtkWidget *ok_button;
	GtkWidget *check1;
	GtkListStore *model_combo;
	gint combo_pos;
} DataInfo, *LPDATAINFO;

#endif
