#ifndef CALLBACKS_H_INCLUDED
#define CALLBACKS_H_INCLUDED

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <gtk/gtk.h>
#include <glib/gi18n.h>
#include <gdk/gdkkeysyms.h>
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
	GtkWidget *add_button;
	GtkWidget *ok_button;
	GtkWidget *clean_button;
	GtkWidget *check1;
	GtkListStore *model_tv; // changed in 2.0
	gint combo_pos;
	gint total;
	gint pos;
	gint audio_bit;
	gint video_format;
	gchar *user;
	gchar *pass;
	GPid pid;
} DataInfo, *LPDATAINFO;

typedef struct {
	gboolean refState;
	GList *refNode;
} RemoveData, *LPREMOVEDATA;

void child_exited (VteTerminal *, LPDATAINFO);

/* enum for combo operation type */
enum {
	FORMAT_MP3,
	FORMAT_MP3_BEST,
	FORMAT_VIDEO,
	FORMAT_3GP,
	FORMAT_FACEBOOK
};

/* move selection on treeview */
enum {
	UNUSED_1,
	SELECTION_MOVE_UP,
	SELECTION_MOVE_DOWN
};

static const gint out_paths[] = {
	G_USER_DIRECTORY_MUSIC,
	G_USER_DIRECTORY_MUSIC,
	G_USER_DIRECTORY_VIDEOS,
	G_USER_DIRECTORY_VIDEOS,
	G_USER_DIRECTORY_VIDEOS
};

enum {
	UNUSED_2,
	LEFT_CLICK,
	MIDDLE_CLICK,
	RIGHT_CLICK
};

#endif
