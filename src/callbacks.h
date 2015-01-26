#ifndef CALLBACKS_H_INCLUDED
#define CALLBACKS_H_INCLUDED

#include "helpers.h"

void on_status_icon_activate (GtkStatusIcon *, GtkWindow *);
void on_status_icon_popup_menu (GtkStatusIcon *, guint, guint, GtkMenu*);

#endif
