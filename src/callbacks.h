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
	GtkWidget *child1;
	GtkWidget *child2;
	GtkWidget *terminal;
	GtkWidget *scroll1;
	GtkWidget *combo1;
	GtkWidget *url_text;
	GtkWidget *user_text;
	GtkWidget *pass_text;
	GtkWidget *output_dir;
	GtkWidget *add_button;
	GtkWidget *ok_button;
	GtkWidget *check1;
	GtkListStore *model_combo;
	gint combo_pos;
	gint total;
	gint pos;
	gchar *user;
	gchar *pass;
	GPid pid;
	GString *_str;
} DataInfo, *LPDATAINFO;

static const gchararray params[] = {
	Y_PATH " -f 17 --extract-audio --audio-format mp3 --audio-quality 128k ",
	Y_PATH " -f best ",
	Y_PATH " -f 17 ",
	Y_PATH " "
};
	
void child_exited (VteTerminal *, LPDATAINFO);

#endif
