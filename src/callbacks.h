#ifndef CALLBACKS_H_INCLUDED
#define CALLBACKS_H_INCLUDED
#include "main.h"

enum {
	UNUSED,
	SELECTION_MOVE_UP,
	SELECTION_MOVE_DOWN
};

gint msg_box (GtkWindow *, GtkMessageType, const gchar*, const gchar *);

#endif
