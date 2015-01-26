#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED

#include "main.h"

void show_preferences_dialog (LPDATAINFO);
gboolean start_or_stop_timer_now (LPDATAINFO);
void toggle_window (GtkWindow *);
void toggle_ui (GObject *, GObject*, GObject*, gboolean);
gboolean test_timer_running (GtkWindow *, GObject *);
void show_popup_menu (GtkMenu *, guint, guint);
void show_about_dialog (LPDATAINFO);
void set_timer_time (GObject *, gint, gint, gint);

#endif
